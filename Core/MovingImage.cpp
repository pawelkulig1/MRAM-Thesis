#include "MovingImage.h"

using namespace GNEB;

MovingImage::MovingImage(double x, double y, double z): Point(x, y, z) 
{
    double dx, dy;
    auto plane = Plane::getInstance();
    dx = plane->getDx();
    dy = plane->getDy();
    kappa = 1;
    x_h = plane->getPointXY(x + dx, y);
    y_h = plane->getPointXY(x, y + dy);
    next = nullptr;
    previous = nullptr;    
    tau = Eigen::Vector3d(0,0,0);
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
    else{
        std::cout<<"next == nullptr"<<std::endl;
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
    if(tau == Eigen::Vector3d(0,0,0))
        calculateTangent();
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
    //moveByVector(NEBForce);
    return NEBForce;
}

void MovingImage::moveToCords(double x, double y)
{
	auto p = Plane::getInstance()->getPointXY(x, y);
	this->x = p->getX();
	this->y = p->getY();
	this->z = p->getZ();
}

void MovingImage::moveByVector(const Eigen::Vector3d v)
{
    //double t_x = x + v[0];
    //double t_y = y + v[1];
    x += v[0];
    y += v[1];
    Point *p = Plane::getInstance()->getPointXY(x,y);
    if(p != nullptr)
        z = p->getZ();
    else
        std::cout<<"Point out of calculation space!"<<std::endl;
}

void MovingImage::setNext(Point *p)
{
    this->next = p;
}

void MovingImage::setPrevious(Point *p)
{
    this->previous = p;
}

void MovingImage::setX_h(Point *p)
{
    this->x_h = p;
}

void MovingImage::setY_h(Point *p)
{
    this->y_h = p;
}

void MovingImage::print()
{
    std::cout<<"["<<x<<", "<<y<<", "<<z<<", x_h: ["<< x_h->getX()<<", "
        <<x_h->getY()<<", "<<x_h->getZ()<<"], y_h: ["<< y_h->getX() <<", "<<y_h->getY()<<", "<<y_h->getZ()<<"]]"<<std::endl;
}
