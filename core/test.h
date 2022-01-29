#pragma once

#include <cmath>

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
      ERROR << "There are test failures!\n";
      std::exit(1);
    }
  }

  static TestRegistration &Singleton() {
    static TestRegistration *kTestReg = new TestRegistration();
    return *kTestReg;
  }

private:
  std::vector<TestCase *> test_cases_;
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

#define EXPECT_EQ(a, b)                                                        \
  {                                                                            \
    auto aresult = (a);                                                        \
    auto bresult = (b);                                                        \
    if (aresult != bresult) {                                                  \
      Fail() << "Expected " << #a << " to be equal to " << #b << " but "       \
             << aresult << " != " << bresult << "\n";                          \
    }                                                                          \
  }

#define EXPECT_LT(a, b)                                                        \
  {                                                                            \
    auto aresult = (a);                                                        \
    auto bresult = (b);                                                        \
    if (!(aresult < bresult)) {                                                \
      Fail() << "Expected " << #a << " to be less than " << #b << " but "      \
             << aresult << " >= " << bresult << "\n";                          \
    }                                                                          \
  }

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
