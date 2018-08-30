#ifndef __MOVING_IMAGE_H__
#define __MOVING_IMAGE_H__

#include <Eigen/Dense>
#include "Point.h"
#include "Plane.h"

namespace GNEB
{
	class MovingImage : public Point
	{
		double kappa; // kappa is spring constant
		Point *x_h, *y_h; //x_h point and y_h are to faster calculate derivate dE and not to search for it. They will store closest Point with coordinates x_h = (x+dx, y); y_h = (x, y+dy).
        Point *next, *previous;
        Eigen::Vector3d tau;
		Eigen::Vector3d dE;
		Eigen::Vector3d spring;
        Eigen::Vector3d NEBForce;

    public:
		Eigen::Vector3d calculateDerivative();
        Eigen::Vector3d calculateTangent();
        Eigen::Vector3d calculateSpring();
        Eigen::Vector3d calculateTotalForce();

		MovingImage(double x, double y, double z);
        Eigen::Vector3d iterate();
		void moveToCords(double x, double y);
		void moveByVector(Eigen::Vector3d);
		void setX_h(Point *p);
		void setY_h(Point *p);
        void setNext(Point *p);
        void setPrevious(Point *p);
        void print() override ;
	};
}

#endif //__MOVING_IMAGE_H__
