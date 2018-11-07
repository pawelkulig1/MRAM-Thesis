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
        Chain findNumberOfFunction(int pointNumber, Chain chain);
        Chain recalculateChain(Chain *originalChain);
    };
}
