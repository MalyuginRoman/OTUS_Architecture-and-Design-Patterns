#include "RotateCommand.h"

class RotateCommandP
{
public:
    int x;
    int y;
    int v;
    double a1;
    double a2;
    int dt;
    RotateCommandP(int x, int y, double a1, double a2, int v, int dt) :
        x(x),
        y(y),
        a1(a1),
        a2(a2),
        v(v),
        dt(dt)
    {
    }
};

RotateCommand::RotateCommand(int x, int y, double a1, double a2, int v, int dt) :
    imp(new RotateCommandP(x, y, a1, a2, v, dt))
{ }

bool RotateCommand::getAngular(object *obj, int dt)
{
    obj->setAngular(obj->angular() * obj->angularVelocity() * dt);
    return true;
}

bool RotateCommand::setAngular(object *obj)
{
    obj->angular();
    return true;
}
bool RotateCommand::getAngularVelocity(object *obj, int dv)
{
    obj->setAngularVelocity(obj->angularVelocity() + dv);
    return true;
}
bool RotateCommand::setAngularVelocity(object *obj)
{
    obj->angularVelocity();
    return true;
}
