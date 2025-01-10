#include <iostream>
#include "math.h"
#include <cppunit/TestRunner.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>

#include "producer.h"

class endpoint_test : public CPPUNIT_NS::TestCase
{
CPPUNIT_TEST_SUITE(endpoint_test);
  CPPUNIT_TEST(test1);
CPPUNIT_TEST_SUITE_END();

public:
void setUp(void) {}
void tearDown(void){}

protected:
  void test1(void)
{
    objectVector vector;
    int count = 2;
    for(int i = 0; i < count; i++)
    {
        int id = i;
        coord place;
        react state;

        place.placeX = 0.;
        place.placeY = 0.;
        place.angular = 45 * i;

        state.velocity = 100;
        state.angularVelocity = 20;
        state.fuel = 10;

        vector.add(id, state, place);
    }

    for(int i = 0; i < count; i++)
    {
        std::cout << vector.at(i)->id() << ":" << vector.at(i)->state().velocity << "," << vector.at(i)->state().angularVelocity << "," << vector.at(i)->state().fuel
                       << "," << vector.at(i)->place().placeX << "," << vector.at(i)->place().placeY << "," << vector.at(i)->place().angular << std::endl;
    }

    Message* m1 = new Message(1, 1, 1, vector.at(0));

    Builder* b1 = new Builder;
    b1->setGameId(1);
    b1->setObjectId(1);
    b1->setOperationId(1);
    b1->setArgs(vector.at(0));

    IocContainer<ICommand> ioc;
    SafeQueue queueCmds;

    // Scope2 with fuel
    // формируем макрокоманды
    CheckCommand *cmd_check = new CheckCommand();
    MoveCommand *cmd_move = new MoveCommand();
    RotateCommand *cmd_rotate = new RotateCommand();
    BurnCommand *cmd_burn = new BurnCommand();
    std::exception ex;
    ExceptionHandler* handler = new ExceptionHandler(0, ex);
    queueCmds.add(cmd_check);
    queueCmds.add(cmd_move);
    queueCmds.add(cmd_burn);
    queueCmds.add(cmd_check);
    queueCmds.add(cmd_rotate);
    queueCmds.add(cmd_burn);
    eventloop* producer = new eventloop(&queueCmds);

    std::thread t1(
                [&ioc, &producer, &queueCmds, &handler, &ex](){
        try {
            producer->start(&queueCmds);
        } catch( std::exception ex) {
            handler->executeRepeat(handler, &queueCmds, ex);
        }
    });
    t1.join(); /**/
}
};

CPPUNIT_TEST_SUITE_REGISTRATION(endpoint_test);

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
