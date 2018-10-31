#ifndef __MOVING_IMAGE_H__
#define __MOVING_IMAGE_H__

#include <Eigen/Dense>
#include "Point.h"
#include "PlaneStrategy.h"

namespace GNEB
{
	class MovingImage : public Point
	{
		double kappa; // kappa is spring constant
        Eigen::Vector3d NEBForce;
        Eigen::Vector3d derivative;

    public:
        void calculateDerivative();
        Eigen::Vector3d calculateTotalForce();

		//Point *x_h, *y_h; //x_h point and y_h are to faster calculate derivate dE and not to search for it. They will store closest Point with coordinates x_h = (x+dx, y); y_h = (x, y+dy).
//        Point *next, *previous;

		MovingImage(double x, double y, double z);
        MovingImage(Point *p);
        Eigen::Vector3d iterate();
		void moveToCords(double x, double y);
		void moveByVector(const Eigen::Vector3d);
        void moveByTotalForce();
//        void setNext(Point *p);
//        void setPrevious(Point *p);
        void print() override ;
        std::string stringify() override;
	};
}

#endif //__MOVING_IMAGE_H__
