#pragma once
#include <math.h>

std::array<double, 5> params = {0, 1, 2, 3, 4};

double exampleFunction(double x, double y)
{
    return 0;
}

double exampleFunction2(double x, double y)
{
    return pow(x, 2) + pow(y, 2);
}

double exampleFunction3(double x, double y)
{
    return -pow(x, 2) + pow(y, 2);
}

double exampleFunction4(double x, double y)
{
    return -pow(x, 2) - pow(y, 2);
}

double exampleFunction5(double x, double y)
{
    return sin(x) + sin(y);
}

ContinuousPlane funcNum(int n)
{
    ContinuousPlane cp;
    if(n == 0)
        cp.setFunction(exampleFunction);
    if(n == 1)
        cp.setFunction(exampleFunction2);
    if(n == 2)
        cp.setFunction(exampleFunction3);
    if(n == 3)
        cp.setFunction(exampleFunction4);
    if(n==4)
        cp.setFunction(exampleFunction5);
    return cp;
}
