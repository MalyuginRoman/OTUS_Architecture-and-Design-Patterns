#include <iostream>
#include "CommandRotate.h"
using namespace std;

class CommandRotateP
{
public:
    object* obj;

    CommandRotateP(object* obj) :
        obj(obj)
    {
    }
};

CommandRotate::CommandRotate(object* obj) :
    imp(new CommandRotateP(obj))
{
    this->getStr("CommandRotate");
}

CommandRotate::~CommandRotate() { delete imp;}

void CommandRotate::execute()
{
    cout << "Start execute of CommandRotate" << endl;
    if(imp->obj->place().placeX < 0 && imp->obj->place().placeY < 0)
        throw runtime_error ("Object not found");
    if(!imp->obj->getAngularVelocity(imp->obj, 0))
        throw runtime_error ("Unknown angular velocity");
    cout << imp->obj->place().angular << endl;
    if(!imp->obj->getAngular(imp->obj, dt))
        throw runtime_error ("Unknown position");
    cout << imp->obj->place().angular << endl;
}

void CommandRotate::getStr(string value)
{
    this->str = value;
}

string CommandRotate::setStr()
{
    return this->str;
}

object* CommandRotate::obj() const
{
    return imp->obj;
}
