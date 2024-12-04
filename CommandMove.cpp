#include <iostream>
#include "CommandMove.h"
using namespace std;

class CommandMoveP
{
public:
    object* obj;

    CommandMoveP(object* obj) :
        obj(obj)
    {
    }
};

CommandMove::CommandMove(object* obj) :
    imp(new CommandMoveP(obj))
{
    this->getStr("CommandMove");
}

CommandMove::~CommandMove() { delete imp;}

void CommandMove::execute()
{
    cout << "Start execute of CommandMove" << endl;
    if(imp->obj->place().placeX < 0 && imp->obj->place().placeY < 0)
        throw runtime_error ("Object not found");
    if(!imp->obj->getVelocity(imp->obj, 0))
        throw runtime_error ("Unknown velocity");
    cout << "Coord before using command [" << imp->obj->place().placeX << ";" << imp->obj->place().placeY << "]" << endl;
    if(!imp->obj->getPosition(imp->obj, dt))
        throw std::runtime_error ("Unknown position");
    cout << "Coord after using command [" << imp->obj->place().placeX << ";" << imp->obj->place().placeY << "]" << endl;
}

void CommandMove::getStr(string value)
{
    this->str = value;
}

string CommandMove::setStr()
{
    return this->str;
}

object* CommandMove::obj() const
{
    return imp->obj;
}
