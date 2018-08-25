#include "MovingImage.h"

using namespace GNEB;

MovingImage::MovingImage(double x, double y, double z): x(x), y(y), z(z)
{
}

Eigen::Vector3d MovingImage::calculateDerivative()
{
    double dx = 0, dy = 0;
    //maybe it should calculate derivative to second site to something like negative derivative

    if(x_h != nullptr)
        dx = (x_h->getZ() - this->z)/Plane::getInstance()->getDx();
    if(y_h != nullptr)
        dy = (y_h->getZ() - this->z)/Plane::getInstance()->getDy();

    //TODO "negative" derivative
	return Eigen::Vector3d(dx, dy, 0);
}


Eigen::Vector3d MovingImage::calculateTangent()
{
    Eigen::Vector3d temp;
    if(next != nullptr)
    {
        temp = next->getVector() - getVector();
    }
    tau = temp / temp.norm();
    Eigen::Vector3d derivative = calculateDerivative();
    dE = derivative - (derivative.dot(tau))*(tau);
    return dE;
}

Eigen::Vector3d MovingImage::calculateSpring()
{
    if(previous == nullptr)
    {
        std::cout<<x<<" "<<y<<" "<<"Cannot calculate spring force! prev"<<std::endl;
    }
    if(next == nullptr)
    {
        std::cout<<x<<" "<<y<<" "<<"Cannot calculate spring force! next"<<std::endl;
    }
    spring = kappa * ((next->getVector() - getVector()).norm() - (getVector() - previous->getVector()).norm()) * tau;
    return spring;
}

Eigen::Vector3d MovingImage::calculateTotalForce()
{
    NEBForce = (dE + spring);
    return NEBForce;
}

Eigen::Vector3d MovingImage::iterate()
{
    calculateTangent();
    calculateSpring();
    calculateTotalForce();
    moveByVector(NEBForce);
}

void MovingImage::moveToCords(double x, double y)
{
	auto p = Plane::getInstance()->getPointXY(x, y);
	this->x = p->getX();
	this->y = p->getY();
	this->z = p->getZ();
}

void MovingImage::moveByVector(Eigen::Vector3d v)
{

}

void MovingImage::setX_h(Point *p)
{
	this->x_h = p;
}

void MovingImage::setY_h(Point *p)
{
	this->y_h = p;
}

void MovingImage::setNext(Point *p)
{
    this->next = p;
}

void MovingImage::setPrevious(Point *p)
{
    this->previous = p;
}

double MovingImage::getX()
{
    return this->x; 
}

double MovingImage::getY()
{
    return this->y;
}

double MovingImage::getZ()
{
    return this->z;
}

void MovingImage::setX(double x)
{
    this->x = x;
}

void MovingImage::setY(double y)
{
    this->y = y;
}

void MovingImage::setZ(double z)
{
    this->z = z;
}



