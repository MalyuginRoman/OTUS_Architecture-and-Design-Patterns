#pragma once
#include <iostream>
#include <thread>
#include "ioc.h"
#include "icommand.h"
#include "object.h"
#include "safequeue.h"

void test_thread1()
{
    std::cout << "Start test_thread1" << std::endl;
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

    IocContainer<ICommand> ioc;
    SafeQueue<ICommand*> queueCmds;
    SafeQueue<ICommand*> queueCmds_1;

    // Scope2 with fuel
    // формируем макрокоманды
    CheckCommand *cmd_check = new CheckCommand();
    MoveCommand *cmd_move = new MoveCommand();
    RotateCommand *cmd_rotate = new RotateCommand();
    BurnCommand *cmd_burn = new BurnCommand();
    EmptyCommand *cmd_empty = new EmptyCommand();
    HardStopCommand *cmd_hard = new HardStopCommand();
    SoftStopCommand *cmd_soft = new SoftStopCommand();

    bool stop = false;
    int ic = 0;

    queueCmds.push(cmd_check);
    queueCmds.push(cmd_move);
    queueCmds.push(cmd_burn);
    queueCmds.push(cmd_check);
    queueCmds.push(cmd_rotate);
    queueCmds.push(cmd_burn);
    std::thread t1(
                [&ioc, &producer, &queueCmds, &handler, &ex](){
        try {
            producer->start(&queueCmds);
        } catch( std::exception ex) {
            handler->executeRepeat(handler, &queueCmds, ex);
        }
    });
    t1.join();
}
