#pragma once
#include <map>
#include <string>
#include "ICommand.h"

class scope
{
public:
    scope();

    std::map<std::string, ICommand*> CurrentScope;
    void insert(const std::string key, const ICommand* value);
    void clear();
    bool isEmpty();
    ICommand* at(std::string key);
};
