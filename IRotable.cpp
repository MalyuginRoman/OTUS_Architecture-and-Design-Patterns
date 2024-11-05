// Поворот
#include "IRotable.h"

class IRotableP
{
public:
    int x;
    int y;
    double a;
    IRotableP(int x, int y, double a) :
        x(x),
        y(y),
        a(a)
    {
    }
};

IRotable::IRotable(int x, int y, double a) :
    imp(new IRotableP(x, y, a))
{
}

IRotable::~IRotable()
{
    delete imp;
}

void IRotable::getAngular(object *obj, int value)
{
    obj->setAngular(value);
}
