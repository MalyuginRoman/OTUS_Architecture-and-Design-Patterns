#include <iostream>
#include "math.h"
#include <cppunit/TestRunner.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>

#include "src/sec/object.h"
#include "src/spe/ioc.h"
#include "src/com/icommand.h"
#include "src/sec/safequeue.h"
#include "src/spe/exceptionhandler.h"
#include "src/spe/eventloop.h"
#include "src/spe/imessage.h"
#include "src/spe/istate.h"
#include "src/sec/objposition.h"
#include "src/sec/producer.h"

class state_test : public CPPUNIT_NS::TestCase
{
CPPUNIT_TEST_SUITE(state_test);
  CPPUNIT_TEST(test1);
CPPUNIT_TEST_SUITE_END();

public:
void setUp(void) {}
void tearDown(void){}

protected:
  void test1(void)
{
//-------------------------------------------------------------
// формируем системы окрестностей
//-------------------------------------------------------------
    std::map<int, system_okr> p_map_c_a;
    std::map<int, system_okr> p_map_c_b;
    p_map_c_a = func_name(1);
    p_map_c_b = func_name(2);
//-------------------------------------------------------------
//   Создаем объекты
//-------------------------------------------------------------
    int count = 1;
    objectVector vector_obj;
    std::cout << std::endl;
    std::cout << "Start create " << count << " objects." << std::endl;

    for(int i = 0; i < count; i++)
    {
        int playerID = i + 1;
        int objectID = playerID * 10 + 1;
        coord place;
        react state;

        place.placeX = 1. + 20. * i;
        if(place.placeX > 100.)
            place.placeX = 100. - (place.placeX - 100.);
        place.placeY = 1. + 25. * i;
        if(place.placeY > 100.)
            place.placeY = 100. - (place.placeY - 100.);
        place.angular = 45 * (i + 1);

        state.velocity = 40;
        state.angularVelocity = 20;
        state.fuel = 10;

        vector_obj.add(id, state, place);
    }

    for(int i = 0; i < count; i++)
    {
        std::cout << vector.at(i)->playerID() << ", " << vector.at(i)->objectID()
                                          << ": u = " << vector.at(i)->state().velocity
                                          << ", v = " << vector.at(i)->state().angularVelocity
                                          << ", f = " << vector.at(i)->state().fuel
                                          << ", x = " << vector.at(i)->place().placeX
                                          << ", y = " << vector.at(i)->place().placeY
                                          << ", a = " << vector.at(i)->place().angular << std::endl;
    }
//-------------------------------------------------------------
// помещаем объекты в системы окресностей
//-------------------------------------------------------------
    p_map_c_a = func_obj(p_map_c_a, &vector);
    p_map_c_b = func_obj(p_map_c_b, &vector);
//-------------------------------------------------------------
//   Общие переменные
//-------------------------------------------------------------
    std::map<std::string, std::function<ICommand*()>> m_map;
    std::map<std::string, std::string> m_scope;
    scope *my_scope = new scope(&m_map, &m_scope);
//-------------------------------------------------------------
//   Регистрация зависимостей в Скоупе (без учета топлива)
//-------------------------------------------------------------
    my_scope = my_scope->fillin(my_scope, p_map_c_a, p_map_c_b, &vector);
//-------------------------------------------------------------
//   Регистрация зависимостей в Скоупе (с учетом топлива)
//-------------------------------------------------------------
    // формируем макрокоманды
    CheckCommand *cmd_check = new CheckCommand();
    BurnCommand *cmd_burn = new BurnCommand();
    MoveCommand *cmd_move = new MoveCommand(&p_map_c_a, &p_map_c_b, vector.at(0));
    RotateCommand *cmd_rotate = new RotateCommand(vector.at(0));
    LogerCommand *cmd_loger = new LogerCommand();
    EmptyCommand *cmd_empty = new EmptyCommand();
    HardStopCommand *cmd_hard = new HardStopCommand();
    SoftStopCommand *cmd_soft = new SoftStopCommand();
    StartMotion *cmd_start = new StartMotion(vector.at(0), vector.at(0)->state().velocity);
    StopMotion *cmd_stop = new StopMotion(vector.at(0));
    ShootCommand *cmd_shoot = new ShootCommand(&vector, vector.at(0));
//-------------------------------------------------------------
    list<ICommand*> cmd_list1, cmd_list2;
    cmd_list1.push_back(cmd_check);
    cmd_list1.push_back(cmd_move);
    cmd_list1.push_back(cmd_burn);

    my_scope->resolve("Scope2",
                    "MacroCommand1",
                    [&cmd_list1]() { return new MacroCommand(cmd_list1); });

    cmd_list2.push_back(cmd_check);
    cmd_list2.push_back(cmd_rotate);
    cmd_list2.push_back(cmd_burn);
    my_scope->resolve("Scope2",
                    "MacroCommand2",
                    [&cmd_list2]() { return new MacroCommand(cmd_list2); });
//-------------------------------------------------------------
    StateStatus *sc = new StateStatus(new DefaultState(), cmd_empty);
    SafeQueue<ICommand*> queueCmds1, queueCmds2, queueCmds3, queueCmds4, queueCmds5;
    eventloop* game1 = new eventloop(&queueCmds1, sc);
    eventloop* game2 = new eventloop(&queueCmds2, sc);
    eventloop* game3 = new eventloop(&queueCmds3, sc);
    eventloop* game4 = new eventloop(&queueCmds4, sc);
    eventloop* game5 = new eventloop(&queueCmds5, sc);
//-------------------------------------------------------------
    queueCmds1.push(cmd_start);
    queueCmds1.push(cmd_move);
    queueCmds1.push(cmd_shoot);
    queueCmds1.push(cmd_rotate);
    queueCmds1.push(cmd_stop);
    queueCmds1.push(cmd_empty);
    queueCmds1.push(cmd_hard);

    queueCmds2.push(cmd_start);
    queueCmds2.push_list(cmd_list1);
    queueCmds2.push(cmd_empty);
    queueCmds2.push(cmd_loger);
    queueCmds2.push_list(cmd_list2);
    queueCmds2.push(cmd_soft);
    queueCmds2.push(cmd_stop);

    game1->start(&queueCmds1, sc, 1);  // потоки создаются внутри eventloop'а

    game2->start(&queueCmds2, sc, 1);

//-------------------------------------------------------------
std::cout << "==========================================================================" << std::endl;
    orderVector message;
    std::list<ICommand*> cmds;
    message.add(1, 11, "StartMove", "InitialVelocity = 2");
    count = message.count() - 1;
    std::cout << message.at(count)->playerID()   << " " << message.at(count)->objectID() << " "
              << message.at(count)->actionName() << " " << message.at(count)->specParam() << std::endl;
//-------------------------------------------------------------
    int current_obj = -1;
    for(int i = 0; i < vector.count(); i++)
    {
        if(message.at(count)->objectID() == vector.at(i)->objectID())
        {
            current_obj = i;
            break;
        }
    }
    if(current_obj != -1)
    {
        InternetCommand* int_cmd = new InternetCommand(&vector, vector.at(current_obj),
                                                        message.at(count), cmds);
//        my_scope->resolve("Scope2",
//                        "StartMove",
//                        [&vector, &current_obj, &message, &count, &cmds]()
//                        { return new InternetCommand(&vector, vector.at(current_obj),
//                                                            message.at(count), cmds); });
        if(int_cmd->create())
            int_cmd->execute();
//        queueCmds3.push_list(int_cmd->cmds);
//        game3->start(&queueCmds3, sc, 1);
    }
    else
    {
        std::cout << "Object with ID " << message.at(count)->objectID() << "is not found!!!" << std::endl;
    }
//-------------------------------------------------------------
    message.add(1, 21, "StopMove", " ");
    count = message.count() - 1;
    std::cout << message.at(count)->playerID()   << " " << message.at(count)->objectID() << " "
              << message.at(count)->actionName() << " " << message.at(count)->specParam() << std::endl;
//-------------------------------------------------------------
    current_obj = -1;
    for(int i = 0; i < vector.count(); i++)
    {
        if(message.at(count)->objectID() == vector.at(i)->objectID())
        {
            current_obj = i;
            break;
        }
    }
    if(current_obj != -1)
    {
        InternetCommand* int_cmd = new InternetCommand(&vector, vector.at(current_obj),
                                                        message.at(count), cmds);
        if(int_cmd->create())
            int_cmd->execute();
    }
    else
    {
        std::cout << "Object with ID " << message.at(count)->objectID() << "is not found!!!" << std::endl;
    }
//-------------------------------------------------------------
    message.add(1, 11, "Shoot", " ");
    count = message.count() - 1;
    std::cout << message.at(count)->playerID()   << " " << message.at(count)->objectID() << " "
              << message.at(count)->actionName() << " " << message.at(count)->specParam() << std::endl;
//-------------------------------------------------------------
    current_obj = -1;
    for(int i = 0; i < vector.count(); i++)
    {
        if(message.at(count)->objectID() == vector.at(i)->objectID())
        {
            current_obj = i;
            break;
        }
    }
    if(current_obj != -1)
    {
        InternetCommand* int_cmd = new InternetCommand(&vector, vector.at(current_obj),
                                                        message.at(count), cmds);
        if(int_cmd->create())
            int_cmd->execute();
    }
    else
    {
        std::cout << "Object with ID " << message.at(count)->objectID() << "is not found!!!" << std::endl;
    }
//-------------------------------------------------------------

    delete sc;
}
};

CPPUNIT_TEST_SUITE_REGISTRATION(state_test);

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
