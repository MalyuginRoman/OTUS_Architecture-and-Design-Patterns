#include <iostream>
#include "math.h"
#include "config.h"

struct root
{
    double x1;
    double x2;
}

int main(int ac, char **av)
{
    std::cout << "Solution of a quadratic equation" << std::endl;
    double a, b, c;

    std::cout << "Enter the coefficient of the quadratic equation:" << std::endl;
    std::cin >> a;
    std::cin >> b;
    std::cin >> c;

    solve(a, b, c);
}
