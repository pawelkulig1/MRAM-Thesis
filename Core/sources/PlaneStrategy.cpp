#include "PlaneStrategy.h"
#include "AbstractPlane.h"
#include "Point.h"

PlaneStrategy *PlaneStrategy::instance = nullptr;

void PlaneStrategy::setStrategy(AbstractPlane *pl)
{
    PlaneStrategy::strategy = pl;
}

PlaneStrategy *PlaneStrategy::getInstance()
{
    if(PlaneStrategy::instance == nullptr)
        PlaneStrategy::instance = new PlaneStrategy();
    return PlaneStrategy::instance;
}

AbstractPlane *PlaneStrategy::getStrategy()
{
    return PlaneStrategy::strategy;
}

Eigen::Vector3d PlaneStrategy::calculateDerivative(double x, double y)
{
    return strategy->calculateDerivative(x, y);
}

Eigen::Vector3d PlaneStrategy::calculateDerivative(Point *p)
{
    return strategy->calculateDerivative(p);
}

double PlaneStrategy::getZ(Point *p)
{
    return strategy->getZ(p);
}

double PlaneStrategy::getZ(double x, double y)
{
    return strategy->getZ(x, y);
}

Point *PlaneStrategy::getClosestPoint(double x, double y)
{
    return strategy->getClosestPoint(x, y);
}

Point *PlaneStrategy::getClosestPoint(Point *p)
{
    return strategy->getClosestPoint(p);
}

void PlaneStrategy::initializeWithParser(ParserInterface *pi)
{
    strategy->initializeWithParser(pi);
}

