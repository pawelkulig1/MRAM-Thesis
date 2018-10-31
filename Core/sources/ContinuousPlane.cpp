#include "ContinuousPlane.h"

using namespace GNEB;


ContinuousPlane::ContinuousPlane()
{
    dx = 0.000001;
    dy = 0.000001;
    planeFunction = nullptr;
}

Eigen::Vector3d ContinuousPlane::calculateDerivative(double x, double y)
{
    double tempDx = (getZ(x + dx, y) - getZ(x, y)) / dx;
    double tempDy = (getZ(x, y + dy) - getZ(x, y)) / dy;
    double sq = sqrt(pow(tempDx, 2) + pow(tempDy, 2));
    tempDx = (tempDx / sq) * 0.1;
    tempDy = (tempDy / sq) * 0.1;   
    Eigen::Vector3d derivative(tempDx, tempDy, 0);
    return derivative;
}

Eigen::Vector3d ContinuousPlane::calculateDerivative(Point *p)
{
    double x = p->getX();
    double y = p->getY();

    double tempDx = (getZ(x + dx, y) - getZ(x, y)) / dx;
    double tempDy = (getZ(x, y + dy) - getZ(x, y)) / dy;
    double sq = sqrt(pow(tempDx, 2) + pow(tempDy, 2));
    tempDx = (tempDx / sq) * 0.1;
    tempDy = (tempDy / sq) * 0.1;   
    Eigen::Vector3d derivative(tempDx, tempDy, 0);
    return derivative;
}

double ContinuousPlane::getZ(double x, double y)
{
    if(planeFunction == nullptr)
    {
        std::cout<<"planeFunction not set: "<<__LINE__<< "ContinuousPlane.cpp"<<std::endl;
        throw("plane function not set!");
    }
    return planeFunction(x, y);
}

double ContinuousPlane::getZ(Point *p)
{
    double x = p->getX();
    double y = p->getY();

    return getZ(x, y);
}

Point *ContinuousPlane::getClosestPoint(double x, double y)
{
    return new Point(x, y, getZ(x, y));
}

Point *ContinuousPlane::getClosestPoint(Point *p)
{
    return new Point(p->getX(), p->getY(), getZ(p->getX(), p->getY()));
}

void ContinuousPlane::initializeWithParser(ParserInterface *pi)
{
    //TODO
}

void ContinuousPlane::setFunction(std::function<double (double, double)> f)
{
    this->planeFunction = f;
}
