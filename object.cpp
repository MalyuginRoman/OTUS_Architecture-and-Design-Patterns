#include "object.h"

class objectP
{
public:
    int id;
    int velocity;
    double angular;
    int placeX;
    int placeY;
    objectP(int id, int velocity, double angular, int placeX, int placeY) :
        id(id),
        velocity(velocity),
        angular(angular),
        placeX(placeX),
        placeY(placeY)
    {
    }
};

object::object(int id, int velocity, double angular, int placeX, int placeY) :
    imp(new objectP(id, velocity, angular, placeX, placeY))
{
}
object::~object()
{
    delete imp;
}
int object::id() const
{
    return imp->id;
}
int object::velocity() const
{
    return imp->velocity;
}
double object::angular() const
{
    return imp->angular;
}
int object::placeX() const
{
    return imp->placeX;
}
int object::placeY() const
{
    return imp->placeY;
}
void object::setVelocity(int value)
{
    imp->velocity = value;
}
void object::setAngular(double value)
{
    imp->angular = value;
}
void object::setPlaceX(int value)
{
    imp->placeX = value;
}
void object::setPlaceY(int value)
{
    imp->placeY = value;
}

class objectListP
{
public:
    std::list<object*> list;
    int defaultVelocity;
    double defaultAngular;
    int defaultPlaceX;
    int defaultPlaceY;

    objectListP():
        defaultVelocity(0),
        defaultAngular(0.),
        defaultPlaceX(0),
        defaultPlaceY(0)
    {
    }
    ~objectListP()
    {
        list.clear();
    }
    void reset()
    {
        list.clear();
    }
    object *add(int id, int velocity, double angular, int placeX, int placeY)
    {
        object* spaceship = new object(id, velocity, angular, placeX, placeY);
        list.push_back(spaceship);
        return spaceship;
    }
};
objectList::objectList() : imp(new objectListP)
{
}
objectList::~objectList()
{
    delete imp;
}
void objectList::reset()
{
    imp->reset();
}
int objectList::defaultVelocity() const
{
    return imp->defaultVelocity;
}
double objectList::defaultAngular() const
{
    return imp->defaultAngular;
}
int objectList::defaultPlaceX() const
{
    return imp->defaultPlaceX;
}
int objectList::defaultPlaceY() const
{
    return imp->defaultPlaceY;
}
void objectList::setDefaultVelocity(int value)
{
    imp->defaultVelocity = value;
}
void objectList::setDefaultAngular(double value)
{
    imp->defaultAngular = value;
}
void objectList::setDefaultPlaceX(int value)
{
    imp->defaultPlaceX = value;
}
void objectList::setDefaultPlaceY(int value)
{
    imp->defaultPlaceY = value;
}
object *objectList::add(int id, int velocity, double angular, int placeX, int placeY)
{
    return imp->add(id, velocity, angular, placeX, placeY);
}
bool objectList::isEmpty() const
{
    return imp->list.empty();
}
int objectList::count() const
{
    return imp->list.size();
}
const std::list<object *> &objectList::list() const
{
    return imp->list;
}
