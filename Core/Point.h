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
        double getX();
        double getY();
        double getZ();
        void setX(double x);
        void setY(double y);
        void setZ(double z);
		void print();
        Eigen::Vector3d getVector();
//		friend std::ostream& operator<<(std::ostream& os, Point *p);
    };
}

#endif //__POINT_H__

