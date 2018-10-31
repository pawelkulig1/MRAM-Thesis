#pragma once
#include <deque>
#include <functional>
#include "MovingImage.h"

namespace GNEB
{
    class MovingImage;
    class Point;

    class AbstractChainRecalculator
    {
    protected:
        std::deque<MovingImage> chainCopy;
    public:
        static double distanceBetweenPoints2D(Point *p1, Point *p2);
        static double distanceBetweenPoints3D(Point *p1, Point *p2);
        virtual std::function<double(double)> getFunctionConnectingPoints(Point *p1, Point *p2) = 0;
        virtual std::deque<MovingImage> recalculateChain() = 0;
    };
}

