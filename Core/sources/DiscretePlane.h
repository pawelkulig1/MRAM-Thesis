#ifndef __PLANE_H__
#define __PLANE_H__
#include <deque>

#include "Point.h"
#include "Parsers/PlainDataParser.h"
#include "AbstractPlane.h"

using namespace Parser;

namespace GNEB
{
    class ParserInterface;
    class DiscretePlane: public AbstractPlane
    {
        double dx, dy;
        int xnum, ynum;
        std::deque<std::deque<Point>> points;
    public:
        DiscretePlane();
        
        Eigen::Vector3d calculateDerivative(double x, double y) override;
        Eigen::Vector3d calculateDerivative(Point *p) override;
        
        double getZ(double x, double y) override;
        double getZ(Point *p) override;
        double getZ(int x, int y);
        
        Point *getClosestPoint(double x, double y) override;
        Point *getClosestPoint(Point *p) override;
        Point *getClosestPoint(int x, int y);

		void initializeWithParser(ParserInterface *pi) override;
        
        void setDx(double dx);
        void setDy(double dy);
        
        void setXnum(int xnum);
        void setYnum(int ynum);

        int getXnum();
        int getYnum();
        void setPoints(std::deque<std::deque<Point>> p);
        std::deque<std::deque<Point >> getPoints();
    };

}
#endif //__PLANE_H__
