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
#include <filesystem>

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
      std::cout << std::endl;
      std::cout << "Start test" << std::endl;

      std::filesystem::path current_path = std::filesystem::current_path();
      std::filesystem::path file_path(current_path);

      cout << file_path.parent_path() << endl;

      for (auto &p : std::filesystem::recursive_directory_iterator(file_path.parent_path()))
        {
          if(p.path().extension() == ".h")
          {
            std::cout << p.path().parent_path() << " _ " << p.path().filename() << std::endl;
            
            std::string readFileName = p.path().parent_path().generic_string() + "/" +
                                  p.path().filename().generic_string();
            fstream readFile(readFileName);
            if (!readFile.is_open())
            {
                std::cout << "File " << readFileName << " not be opened" << std::endl;
            }
            else
            {
                std::string str;
                while(readFile >> str)
                {
                    std::cout << str << std::endl;
                }
            }
            readFile.close();
          }
        }
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION(test_adapter);/**/

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
/*  return 0;*/
}
