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
        std::vector<std::pair<double, double>> getDistantPointOnFunction(double len, Point *p1, Point *p2, Point *lPoint);
        Eigen::Vector3d getChainDirection();
        Chain findNumberOfFunction(int pointNumber, Chain chain);
        Chain recalculateChain(Chain *originalChain);
        bool checkChainIntegrity(Chain c);

    };
}
