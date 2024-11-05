#pragma once
// прямолинейное движение
#include "object.h"

class IMovable
{
public:
    IMovable(int x, int y, double a, int v, int dt);
    ~IMovable();
    void getPosition(object *obj, int dt);
    void getVelocity(object *obj, int value);

private:
    class IMovableP *imp;
};
