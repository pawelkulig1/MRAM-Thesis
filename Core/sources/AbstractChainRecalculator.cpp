#include "AbstractChainRecalculator.h"
#include "Point.h"
#include <math.h>


double AbstractChainRecalculator::distanceBetweenPoints2D(Point *p1, Point *p2)
{
    return sqrt(pow(p1->getX() - p2->getX(), 2) + 
                pow(p1->getY() - p2->getY(), 2));
}

double AbstractChainRecalculator::distanceBetweenPoints3D(Point *p1, Point *p2)
{
    return sqrt(pow(p1->getX() - p2->getX(), 2) + 
                pow(p1->getY() - p2->getY(), 2) +
                pow(p1->getZ() - p2->getZ(), 2));
}
                

