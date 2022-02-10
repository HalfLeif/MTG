#pragma once

#include <cmath>
#include <iostream>
#include <sstream>

#include "debug.h"

void RunAllTests();

class TestRegistration {
public:
  class TestCase {
  public:
    TestCase(std::string test_name, std::string file, int line)
        : test_name_(test_name), file_(file), line_(line) {
      TestRegistration::Singleton().AddTestCase(this);
    }

    bool RunAndLogFailure() {
      RunTest();
      if (success_) {
        INFO << "Test passed: " << test_name_ << " from " << file_ << ":"
             << line_ << std::endl;
      } else {

        std::cerr << "Test failed: " << test_name_ << " from " << file_ << ":"
                  << line_ << std::endl
                  << std::endl;
      }
      return success_;
    }

  protected:
    // TODO: Refactor into simply streaming Fail();
    std::ostream &Fail(std::string_view msg) {
      return Fail() << msg << std::endl;
    }

    std::ostream &Fail() {
      return FailSilently() << "Failed test " << test_name_ << std::endl;
    }

    std::ostream &FailSilently() {
      success_ = false;
      return std::cerr;
    }

    class TestExpectationHelper;

  private:
    virtual void RunTest() = 0;

    bool success_ = true;
    std::string test_name_;
    std::string file_;
    int line_;
  };

  void AddTestCase(TestCase *t) { test_cases_.push_back(t); }

  void RunTests() {
    bool success = true;
    for (TestCase *t : test_cases_) {
      // Always evaluate, even if success is already false.
      success = t->RunAndLogFailure() && success;
    }

    if (success) {
      INFO << "All tests pass!\n";
    } else {
      FATAL << "There are test failures!\n";
    }
  }

  static TestRegistration &Singleton() {
    static TestRegistration *kTestReg = new TestRegistration();
    return *kTestReg;
  }

private:
  std::vector<TestCase *> test_cases_;
};

void RunAllTests() { TestRegistration::Singleton().RunTests(); }

class TestRegistration::TestCase::TestExpectationHelper {
public:
  TestExpectationHelper(TestRegistration::TestCase *test, std::string file,
                        int line)
      : test_(test), file_(std::move(file)), line_(line) {}

  ~TestExpectationHelper() {
    if (!pass_) {
      test_->FailSilently() << "Expectation failed at " << file_ << ":" << line_
                            << ": " << failure_stream_.str() << std::endl;
    }
  }

  template <typename L, typename R>
  bool EvaluateEq(const L &left, const R &right, const char *left_desc,
                  const char *right_desc) {
    pass_ = (left == right);
    if (!pass_) {
      Stream() << "Expected " << left_desc << " to be equal to " << right_desc
               << " but " << left << " != " << right << std::endl;
    }
    return pass_;
  }

  template <typename L, typename R>
  bool EvaluateNe(const L &left, const R &right, const char *left_desc,
                  const char *right_desc) {
    pass_ = (left != right);
    if (!pass_) {
      Stream() << "Expected " << left_desc << " to be different from "
               << right_desc << " but " << left << " == " << right << std::endl;
    }
    return pass_;
  }

  template <typename L, typename R>
  bool EvaluateLt(const L &left, const R &right, const char *left_desc,
                  const char *right_desc) {
    pass_ = (left < right);
    if (!pass_) {
      Stream() << "Expected " << left_desc << " to be equal to " << right_desc
               << " but " << left << " != " << right << std::endl;
    }
    return pass_;
  }

  template <typename L, typename R>
  bool EvaluateNear(const L &left, const R &right, const char *left_desc,
                    const char *right_desc) {
    pass_ = (std::abs(left - right) < 0.01);
    if (!pass_) {
      Stream() << "Expected " << left_desc << " to be near " << right_desc
               << " but " << left << " != " << right << std::endl;
    }
    return pass_;
  }

  std::ostream &Stream() { return failure_stream_; }

private:
  // Contains all streamed debug about the test expectation.
  std::stringstream failure_stream_;
  bool pass_ = true;

  TestRegistration::TestCase *test_;
  std::string file_;
  int line_;
};

// class MyTest : public TestRegistration::TestCase {
// public:
//   MyTest() : TestRegistration::TestCase("MyTest", __FILE__, __LINE__) {}
//
// private:
//   bool RunTest() const override;
// } kMyTestInstance;
// bool MyTest::RunTest() const { return 1 == 2; }

#define TEST(tname)                                                            \
  class TestCase##tname : public TestRegistration::TestCase {                  \
  public:                                                                      \
    TestCase##tname()                                                          \
        : TestRegistration::TestCase(#tname, __FILE__, __LINE__) {}            \
                                                                               \
  private:                                                                     \
    void RunTest() override;                                                   \
  } kTestInstance##tname;                                                      \
  inline void TestCase##tname::RunTest()

// Supports streaming comments to the test expectation object:
// EXPECT_EQ(a, 1) << "blah" << std::endl;
//
// Streaming comment expression is only evaluated on expectation failure.
#define EXPECT_EQ(a, b)                                                        \
  if (TestExpectationHelper helper(this, __FILE__, __LINE__);                  \
      !helper.EvaluateEq((a), (b), #a, #b))                                    \
  helper.Stream()

#define EXPECT_NE(a, b)                                                        \
  if (TestExpectationHelper helper(this, __FILE__, __LINE__);                  \
      !helper.EvaluateNe((a), (b), #a, #b))                                    \
  helper.Stream()

#define EXPECT_LT(a, b)                                                        \
  if (TestExpectationHelper helper(this, __FILE__, __LINE__);                  \
      !helper.EvaluateLt((a), (b), #a, #b))                                    \
  helper.Stream()

#define EXPECT_TRUE(a) EXPECT_EQ(a, true)
#define EXPECT_FALSE(a) EXPECT_EQ(a, false)

#define EXPECT_NEAR(a, b)                                                      \
  if (TestExpectationHelper helper(this, __FILE__, __LINE__);                  \
      !helper.EvaluateNear((a), (b), #a, #b))                                  \
  helper.Stream()

// Passes by default
TEST(SimpleTest) {
  int a = 1;
  EXPECT_EQ(a, 1);
  EXPECT_EQ(a + 1, 2);
  EXPECT_LT(a, 5);
  EXPECT_LT(0, a);
  EXPECT_NE(1, 2);

  EXPECT_TRUE(a < 2);
  EXPECT_FALSE(a > 2);
  EXPECT_NEAR(1.0, 1.001);
}

TEST(FatalLog) {
  CHECK(true) << "OK" << std::endl;
  // CHECK(false) << "Condition failed!" << std::endl;
}

TEST(OnlyEvaluateCommentOnFailure) {
  int count = 0;
  auto cb = [&count]() { return ++count; };

  // Verify that the callback works.
  cb();
  cb();
  EXPECT_EQ(count, 2);

  // Expectations are true so expressions at << is never evaluated, and so count
  // should not increase.
  EXPECT_EQ(1, 1) << cb() << std::endl;
  EXPECT_TRUE(true) << cb() << std::endl;
  EXPECT_LT(1, 2) << cb() << std::endl;
  EXPECT_NEAR(1, 1) << cb() << std::endl;
  EXPECT_EQ(count, 2);
}
