#pragma once
#include "QString"

class LogeCommand
{
public:
    LogeCommand(int actionID, QString text);

private:
    class LogeCommandP *imp;
};
