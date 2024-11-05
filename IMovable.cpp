// прямолинейное движение
#include "IMovable.h"
#include "math.h"

const double TR = 0.01745329252;

class IMovableP
{
public:
    int x;
    int y;
    int v;
    double a;
    int dt;
    IMovableP(int x, int y, double a, int v, int dt) :
        x(x),
        y(y),
        a(a),
        v(v),
        dt(dt)
    {
    }
};

IMovable::IMovable(int x, int y, double a, int v, int dt) :
    imp(new IMovableP(x, y, a, v, dt))
{
}

IMovable::~IMovable()
{
    delete imp;
}

void IMovable::getPosition(object *obj, int dt)
{
    obj->setPlaceX(obj->velocity() * cos(obj->angular()*TR) * dt);
    obj->setPlaceY(obj->velocity() * sin(obj->angular()*TR) * dt);
}

void IMovable::getVelocity(object *obj, int value)
{
    obj->setVelocity(value);
}
