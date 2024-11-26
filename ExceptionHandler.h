#pragma once
#include <iostream>
#include "ICommand.h"
#include "CommandQueue.h"

class ExceptionHandler
{
public:
    ExceptionHandler(ICommand* cmd, std::exception ex);

    ICommand* cmd() const;
    std::exception ex() const;

    void executeWrite(CommandQueue* cmd, ICommand* com, std::exception ex);
    void executeRepeat(ExceptionHandler* handler, CommandQueue* cmd, ICommand* com, std::exception ex);
private:
    class ExceptionHandlerP* imp;
};
