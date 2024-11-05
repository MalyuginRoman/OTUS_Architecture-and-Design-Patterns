#pragma once
// Поворот
#include "object.h"

class IRotable
{
public:
    IRotable(int x, int y, double a);
    ~IRotable();
    void getAngular(object *obj, int value);

private:
    class IRotableP *imp;
};
