#include "scope.h"

scope::scope()
{}

void scope::insert(std::string key, ICommand* value)
{
    CurrentScope.emplace(std::make_pair(key, value));
}

void scope::clear()
{
    CurrentScope.clear();
}

bool scope::isEmpty()
{
    return CurrentScope.empty();
}

ICommand* scope::at(std::string key)
{
    return CurrentScope.at(key);
}
