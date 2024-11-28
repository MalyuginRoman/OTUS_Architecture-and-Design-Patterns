#ifndef COMMANDFUELBURN_H
#define COMMANDFUELBURN_H
#include "ICommand.h"
#include "object.h"
#include <string>

class CommandFuelBurn : public ICommand
{
public:
    CommandFuelBurn(object* obj);
    ~CommandFuelBurn();

    object* obj() const;

    void execute();
    void getStr(std::string value);
    std::string setStr();
private:
    std::string str;
    class CommandFuelBurnP* imp;
};

#endif // COMMANDFUELBURN_H
