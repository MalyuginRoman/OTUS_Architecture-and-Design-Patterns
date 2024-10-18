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
