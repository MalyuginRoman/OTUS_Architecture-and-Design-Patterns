#include <iostream>
#include <thread>
#include "ioc.h"
#include "icommand.h"
#include "object.h"
#include "safequeue.h"
#include "exceptionhandler.h"
#include "eventloop.h"
#include "imessage.h"
#include <thread>
using namespace std;

int main(int ac, char **av)
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
        cout << vector.at(i)->id() << ":" << vector.at(i)->state().velocity << "," << vector.at(i)->state().angularVelocity << "," << vector.at(i)->state().fuel
                       << "," << vector.at(i)->place().placeX << "," << vector.at(i)->place().placeY << "," << vector.at(i)->place().angular << endl;
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
    t1.join();


    return 0;
}
