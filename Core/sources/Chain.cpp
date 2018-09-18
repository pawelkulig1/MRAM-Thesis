#include "Chain.h"
#include "StationaryImage.h"
#include "Point.h"
#include "PlaneStrategy.h"

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

void Chain::addToChain(MovingImage *p)
{
    auto *plane = PlaneStrategy::getInstance();
    auto TempPoint = plane->getClosestPoint(p->getX(), p->getY());

    p->setX(TempPoint->getX());
    p->setY(TempPoint->getY());
    p->setZ(TempPoint->getZ());
    if(chain.size() == 0)
        p->setPrevious(static_cast<Point *> (first));
    else
    {
        p->setPrevious(static_cast<Point *>(&chain[chain.size()-1]));
        chain[chain.size()-1].setNext(p);   
    }
    p->setNext(static_cast<Point *>(last));

	chain.push_back(*p);
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

void Chain::checkFirstAndLast()
{
    if(first == nullptr || last == nullptr)
    {
        return;
    }

    StationaryImage *temp = nullptr;
    if(last->getX() < first->getX() || last->getY() < first->getY())
    {
        temp = first;
        first = last;
        last = temp;
    }
    temp = nullptr;
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
    chain[chain.size() - 1].setNext(last);

}

int Chain::size()
{
    return this->chain.size();
}

void Chain::print()
{
    first->print();

    for(int i=0;i<chain.size();i++)
    {
        std::cout<<"["<<chain[i].getX()<<", "<<chain[i].getY()<<", "<<chain[i].getZ()<<"]"<<std::endl;
    }
    last->print();
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
