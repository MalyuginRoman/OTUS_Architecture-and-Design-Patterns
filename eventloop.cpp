#include "eventloop.h"

class eventloopP
{
public:
    SafeQueue<ICommand *> *cmds;
    StateStatus *status;
    eventloopP(SafeQueue<ICommand *> *cmds, StateStatus *status) :
        cmds(cmds),
        status(status)
    {
    }
};

eventloop::eventloop(SafeQueue<ICommand *> *cmds, StateStatus *status) :
    imp(new eventloopP(cmds, status))
{
}


eventloop::~eventloop() { delete imp; }

void eventloop::start(SafeQueue<ICommand *> *cmds, StateStatus *status, int variant)
{
    bool stop = false;
    int ic = 0;
    SafeQueue<ICommand*> cmds_1;
    EmptyCommand *cmd_empty = new EmptyCommand();
    HardStopCommand *cmd_hard = new HardStopCommand();
    SoftStopCommand *cmd_soft = new SoftStopCommand();
    
    std::exception ex;
    ExceptionHandler* handler = new ExceptionHandler(0, ex);
    
    std::thread t1(
                [&cmds, &stop, &ic, &variant, &cmd_empty, &cmd_hard, &cmd_soft, &ex, &handler](){
        try {
              while(!stop)
              {
                  ic += 1;
                  ICommand* cmd = cmds->front();
                  execute(cmd);
                  cmds->pop();
                  if(cmd == cmd_hard)
                  {
                      stop = true;
                      std::cout << "in queue after HardStop : " << std::endl;
                      status->execute(cmd);
                      while(!cmds->empty())
                      {
                          ICommand* cmdh = cmds->front();
                          cmdh->execute();
                          cmds->pop();
                          if(cmds->size() > 0)
                              std::cout << ", ";
                      }
                      std::cout << std::endl;
                  }
                  if(cmd == cmd_soft)
                  {
                      stop = true;
                      while(!cmds->empty())
                      {
                          std::cout << cmds->size() << " -> " << cmds_1.size() << std::endl;
                          ICommand* cmdss = cmds->front();
                          cmds_1.push(cmdss);
                          cmds->pop();
                      }
                      while(!cmds_1.empty())
                      {
                          ICommand* cmds = cmds_1.front();
                          cmds->execute();
                          cmds_1.pop();
                      }
                  }
                  if(cmds->empty())
                      stop = true;
                  if(ic == 2) cmds->push(cmd_empty);
                  if(variant == 1 && ic == 3) cmds->push(cmd_soft);
                  if(variant == 2 && ic == 4) cmds->push(cmd_hard);
              }
        } catch( std::exception ex) {
            handler->executeRepeat(handler, cmds, ex);
        }
    });
    t1.join();
}

void eventloop::execute(ICommand *cmd)
{
    std::cout << "Start execute ";
    cmd->execute();
    std::cout << std::endl;
}
