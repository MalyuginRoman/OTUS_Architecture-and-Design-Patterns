#include <iostream>
#include "math.h"

const double e = 1E-07;

double discr(double a, double b, double c)
{
    return b * b - 4.0 * a * c;
}

int root(double a, double b, double d, bool i)
{
    if(i == false)
        return (-b + sqrt(d) / (2 * a));
    else
        return (-b - sqrt(d) / (2 * a));
}

int main(int ac, char **av)
{
    std::cout << "Solution of a quadratic equation" << std::endl;
    double a, b, c;

    std::cout << "Enter the coefficient of the quadratic equation:" << std::endl;
    std::cin >> a;
    std::cin >> b;
    std::cin >> c;

    if(abs(a) < e)
        std::cout << "The equation is not quadratic." << std::endl;
    else
    {
        double d = discr(a, b, c);
        std::cout << "d = " << d << std::endl;
        if(d < 0.0)
            std::cout << "The equation has no real roots." << std::endl;
        else
        {
            double x;
            if(abs(d) < e)
            {
                std::cout << "The equation has one real roots:" << std::endl;
                x = root(a, b, d, false);
                std::cout << x << std::endl;
            }
            else
            {
                std::cout << "The equation has two real roots:" << std::endl;
                x = root(a, b, d, false);
                std::cout << x << ", ";
                x = root(a, b, d, true);
                std::cout << x << std::endl;
            }
        }
    }
}
