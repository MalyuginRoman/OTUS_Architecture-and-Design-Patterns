#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include "minor.h"
#include "IMoving.h"
#include "IRotatable.h"

class object : public IMoving, IRotatable
{
public:
    object(int id, react state, coord place);
    ~object();

    int id() const;
    react state() const;
    coord place() const;

    void setState(react state);
    void setPlace(coord place);

    bool getPosition(object *obj, int dt);
    bool setPosition(object *obj);
    bool getVelocity(object *obj, int du);
    bool setVelocity(object *obj);

    bool getAngular(object *obj, int dt);
    bool setAngular(object *obj);
    bool getAngularVelocity(object *obj, int dv);
    bool setAngularVelocity(object *obj);

    bool getFuel(object *obj, int dF);

private:
    class objectP* imp;
};

class objectVector
{
public:
    objectVector();
    ~objectVector();
    void reset();

    object* add(int id, react state, coord place);
    bool isEmpty() const;
    size_t count() const;
    const std::vector<object *>& vector() const;
    object* at(int i);
private:
    class objectVectorP* imp;
};

#endif // OBJECT_H
