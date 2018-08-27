#ifndef __POINT_H__
#define __POINT_H__

#include <iostream>
#include <boost/lexical_cast.hpp>
#include <Eigen/Dense>

namespace GNEB
{ 
    class Point
    {
    protected:
        double x, y, z;
        static int counter;
    public:
        Point(double x, double y, double z);
        Point();
        virtual double getX();
        virtual double getY();
        virtual double getZ();
        virtual void setX(double x);
        virtual void setY(double y);
        virtual void setZ(double z);
		virtual void print();
        virtual Eigen::Vector3d getVector();
//		friend std::ostream& operator<<(std::ostream& os, Point *p);
    };
}

#endif //__POINT_H__

