#include "PlaneStrategy.h"
#include "AbstractPlane.h"
#include "Point.h"

PlaneStrategy *PlaneStrategy::instance = nullptr;


PlaneStrategy::PlaneStrategy()
{
    this->strategy = nullptr;
}

void PlaneStrategy::setStrategy(AbstractPlane *pl)
{
    PlaneStrategy::strategy = pl;
}

PlaneStrategy *PlaneStrategy::getInstance()
{
    if(PlaneStrategy::instance == nullptr)
    {
        PlaneStrategy::instance = new PlaneStrategy();
    }   
    return PlaneStrategy::instance;
}

AbstractPlane *PlaneStrategy::getStrategy()
{
    throwIfStrategyNotSet();
    return PlaneStrategy::strategy;
}

void PlaneStrategy::throwIfStrategyNotSet()
{
    if(strategy == nullptr)
        throw(std::string("PlaneStrategy! No strategy was set!"));
}

Eigen::Vector3d PlaneStrategy::calculateDerivative(double x, double y)
{
    throwIfStrategyNotSet();
    return strategy->calculateDerivative(x, y);
}

Eigen::Vector3d PlaneStrategy::calculateDerivative(Point *p)
{   
    throwIfStrategyNotSet();
    return strategy->calculateDerivative(p);
}

double PlaneStrategy::getZ(Point *p)
{
    throwIfStrategyNotSet();
    return strategy->getZ(p);
}

double PlaneStrategy::getZ(double x, double y)
{   
    throwIfStrategyNotSet();
    return strategy->getZ(x, y);
}

Point *PlaneStrategy::getClosestPoint(double x, double y)
{
    throwIfStrategyNotSet();
    return strategy->getClosestPoint(x, y);
}

Point *PlaneStrategy::getClosestPoint(Point *p)
{
    throwIfStrategyNotSet();
    return strategy->getClosestPoint(p);
}

void PlaneStrategy::initializeWithParser(ParserInterface *pi)
{
    throwIfStrategyNotSet();
    strategy->initializeWithParser(pi);
}

