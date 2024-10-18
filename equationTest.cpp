#include <iostream>
#include <cppunit/TestRunner.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>

class TestSolution : public CPPUNIT_NS::TestCase
{
  CPPUNIT_TEST_SUITE(TestSolution);
  CPPUNIT_TEST(calculate);
  CPPUNIT_TEST_SUITE_END();

public:
  void setUp(void) {}
  void tearDown(void){}

protected:
  void calculate(void){
    system("");
  }
//  void noRoot();
//  void oneRoot();
//  void twoRoot();
//  void firstCoef();
//  void inPutCorrect();
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestSolution);

//void TestSolution::calculate()
//{
//  CPPUNIT_ASSERT_EQUAL(1,1);
//}

int main()
{
  CPPUNIT_NS::TestResult controller;

  CPPUNIT_NS::TestResultCollector result;
  controller.addListener(&result);

  CPPUNIT_NS::BriefTestProgressListener progress;
  controller.addListener(&progress);

  CPPUNIT_NS::TestRunner runner;
  runner.addTest(CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest());
  runner.run(controller);

  return result.wasSuccessful() ? 0 : 1;
}
