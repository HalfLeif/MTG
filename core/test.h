#pragma once

#include <cmath>
#include <iostream>

#include "debug.h"

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
        INFO << test_name_ << " passed! Defined at " << file_ << "::" << line_
             << "\n";
      } else {
        ERROR << test_name_ << " failed! Defined at " << file_ << "::" << line_
              << "\n";
      }
      return success_;
    }

  protected:
    void Fail(std::string msg) {
      Fail() << test_name_ << " failed with error: " << msg << "\n";
      success_ = false;
    }

    std::ostream &Fail() {
      success_ = false;
      return ERROR << test_name_ << "\n";
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

std::ostream &NullStream() {
  class NullBuffer : public std::streambuf {
  public:
    int overflow(int c) { return c; }
  };

  static NullBuffer *kNullBuffer = new NullBuffer;
  static std::ostream *kNullStream = new std::ostream(kNullBuffer);
  return *kNullStream;
}

class TestRegistration::TestCase::TestExpectationHelper {
public:
  TestExpectationHelper(TestRegistration::TestCase *test) : test_(test) {}

  template <typename L, typename R>
  std::ostream &EvaluateEq(const L &left, const R &right, const char *left_desc,
                           const char *right_desc) {
    return EvaluateBool(left == right)
           << "Expected " << left_desc << " to be equal to " << right_desc
           << " but " << left << " != " << right << std::endl;
  }

  template <typename L, typename R>
  std::ostream &EvaluateLt(const L &left, const R &right, const char *left_desc,
                           const char *right_desc) {
    return EvaluateBool(left < right)
           << "Expected " << left_desc << " to be equal to " << right_desc
           << " but " << left << " != " << right << std::endl;
  }

private:
  std::ostream &EvaluateBool(bool pass) {
    if (!pass) {
      maybe_stream_ = &test_->Fail();
    }
    return *maybe_stream_;
  }

  TestRegistration::TestCase *test_;

  // NullStream prints nothing. Is replaced with real stream in case of test
  // failure.
  std::ostream *maybe_stream_ = &NullStream();
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
#define EXPECT_EQ(a, b) TestExpectationHelper(this).EvaluateEq((a), (b), #a, #b)
#define EXPECT_LT(a, b) TestExpectationHelper(this).EvaluateLt((a), (b), #a, #b)
#define EXPECT_TRUE(a) EXPECT_EQ(a, true)
#define EXPECT_FALSE(a) EXPECT_EQ(a, false)
#define EXPECT_NEAR(a, b) EXPECT_LT(std::abs(a - b), 0.01)

// Passes by default
TEST(SimpleTest) {
  int a = 1;
  EXPECT_EQ(a, 1);
  EXPECT_EQ(a + 1, 2);
  EXPECT_LT(a, 5);
  EXPECT_LT(0, a);

  EXPECT_TRUE(a < 2);
  EXPECT_FALSE(a > 2);
  EXPECT_NEAR(1.0, 1.001);
}

TEST(FatalLog) {
  CHECK(true) << "OK" << std::endl;
  // CHECK(false) << "Condition failed!" << std::endl;
}
