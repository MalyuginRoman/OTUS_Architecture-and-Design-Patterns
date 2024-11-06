#include "MoveCommand.h"
#include "math.h"

const double TR = 0.01745329252;

class MoveCommandP
{
public:
    int x;
    int y;
    int v;
    double a1;
    double a2;
    int dt;
    MoveCommandP(int x, int y, double a1, double a2, int v, int dt) :
        x(x),
        y(y),
        a1(a1),
        a2(a2),
        v(v),
        dt(dt)
    {
    }
};

MoveCommand::MoveCommand(int x, int y, double a1, double a2, int v, int dt) :
                         imp(new MoveCommandP(x, y, a1, a2, v, dt))
{ }

bool MoveCommand::getPosition(object *obj, int dt)
{
    obj->setPlaceX(obj->velocity() * cos(obj->angular()*TR) * dt);
    obj->setPlaceY(obj->velocity() * sin(obj->angular()*TR) * dt);
    return true;
}

bool MoveCommand::setPosition(object *obj)
{
    obj->placeX();
    obj->placeY();
    return true;
}
bool MoveCommand::getVelocity(object *obj, int du)
{
    obj->setVelocity(obj->velocity() + du);
    return true;
}
bool MoveCommand::setVelocity(object *obj)
{
    obj->velocity();
    return true;
}
