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
        //Point *x_h, *y_h;
    public:
        Point(double x, double y, double z);
        Point();
        double getX();
        double getY();
        double getZ();
        virtual void setX(double x);
        virtual void setY(double y);
        virtual void setZ(double z);
        virtual void print();
        virtual std::string stringify();
        virtual ~Point(){};

        //static double getDistance(Point *p1, Point *p2);
        //
        //void setX_h(Point *p);
        //void setY_h(Point *p);

        Eigen::Vector3d getVector();
        bool operator==(Point p);
        bool operator==(Point *p);
        
//		friend std::ostream& operator<<(std::ostream& os, Point *p);
    };
}

#endif //__POINT_H__

