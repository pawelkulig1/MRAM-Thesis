#pragma once
#include <vector>
#include "Chain.h"
#include "AbstractChainRecalculator.h"

namespace GNEB
{
    class SimulationRunner
    {
    private:
        Chain chain;
        std::vector<Chain> chainStorage;
        AbstractChainRecalculator *cRecalc;
        int iterationsGuard;
        int lastNCompare;
        bool isFifoEnabled;
        std::string fifoPath;
        int iterationNumber;

    public:
        SimulationRunner(Chain c);
        void setChainRecalculator(AbstractChainRecalculator &cRecalc);
        void addToStorage(Chain c);
        Chain findBestChain();
        double findLastNMax();
        bool isBreakConditionMet();
        bool run();
        void end();
        

    };
}
