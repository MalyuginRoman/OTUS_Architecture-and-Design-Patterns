#pragma once
#include <string>

class LogeCommand
{
public:
    LogeCommand(int actionID, std::string text);

private:
    class LogeCommandP *imp;
};
