#include "eventloop.h"

class eventloopP
{
public:
    SafeQueue *cmds;
    eventloopP(SafeQueue *cmds) :
        cmds(cmds)
    {
    }
};

eventloop::eventloop(SafeQueue *cmds) :
    imp(new eventloopP(cmds))
{
}


eventloop::~eventloop() { delete imp; }

void eventloop::start(SafeQueue *cmds)
{
    std::cout << "I am here!" << std::endl;
    bool stop = false;
    int ic = 0;
    SafeQueue cmds_1;
    EmptyCommand *cmd_empty = new EmptyCommand();
    HardStopCommand *cmd_hard = new HardStopCommand();
    SoftStopCommand *cmd_soft = new SoftStopCommand();
    while(!stop)
    {
        ic += 1;
        ICommand* cmd = cmds->front();
        cmd->execute();
        cmds->del();
        /*if(cmd == cmd_hard)
        {
            stop = true;
            std::cout << "in queue after HardStop : " << std::endl;
            while(!cmds->empty())
            {
                ICommand* cmdh = cmds->front();
                cmdh->execute();
                cmds->pop();
            }
        }*/
        if(cmd == cmd_soft)
        {
            stop = true;
            while(!cmds->isEmpty())
            {
                std::cout << cmds->size() << " -> " << cmds_1.size() << std::endl;
                ICommand* cmdss = cmds->front();
                cmds_1.add(cmdss);
                cmds->del();
            }
            while(!cmds_1.isEmpty())
            {
                ICommand* cmds = cmds_1.front();
                cmds->execute();
                cmds_1.del();
            }
        }
        if(cmds->isEmpty())
            stop = true;
        if(ic == 2) cmds->add(cmd_empty);
        if(ic == 3) cmds->add(cmd_soft);
        if(ic == 4) cmds->add(cmd_hard);
        if(ic == 5) cmds->add(cmd_empty);
        if(ic == 6) cmds->add(cmd_empty);
        if(ic == 7) cmds->add(cmd_empty);
    } /**/
}
