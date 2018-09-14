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
	chain.push_back(p);
}

void Chain::addToChain(MovingImage *p)
{

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
    //std::cout<<"["<<first->getX()<<", "<<first->getY()<<", "<<first->getZ()<<"]"<<std::endl;
    //for_each(chain.begin(), chain.end(), [](MovingImage m){
    //    std::cout<<"["<<m.getX()<<", "<<m.getY()<<", "<<m.getZ()<<"]"<<std::endl;
    //});

    for(int i=0;i<chain.size();i++)
    {
        std::cout<<"["<<chain[i].getX()<<", "<<chain[i].getY()<<", "<<chain[i].getZ()<<"]"<<std::endl;
    }
    last->print();
    //std::cout<<"["<<getX()<<", "<<getY()<<", "<<getZ()<<"]"<<std::endl;
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
