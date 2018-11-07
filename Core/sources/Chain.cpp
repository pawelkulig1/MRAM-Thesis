#include "Chain.h"
#include "StationaryImage.h"
#include "Point.h"
#include "PlaneStrategy.h"

using namespace GNEB;

Chain::Chain()
{
    
}

MovingImage *Chain::getPoint(unsigned int number)
{
	if(number >= chain.size())
		throw("Chain::getPoint() to high index: " + std::to_string(number));
	return static_cast<MovingImage *>(&chain[number]);
}

void Chain::addToChain(MovingImage *p)
{
    auto *plane = PlaneStrategy::getInstance();
    auto TempPoint = plane->getClosestPoint(p->getX(), p->getY());
   
    p->setX(TempPoint->getX());
    p->setY(TempPoint->getY());
    p->setZ(TempPoint->getZ());

    chain.push_back(*p);
    delete TempPoint;
}

std::deque<MovingImage>::iterator Chain::begin()
{
	return chain.begin();
}

std::deque<MovingImage>::iterator Chain::end()
{
	return chain.end();
}

void Chain::setFirst(StationaryImage *p)
{
    auto plane = PlaneStrategy::getInstance();
    auto point = plane->getClosestPoint(static_cast<Point *>(p));
    this->first = static_cast<StationaryImage *>(point);
}

void Chain::setFirst(Point *p)
{
    auto plane = PlaneStrategy::getInstance();
    auto point = plane->getClosestPoint(p);
    this->first = static_cast<StationaryImage *>(point);
}

void Chain::setLast(StationaryImage *p)
{
    auto plane = PlaneStrategy::getInstance();
    auto point = plane->getClosestPoint(static_cast<Point *>(p));
    this->last = static_cast<StationaryImage *>(point);
}

void Chain::setLast(Point *p)
{
    auto plane = PlaneStrategy::getInstance();
    auto point = plane->getClosestPoint(p);
    this->last= static_cast<StationaryImage *>(point);
}

StationaryImage *Chain::getFirst()
{
    return first;
}

StationaryImage *Chain::getLast()
{
    return last;
}

void Chain::calculateInterpolation(const int Q)
{
    chain.erase(chain.begin(), chain.end());
	Eigen::Vector3d R1 = Eigen::Vector3d(first->getVector());
	Eigen::Vector3d RQ = Eigen::Vector3d(last->getVector());
	Eigen::Vector3d temp;
	for(int v=1;v<Q+1;v++)
	{
		temp = R1 + v * (RQ - R1) / (Q+1);
		addToChain(new MovingImage(temp[0], temp[1], temp[2]));
	}
}

double Chain::length2D()
{ 
    double length = 0;
    length += Point::distanceBetweenPoints2D(first, &chain[0]);
    length += Point::distanceBetweenPoints2D(last, &chain[chain.size() - 1]);
    for(int i=0;i<size()-1;i++)
    {
        length += Point::distanceBetweenPoints2D(&chain[i], &chain[i+1]);
    }
    return length;
}

double Chain::length3D()
{
    double length = 0;
    length += Point::distanceBetweenPoints3D(first, &chain[0]);
    length += Point::distanceBetweenPoints3D(last, &chain[chain.size() - 1]);
    for(int i=0;i<size()-1;i++)
    {
        length += Point::distanceBetweenPoints3D(&chain[i], &chain[i+1]);
    }

    return length;
}

int Chain::size()
{
    return this->chain.size();
}

void Chain::print()
{
    std::cout<<"["<<first->getX()<<", "<<first->getY()<<", "<<first->getZ()<<"]"<<std::endl;
    for(int i=0;i<chain.size();i++)
    {
        std::cout<<"["<<chain[i].getX()<<", "<<chain[i].getY()<<", "<<chain[i].getZ()<<"]"<<std::endl;
    }
    std::cout<<"["<<last->getX()<<", "<<last->getY()<<", "<<last->getZ()<<"]"<<std::endl;
}

std::string Chain::stringify()
{
    std::string ret = "";
    ret += first->stringify();
    for(int i=0;i<chain.size();i++)
    {
        ret += chain[i].stringify();
    }
    ret += last->stringify();
    ret += "|";
    return ret;

}

void Chain::erase()
{
    chain.erase(chain.begin(), chain.end());
}

Point* Chain::at(int n)
{
    return &chain[n];
}

void Chain::setCopy(Chain *c)
{
    erase();
    for(int i=0;i<c->size();i++)
    {
        this->chain.push_back(c->chain[i]);
    }
    this->first = c->getFirst(); 
    this->last = c->getLast();
}

void Chain::setCopy(Chain c)
{
    erase();
    for(int i=0;i<c.size();i++)
    {
        this->chain.push_back(c.chain[i]);
    }
    this->first = c.getFirst(); 
    this->last = c.getLast();
}


