#include "Chain.h"

using namespace GNEB;

Chain *Chain::instance = nullptr;

Chain *Chain::getInstance()
{
	if(!instance)
		instance = new Chain();
	return instance;
}

Point Chain::getPoint(unsigned int number)
{
	if(number > chain.size())
		throw("Chain::getPoint() to high index");
	return chain[number];
}

void Chain::addToChain(MovingImage p)
{
    //TODO here we may go outside of Plane and add point that doesn't exist. Need to check that. not sure now
    Point *TempPoint;
    Plane *plane = Plane::getInstance();

    TempPoint = plane->getPointXY(p.getX() + plane->getDx(), p.getY());

	p.setX_h(TempPoint);

    TempPoint = plane->getPointXY(p.getX(), p.getY() + plane->getDy());
    
    p.setY_h(TempPoint);
    if(chain.size() == 0)
    {
        p.setPrevious(first);
    }

    if(chain.size() > 0)
    {
        chain[chain.size() - 1].setNext(&p);
        p.setPrevious(&chain[chain.size() - 1]);
    }

    TempPoint = plane->getPointXY(p.getX(), p.getY());
    p.setX(TempPoint->getX());
    p.setY(TempPoint->getY());
    p.setZ(TempPoint->getZ());
    //std::cout<<&p<<std::endl;
	chain.push_back(p);
	recalculateChain();
}

void Chain::addToChain(MovingImage *p)
{

    std::cout<<"pointer to p: "<<p<<std::endl;
    Point *TempPoint;
    Plane *plane = Plane::getInstance();

    TempPoint = plane->getPointXY(p->getX() + plane->getDx(), p->getY());

	p->setX_h(TempPoint);

    TempPoint = plane->getPointXY(p->getX(), p->getY() + plane->getDy());
    
    p->setY_h(TempPoint);
    if(chain.size() == 0)
    {
        p->setPrevious(first);
    }

    if(chain.size() > 0)
    {
        chain[chain.size() - 1].setNext(p);
        p->setPrevious(&(chain[chain.size() - 1]));
    }

    TempPoint = plane->getPointXY(p->getX(), p->getY());
    p->setX(TempPoint->getX());
    p->setY(TempPoint->getY());
    p->setZ(TempPoint->getZ());

    std::cout<<"pointer before chain size > 0: "<<p<<std::endl;
	chain.push_back(*p);
	recalculateChain();
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
    this->first = p;
}

void Chain::setFirst(Point *p)
{
    this->first = static_cast<StationaryImage *>(p);
}

void Chain::setLast(StationaryImage *p)
{
    this->last = p;
}

void Chain::setLast(Point *p)
{
	this->last = static_cast<StationaryImage *>(p);
}

StationaryImage *Chain::getFirst()
{
    return first;
}

StationaryImage *Chain::getLast()
{
    return last;
}


void Chain::calculateInterpolation(int Q)
{
	Eigen::Vector3d R1 = Eigen::Vector3d(first->getVector());
	Eigen::Vector3d RQ = Eigen::Vector3d(last->getVector());
    std::cout<<R1<<" "<<RQ<<std::endl;
	Eigen::Vector3d temp;
	for(int v=1;v<Q+1;v++)
	{
		temp = R1 + v * (RQ - R1) / (Q+1);
        std::cout<<temp[0]<<" "<<temp[1]<<" "<<temp[2]<<std::endl;
		addToChain(new MovingImage(temp[0], temp[1], temp[2]));
	}
    chain[chain.size() - 1].setNext(last);

	recalculateChain();
}


void Chain::recalculateChain()
{
		std::sort(chain.begin(), chain.end(), [](Point p1, Point p2){
						if(p1.getX() < p2.getX() || p1.getY() < p2.getY())
							return true;
						else
							return false;
						});
}
