#ifndef __MOVING_IMAGE_H__
#define __MOVING_IMAGE_H__

#include <Eigen/Dense>
#include "Point.h"
#include "Plane.h"

namespace GNEB
{
	class MovingImage : public Point
	{
		double kappa, maxJumpDx, maxJumpDy; // kappa is spring constant
        Eigen::Vector3d tau;
		Eigen::Vector3d dE;
		Eigen::Vector3d spring;
        Eigen::Vector3d NEBForce;

    public:
		Eigen::Vector3d calculateDerivative();
        Eigen::Vector3d calculateTangent();
        Eigen::Vector3d calculateUpgradedTangent();
        Eigen::Vector3d calculatePerpendicularComponent();
        Eigen::Vector3d calculateSpring();
        Eigen::Vector3d calculateTotalForce();

		Point *x_h, *y_h; //x_h point and y_h are to faster calculate derivate dE and not to search for it. They will store closest Point with coordinates x_h = (x+dx, y); y_h = (x, y+dy).
        Point *next, *previous;

		MovingImage(double x, double y, double z);
        Eigen::Vector3d iterate();
        Point *findXhPoint();
        Point *findYhPoint();
		void moveToCords(double x, double y);
		void moveByVector(const Eigen::Vector3d);
        void moveByTotalForce();
		void setX_h(Point *p);
		void setY_h(Point *p);
        void getX_h();
        void getY_h();
        void setNext(Point *p);
        void setPrevious(Point *p);
        void print() override ;
        std::string stringify();
	};
}

#endif //__MOVING_IMAGE_H__
