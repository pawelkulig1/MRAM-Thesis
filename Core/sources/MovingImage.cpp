#include "MovingImage.h"

using namespace GNEB;

MovingImage::MovingImage(double x, double y, double z): Point(x, y, z) 
{
    double dx, dy;
    kappa = 1; 
    next = nullptr;
    previous = nullptr;    
    tau = Eigen::Vector3d(0,0,0);
    calculateDerivative();
}

void MovingImage::calculateDerivative()
{
    auto plane = PlaneStrategy::getInstance();
    derivative = plane->calculateDerivative(x, y);
}

Eigen::Vector3d MovingImage::calculateTangent()
{
    Eigen::Vector3d temp;
    if(next != nullptr && previous != nullptr)
    {
        temp = next->getVector() - previous->getVector();
    }
    else{
        std::cout<<"next == nullptr or previous == nullptr"<<std::endl;
    }
    tau = temp / temp.norm();
    return tau;
}

Eigen::Vector3d MovingImage::calculateUpgradedTangent()
{
    double dEMax = (abs(next->getZ() - z) > abs(previous->getZ() - z)) ? abs(next->getZ() - z) : abs(previous->getZ() - z);
    double dEMin = (abs(next->getZ() - z) < abs(previous->getZ() - z)) ? abs(next->getZ() - z) : abs(previous->getZ() - z);

    Eigen::Vector3d tPlus = next->getVector() - getVector();
    Eigen::Vector3d tMinus = getVector() - previous->getVector();

    if(next->getZ() >= previous->getZ())
    {
        return tPlus * dEMax + tMinus * dEMin;
    }
    if(next->getZ() < previous->getZ())
    {
        return tPlus * dEMin + tMinus * dEMax;
    }
    return tPlus; //to avoid warning
}

Eigen::Vector3d MovingImage::calculatePerpendicularComponent()
{
    calculateTangent();
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
    /*if(tau == Eigen::Vector3d(0,0,0))
        calculateTangent();
    auto tempNext = Eigen::Vector3d(next->getX(), next->getY(), 0);
    auto tempPrev = Eigen::Vector3d(previous->getX(), previous->getY(), 0);
    //spring kappa * (next - )
    spring = kappa * ((next->getVector() - getVector()).norm() - (getVector() - previous->getVector()).norm()) * tau;
    */

    double tempDx = ((previous->getX() + next->getX()) / 2) - x;
    double tempDy = ((previous->getY() + next->getY()) / 2) - y;

    spring = Eigen::Vector3d(tempDx * 0.1, tempDy * 0.1, 0);
    return spring;
}

Eigen::Vector3d MovingImage::calculateTotalForce()
{
    NEBForce = (- derivative + spring);
    return NEBForce;
}

Eigen::Vector3d MovingImage::iterate()
{
    //calculateUpgradedTangent();
    //calculatePerpendicularComponent();
    calculateSpring();
    calculateTotalForce();
    //NEBForce =-derivative;
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
    ret += "spring:" + std::to_string(spring[0]) + "," + std::to_string(spring[1]) + "," + std::to_string(spring[2]) + ";";
    return ret;
}
