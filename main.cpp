#pragma once
#include <iostream>
#include "EventManager.h"
#include "object.h"

class objectList;
class EventManager;

void execute_moving()
{
    objectList* list = new objectList;
    EventManager* manager = new EventManager;

    int count = 5;
    for(int i = 0; i < count; i++)
    {
        int id = i;
        int velocity = 10 * i;
        int angular = 45 * i;
        int angularVelocity = 0;
        int placeX = list->defaultPlaceX();
        int placeY = list->defaultPlaceY();
        list->add(id, velocity, angular, angularVelocity, placeX, placeY);
        //qDebug() << "addObject:" << list->count();
        //qDebug() << id << "," << velocity << "," << angular << "," << angularVelocity<< "," << placeX<< "," << placeY;
    }

    bool isOk = manager->init(list);
    if(!isOk) return false;

    int timeStep = 1;

    // start timestep
    isOk = manager->appendCommand(list, timeStep);
    if(!isOk) return false;

    // release timestep
    isOk = manager->execute(list, timeStep);
    if(!isOk) return false;

    // end timestep
    isOk = manager->removeCommand(list, timeStep);
    if(!isOk) return false;
}
