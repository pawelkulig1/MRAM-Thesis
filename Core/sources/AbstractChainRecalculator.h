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
        static double distanceBetweenPoints(Point *p1, Point *p);
        virtual std::function<double(double)> getFunctionConnectingPoints(Point *p1, Point *p2) = 0;
        virtual std::deque<MovingImage> recalculateChain() = 0;
    };
}

