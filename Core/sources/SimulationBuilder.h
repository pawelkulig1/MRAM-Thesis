#pragma once
#include "Parsers/ConfigParser.h"
#include <functional>
#include "Chain.h"

namespace GNEB
{
    class AbstractChainRecalculator;

    class SimulationBuilder
    {
    private:
        Chain buildChain();
        Chain chain;

    public:
        SimulationBuilder();
        void setPlaneType();
        Chain buildContinuous(std::function<double (double, double)> func);
    };
}
