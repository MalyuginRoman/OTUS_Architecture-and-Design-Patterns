#pragma once
#include <iostream>
#include "icommand.h"
#include "safequeue.h"

class eventloop
{
public:
    eventloop(SafeQueue *cmds);
    ~eventloop();

    SafeQueue *cmds;

    void start(SafeQueue *cmds);
private:
    class eventloopP* imp;
};
