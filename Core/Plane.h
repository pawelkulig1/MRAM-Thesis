#ifndef __PLANE_H__
#define __PLANE_H__
#include <deque>

#include "Point.h"
#include "Parsers/PlainDataParser.h"

using namespace GNEB;

namespace GNEB
{
    class Plane
    {
        static Plane *instance;
        double xpos, ypos, zpos, dx, dy;
        int xnum, ynum;
        std::deque<std::deque<Point>> points;
        Plane(){}
    public:
        static Plane *getInstance();
		void initializeWithParser(Parser::PlainDataParser *parser);
        double getXpos();
        void setXpos(double x);
        double getYpos();
        void setYpos(double y);
        double getZpos();
        void setZpos(double z);
        double getDx();
        double getDy();
        int getXnum();
        int getYnum();
        void setPoints(std::deque<std::deque<Point>> p);
        Point *getPointXY(double x, double y);
        Point *getPointNM(int x, int y);
        std::deque<std::deque<Point >> getPoints();
    };

}
#endif //__PLANE_H__
