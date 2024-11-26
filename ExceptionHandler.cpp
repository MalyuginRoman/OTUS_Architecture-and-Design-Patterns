#include "ExceptionHandler.h"
#include "CommandLoger.h"

class ExceptionHandlerP
{
public:
    ICommand* cmd;
    std::exception ex;
    ExceptionHandlerP(ICommand* cmd, std::exception ex) :
        cmd(0),
        ex(ex)
    {
    }
};

ExceptionHandler::ExceptionHandler(ICommand* cmd, std::exception ex) :
    imp(new ExceptionHandlerP(cmd, ex))
{
}

void ExceptionHandler::executeRepeat(ExceptionHandler* handler, CommandQueue* cmd, ICommand* com, std::exception ex)
{
    std::cout << "Repeat execute of ExceptionHandler" << ex.what() << std::endl;
    cmd->add(com);
    cmd->del();
    try {
        cmd->front()->execute();
        cmd->del();
    } catch( std::exception ex1) {
        handler->executeWrite(cmd, cmd->front(), ex1);
    }
}

void ExceptionHandler::executeWrite(CommandQueue* cmd, ICommand* com, std::exception ex)
{
    std::cout << "Write execute of ExceptionHandler" << ex.what() << std::endl;
    CommandLoger *cmd_loger = new CommandLoger;
    cmd_loger->execute();
    cmd->del();
}
