#pragma once
#include "icommand.h"
#include <queue>

class SafeQueue
{
public:
    void add(ICommand* c)
    {
        cmd.push(c);
    };
    void del()
    {
        cmd.pop();
    };
    size_t size()
    {
        return cmd.size();
    };
    bool isEmpty()
    {
        return cmd.empty();
    };
    ICommand* front()
    {
        return cmd.front();
    };
private:
    std::queue<ICommand*> cmd;
};
