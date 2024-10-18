#include <iostream>
#include "math.h"

const double e = 1E-07;

int main(int ac, char **av)
{
    std::cout << "Solution of a quadratic equation" << std::endl;
    double a, b, c;

    std::cout << "Enter the coefficient of the quadratic equation:" << std::endl;
    std::cin >> a;
    std::cin >> b;
    std::cin >> c;

    calc(a, b, c);
}

void calc(double a, double b, double c)
{
    if(abs(a) < e)
        std::cout << "The equation is not quadratic." << std::endl;
    else
    {
        double d = b * b - 4.0 * a * c;
        std::cout << "d = " << d << std::endl;
        if(d < 0.0)
            std::cout << "The equation has no real roots." << std::endl;
        else
        {
            double x;
            if(abs(d) < e)
            {
                std::cout << "The equation has one real roots:" << std::endl;
                x = -b / (2 * a);
                std::cout << x << std::endl;
            }
            else
            {
                std::cout << "The equation has two real roots:" << std::endl;
                x = -b + sqrt(d) / (2 * a);
                std::cout << x << ", ";
                x = -b - sqrt(d) / (2 * a);
                std::cout << x << std::endl;
            }
        }
    }
}
