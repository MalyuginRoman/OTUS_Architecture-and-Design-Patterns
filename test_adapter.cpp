#include <iostream>
#include "math.h"
#include <cppunit/TestRunner.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>

#include "ioc.h"
#include "icommand.h"
#include "object.h"

class test_adapter : public CPPUNIT_NS::TestCase
{
CPPUNIT_TEST_SUITE(test_adapter);
  CPPUNIT_TEST(test1);
CPPUNIT_TEST_SUITE_END();

public:
void setUp(void) {}
void tearDown(void){}

protected:
  void test1(void)
    {
      std::cout << "Start test" << std::endl;
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION(test_adapter);

int main()
{
CPPUNIT_NS::TestResult controller;

/*CPPUNIT_NS::TestResultCollector result;
controller.addListener(&result);

CPPUNIT_NS::BriefTestProgressListener progress;
controller.addListener(&progress);

CPPUNIT_NS::TestRunner runner;
runner.addTest(CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest());
runner.run(controller);

return result.wasSuccessful() ? 0 : 1;*/
  return 0;
}
