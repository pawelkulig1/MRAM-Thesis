#include "MovingImage.h"

using namespace GNEB;

MovingImage::MovingImage(double x, double y, double z): Point(x, y, z) 
{
    double dx, dy;
    kappa = 1; 
    next = nullptr;
    previous = nullptr;    
    calculateDerivative();
}

MovingImage::MovingImage(Point *p)
{
    kappa = 1;
}


void MovingImage::calculateDerivative()
{
    auto plane = PlaneStrategy::getInstance();
    derivative = plane->calculateDerivative(x, y);
}


Eigen::Vector3d MovingImage::calculateTotalForce()
{
    NEBForce = (- derivative );
    return NEBForce;
}

Eigen::Vector3d MovingImage::iterate()
{
    calculateTotalForce();
    return NEBForce;
}

void MovingImage::moveToCords(double x, double y)
{
    auto plane = PlaneStrategy::getInstance();
	auto p = plane->getClosestPoint(x, y);
	this->x = p->getX();
	this->y = p->getY();
	this->z = p->getZ();
    calculateDerivative();
}

void MovingImage::moveByVector(const Eigen::Vector3d v)
{
    double temp_x = this->x + v[0];
    double temp_y = this->y + v[1];
    auto plane = PlaneStrategy::getInstance();
    auto p = plane->getClosestPoint(temp_x, temp_y);
    this->x = p->getX();
    this->y = p->getY();
    this->z = p->getZ();
    calculateDerivative();

}

void MovingImage::moveByTotalForce()
{
    auto plane = PlaneStrategy::getInstance();
    this->x += NEBForce[0];
    this->y += NEBForce[1];
    this->z = plane->getZ(x, y);
    calculateDerivative();
}

void MovingImage::setNext(Point *p)
{
    this->next = p;
}

void MovingImage::setPrevious(Point *p)
{
    this->previous = p;
}

void MovingImage::print()
{
    std::cout<<"["<<x<<", "<<y<<", "<<z<<"]"
        <<std::endl;
}

std::string MovingImage::stringify()
{
    std::string ret = "";
    ret += "coords:" + std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(z) + ";";
    ret += "deriv:" + std::to_string(-derivative[0]) + ","+std::to_string(-derivative[1]) + ";"; 
    ret += "spring:" + std::to_string(0) + ","+std::to_string(0) + ";"; 
    return ret;
}
