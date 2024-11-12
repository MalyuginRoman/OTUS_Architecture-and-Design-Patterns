#pragma once
#include "object.h"

class EventManager
{
public:
    EventManager();
    ~EventManager();

    bool init(objectList* list);
    bool appendCommand(objectList* list, int timeStep);
    bool execute(objectList* list, int timeStep);
    bool removeCommand(objectList* list, int timeStep);

private:
    class EventManagerP* imp;
};
