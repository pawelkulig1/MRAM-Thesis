#pragma once
#include "AbstractChainRecalculator.h"

namespace GNEB
{
    class FixedDistanceChainRecalculator: public AbstractChainRecalculator
    {
    private:
        bool normalMode;

    public:
        FixedDistanceChainRecalculator();
        Eigen::Vector3d getDistantPointOnFunction(double len, Point *p1, Point *p2, Point *lPoint);
        Eigen::Vector3d getChainDirection();
        Eigen::Vector3d findNumberOfFunction(int pointNumber);
        std::function<double(double)> getFunctionConnectingPoints(Point *p1, Point *p2);
        std::deque<MovingImage> recalculateChain();
    };
}
