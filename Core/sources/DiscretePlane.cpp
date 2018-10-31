#include "DiscretePlane.h"

using namespace GNEB;

DiscretePlane::DiscretePlane(){}

Eigen::Vector3d DiscretePlane::calculateDerivative(double x, double y)
{
    double tempDx = (getZ(x + dx, y) - getZ(x, y)) / dx;
    double tempDy = (getZ(x, y + dy) - getZ(x, y)) / dy;
    return Eigen::Vector3d(tempDx, tempDy, 0);
}

Eigen::Vector3d DiscretePlane::calculateDerivative(Point *p)
{
    double x = p->getX();
    double y = p->getY();
    return calculateDerivative(x, y);   
}

double DiscretePlane::getZ(double x, double y)
{
    int n, m;
    n = round((x)/dx);
    m = round((y)/dy);

    return getClosestPoint(n, m)->getZ();
}

double DiscretePlane::getZ(Point *p)
{
    double x = p->getX();
    double y = p->getY();
    return getClosestPoint(x, y)->getZ();
}

double DiscretePlane::getZ(int x, int y)
{
    return getClosestPoint(x, y)->getZ();
}

Point *DiscretePlane::getClosestPoint(double x, double y)
{    
    int n, m;
    n = round((x)/dx);
    m = round((y)/dy);
    return getClosestPoint(n, m);
}

Point *DiscretePlane::getClosestPoint(int x, int y)
{ 
	if(x > xnum-1 || y > ynum-1 || x<0 || y<0)
	{
        std::cout<<"bad x or y value in getPointNM! "
            <<x<<" "<<y<<" "<<xnum<<" "<<ynum<<std::endl;
	}	
    if(x > xnum - 1)
        x = xnum - 1;
    if(y > ynum - 1)
        y = ynum - 1;
    if(x < 0)
        x = 0;
    if(y < 0)
        y = 0;

    // not sure if I can do smth about that
    // this is caused by input file format and parser,
    // we parse symbol after symbol and they go first n 
    // symbols has coordinates with increasing x so 
    // [0...n][0], but array in goes like this [col][row] 
    // so it has to be considered somewhere to switch these two.

    return &points[y][x];
    
}

Point *DiscretePlane::getClosestPoint(Point *p)
{
    double x = p->getX();
    double y = p->getY();
    return getClosestPoint(x, y);
}


void DiscretePlane::initializeWithParser(ParserInterface *pi)
{
    /*points.erase(points.begin(), points.end());
    pi->parse(&points);

	this->dx = pi->getDx();
	this->dy = pi->getDy();
	this->xnum = pi->getXSize();
	this->ynum = pi->getYSize();*/
}

void DiscretePlane::setPoints(std::deque<std::deque<Point>> p)
{
    DiscretePlane::points = p;
}

std::deque<std::deque<Point>> DiscretePlane::getPoints()
{
    return DiscretePlane::points;
}

void DiscretePlane::setDx(double dx)
{
    this->dx = dx;
}

void DiscretePlane::setDy(double dy)
{
    DiscretePlane::dy = dy;
}

void DiscretePlane::setXnum(int xnum)
{
    this->xnum = xnum;
}

void DiscretePlane::setYnum(int ynum)
{
    this->ynum = ynum;
}

DiscretePlane::~DiscretePlane()
{
}
