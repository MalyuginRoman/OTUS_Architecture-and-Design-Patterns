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
                [&ioc, &queueCmds, &queueCmds_1, &stop, &ic, &cmd_empty, &cmd_hard, &cmd_soft](){
        while(!stop)
        {
            ICommand* cmd = queueCmds.front();;
            cmd->execute();
            queueCmds.pop();
            if(cmd == cmd_hard)
            {
                stop = true;
                std::cout << "in queue after HardStop : " << std::endl;
                while(!queueCmds.empty())
                {
                    ICommand* cmdh = queueCmds.front();
                    cmdh->execute();
                    queueCmds.pop();
                }
            }
            if(cmd == cmd_soft)
            {
                stop = true;
                std::cout << "in queue after SoftStop : " << std::endl;
                while(!queueCmds.empty())
                {
                    ICommand* cmds = queueCmds.front();
                    queueCmds_1.push(cmds);
                    queueCmds.pop();
                }
                while(!queueCmds_1.empty())
                {
                    ICommand* cmds = queueCmds_1.front();
                    cmds->execute();
                    queueCmds_1.pop();
                }
            }
            if(queueCmds.empty())
                stop = true;
            if(ic == 2) queueCmds.push(cmd_empty);
            if(ic == 3) queueCmds.push(cmd_soft);
            if(ic == 4) queueCmds.push(cmd_hard);
            if(ic == 5) queueCmds.push(cmd_empty);
            if(ic == 6) queueCmds.push(cmd_empty);
            if(ic == 7) queueCmds.push(cmd_empty);
        }
    });
    t1.join();
}
