#include "MovingImage.h"

using namespace GNEB;

MovingImage::MovingImage(double x, double y, double z): Point(x, y, z) 
{
    double dx, dy;
    auto plane = Plane::getInstance();
    dx = plane->getDx();
    dy = plane->getDy();
    kappa = 0.01; 
    maxJumpDx = 0.1;
    maxJumpDy = 0.1;
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


    //linear interpolation between this and next point
    /*double b_x = (z * (x_h->getX()) - x * x_h->getZ())/(x_h->getX() - x);
    double a_x = (z - b_x) / x;

    double b_y = (z * (y_h->getY()) - y * y_h->getZ())/(y_h->getY() - y);
    double a_y = (z - b_y) / y;

    double h = 0.0001;

    dx = ((a_x * (x + h) + b_x) - (a_x * x + b_x)) / h;
    dy = ((a_y * (y + h) + b_y) - (a_y * y + b_y)) / h;
*/
    if(x_h != nullptr)
        dx = (x_h->getZ() - this->z)/Plane::getInstance()->getDx();
    if(y_h != nullptr)
        dy = (y_h->getZ() - this->z)/Plane::getInstance()->getDy();

    if(dx > maxJumpDx)
        dx = maxJumpDx;
    
    if(dy > maxJumpDy)
        dy = maxJumpDy;

    if(dx < -maxJumpDx)
        dx = -maxJumpDx;
    
    if(dy < -maxJumpDy)
        dy = -maxJumpDy;
    //TODO "negative" derivative
	return Eigen::Vector3d(dx, dy, 0);
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
    calculateUpgradedTangent();
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
        calculateUpgradedTangent();
    spring = kappa * ((next->getVector() - getVector()).norm() - (getVector() - previous->getVector()).norm()) * tau * 0;
    return spring;
}

Eigen::Vector3d MovingImage::calculateTotalForce()
{
    NEBForce = (- dE + spring);
    return NEBForce;
}

Eigen::Vector3d MovingImage::iterate()
{
    /*std::cout<<"before move: "<<calculateDerivative()<<std::endl;
    print();
    std::cout<<"======"<<std::endl;

    moveByVector(calculateDerivative());

    std::cout<<"after move: "<<std::endl;
    print();
    std::cout<<"======"<<std::endl;
    return calculateDerivative();*/
    calculateDerivative();
    calculateUpgradedTangent();
    calculatePerpendicularComponent();
    calculateSpring();
    calculateTotalForce();
    //moveByVector(NEBForce);
    return NEBForce;
}

Point *MovingImage::findXhPoint()
{
    return Plane::getInstance()->getPointXY(x + Plane::getInstance()->getDx(), y);
}

Point *MovingImage::findYhPoint()
{
    return Plane::getInstance()->getPointXY(x, y + Plane::getInstance()->getDy());
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
    double temp_x = this->x + v[0];
    double temp_y = this->y + v[1];
    Point *p = Plane::getInstance()->getPointXY(temp_x,temp_y);
    if(p != nullptr)
    {
        this->x = p->getX();
        this->y = p->getY();
        this->z = p->getZ();
        this->x_h = findXhPoint();
        this->y_h = findYhPoint(); 
    }
    else
        std::cout<<"MovingImage::moveByVector(): Point out of calculation space! Point: "<<x << " " << y <<" "<<z<<" "<<temp_x<<" "<<temp_y<<std::endl;

}

void MovingImage::moveByTotalForce()
{
        this->x += NEBForce[0];
        this->y += NEBForce[1];
        this->z += NEBForce[2];
        this->x_h = findXhPoint();
        this->y_h = findYhPoint(); 
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

std::string MovingImage::stringify()
{
    std::string ret = "";
    ret += "coords:" + std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(z) + ";";
    ret += "deriv:" + std::to_string(calculateDerivative()[0]) + ","+std::to_string(calculateDerivative()[1]) + ";"; 
    ret += "spring:" + std::to_string(spring[0]) + "," + std::to_string(spring[1]) + "," + std::to_string(spring[2]) + ";";
    return ret;
}
