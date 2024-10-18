#include <iostream>
#include "math.h"
#include <cppunit/TestRunner.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>

const double e = 1E-07;

class TestSolution : public CPPUNIT_NS::TestCase
{
CPPUNIT_TEST_SUITE(TestSolution);
  CPPUNIT_TEST(testEquationSolution);
  CPPUNIT_TEST(calculate);
CPPUNIT_TEST_SUITE_END();

public:
void setUp(void) {}
void tearDown(void){}

protected:
  void testEquationSolution(void) {
    system("0");
  }
  void calculate(void)
{
  double x = root(1, 2, 1, false);
  double result = 1.;
  CPPUNIT_ASSERT((x - result) < e);
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
//  CPPUNIT_ASSERT_EQUAL();
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
