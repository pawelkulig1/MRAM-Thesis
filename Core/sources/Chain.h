#ifndef __CHAIN_H__
#define __CHAIN_H__
#include <deque>
#include <Eigen/Dense>
#include <iostream>
#include "MovingImage.h" //needed because of container

namespace GNEB
{
    class StationaryImage;
    class Point;
    class PlaneStrategy;

	class Chain
	{
		//static Chain *instance;
		std::deque<MovingImage> chain;
        StationaryImage	*first, *last;

	public:
        Chain();
		//static Chain *getInstance();
        MovingImage *getPoint(unsigned int number);
		std::deque<MovingImage>::iterator begin();
		std::deque<MovingImage>::iterator end();
		void addToChain(MovingImage p);
		void addToChain(MovingImage *p);
        void setFirst(StationaryImage *p);
		void setFirst(Point *p);
   		void setLast(StationaryImage *p);
		void setLast(Point *p);
		void calculateInterpolation(const int Q);
        StationaryImage *getFirst();
        StationaryImage *getLast();
        int size();
        double length2D();
        double length3D();
        double findMaxEnergy();
        void print();        
        std::string stringify();
        void erase();

        void setCopy(Chain *c);
        void setCopy(Chain c);
        Point *at(int n);
	};
}

#endif //__CHAIN_H__
