#include <iostream>
#include "math.h"
#include <cppunit/TestRunner.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>

#include "config.h"

class test_macrocommand : public CPPUNIT_NS::TestCase
{
CPPUNIT_TEST_SUITE(test_macrocommand);
  CPPUNIT_TEST(test1);
  CPPUNIT_TEST(test2);
CPPUNIT_TEST_SUITE_END();

public:
void setUp(void) {}
void tearDown(void){}

protected:
// Реализовать класс CheckFuelComamnd и тесты к нему.
  void test1(void)
{
    objectVector vector;
    {
        int id = 0;
        coord place;
        react state;

        place.placeX = 0.;
        place.placeY = 0.;
        place.angular = 45;

        state.velocity = 100;
        state.angularVelocity = 20;
        state.fuel = 10;

        vector.add(id, state, place);
    }
  
    CommandQueue cmd;
    CommandFuelCheck *cmd_check = new CommandFuelCheck(vector.at(0));
    CommandMove *cmd_move = new CommandMove(vector.at(0));
    CommandRotate *cmd_rotate = new CommandRotate(vector.at(0));
    std::exception ex;
    ExceptionHandler* handler = new ExceptionHandler(0, ex);

    cmd.add(cmd_check);
    cmd.add(cmd_move);
    cmd.add(cmd_rotate);

    std::cout << std::endl;
    while(!cmd.isEmpty())
    {
        try {
            cmd.front()->execute();
        } catch( std::exception ex) {
            handler->executeWrite(&cmd, cmd.front(), ex);
        }
        cmd.del();
    }
    std::cout << std::endl;
}
// Реализовать класс BurnFuelCommand и тесты к нему.
  void test2(void)
{
    objectVector vector;
    {
        int id = 0;
        coord place;
        react state;

        place.placeX = 0.;
        place.placeY = 0.;
        place.angular = 45;

        state.velocity = 100;
        state.angularVelocity = 20;
        state.fuel = 10;

        vector.add(id, state, place);
    }
  
    CommandQueue cmd;
    CommandFuelCheck *cmd_check = new CommandFuelCheck(vector.at(0));
    CommandMove *cmd_move = new CommandMove(vector.at(0));
    CommandRotate *cmd_rotate = new CommandRotate(vector.at(0));
    CommandFuelBurn *cmd_burn = new CommandFuelBurn(vector.at(0));
    std::exception ex;
    ExceptionHandler* handler = new ExceptionHandler(0, ex);

    cmd.add(cmd_check);
    cmd.add(cmd_move);
    cmd.add(cmd_burn);
    cmd.add(cmd_rotate);
    cmd.add(cmd_burn);

    std::cout << std::endl;
    while(!cmd.isEmpty())
    {
        try {
            cmd.front()->execute();
        } catch( std::exception ex) {
            handler->executeWrite(&cmd, cmd.front(), ex);
        }
        cmd.del();
    }
    std::cout << std::endl;
}
};

CPPUNIT_TEST_SUITE_REGISTRATION(test_macrocommand);

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
