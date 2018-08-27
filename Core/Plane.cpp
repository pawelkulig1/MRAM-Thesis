#include "Plane.h"

using namespace GNEB;

Plane *Plane::instance = nullptr;

Plane *Plane::getInstance()
{
    if(!instance)
        Plane::instance = new Plane();

    return instance;
}

void Plane::initializeWithParser(Parser::PlainDataParser *parser)
{
	this->points = parser->parse();
	this->xpos = parser->getXpos();
	this->ypos = parser->getYpos();
	this->zpos = 0; //CHECK IF NEEDED
	this->dx = parser->getDx();
	this->dy = parser->getDy();
	this->xnum = parser->getXSize();
	this->ynum = parser->getYSize();
}

double Plane::getXpos()
{
    return Plane::xpos;
}

double Plane::getYpos()
{
    return Plane::ypos;
}

double Plane::getZpos()
{
    return Plane::zpos;
}

void Plane::setXpos(double x)
{
    Plane::xpos = x;
}

void Plane::setYpos(double y)
{
    Plane::ypos = y;
}

void Plane::setZpos(double z)
{
    Plane::zpos = z;
}

double Plane::getDx()
{
    return Plane::dx;
}

double Plane::getDy()
{
    return Plane::dy;
}

int Plane::getXnum()
{
    return Plane::xnum;
}

int Plane::getYnum()
{
    return Plane::ynum;
}

void Plane::setPoints(std::deque<std::deque<Point *>> p)
{
    Plane::points = p;
}

std::deque<std::deque<Point *>> Plane::getPoints()
{
    return Plane::points;
}

Point *Plane::getPointXY(double x, double y)
{
    int n, m;
    n = round((x + xpos)/dx);
    m = round((y + ypos)/dy);
    return Plane::getPointNM(n, m);
}

Point *Plane::getPointNM(int x, int y)
{
	if(x > xnum-1 || y > ynum-1 || x<0 || y<0)
	{
		std::cout<<"bad x or y value in getPointNM! "<<x<<" "<<y<<" "<<xnum<<" "<<ynum<<std::endl;
        return nullptr; 
	}	
    return points[y][x];//not sure if I can do smth about that
    //this is caused by input file format and parser, we parse symbol after symbol and they go first n 
    //symbols has coordinates with increasing x so [0...n][0], but array in goes like this [col][row] 
    //so it has to be considered somewhere to switch these two.
    //
}

