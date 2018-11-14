#include "SimulationRunner.h"
#include "Parsers/ConfigParser.h"
#include "commonDefines.h"
#include "Pipe.h"


using namespace GNEB;

SimulationRunner::SimulationRunner(Chain c)
{
    ConfigParser cp(MAIN_CONFIG_PATH);
    iterationsGuard = cp.getValue<int>("main.iterationsGuard");
    lastNCompare = cp.getValue<int>("main.lastNCompare");
    isFifoEnabled = cp.getValue<bool>("main.enableFifoOutput");
    if(isFifoEnabled)
        fifoPath = cp.getValue<std::string>("main.fifoPath");

    chain.setCopy(c);
}

void SimulationRunner::setChainRecalculator(AbstractChainRecalculator &cRecalc)
{
    this->cRecalc = &cRecalc;
}

void SimulationRunner::addToStorage(Chain c)
{
    chainStorage.push_back(c);
}

Chain SimulationRunner::findBestChain()
{
    Chain min = Chain();
    min.setCopy(chainStorage[0]);

    for(Chain c: chainStorage)
    {
        if(metricsFunction(c) < metricsFunction(min))
        {
            min.setCopy(c);
        }
    }
    return min;
}

double SimulationRunner::findLastNMax()
{
    int i = iterationNumber;
    double max = 0;
    int N = lastNCompare;
    if(i > N)
    {
        for(int j=0;j<N;j++)
        {
            if(metricsFunction(chainStorage[i - j - 2]) > max)
                max = metricsFunction(chainStorage[i - j - 2]);
        }
    }
    else
        max = 100;

    return max;
}

bool SimulationRunner::isBreakConditionMet()
{
    double max = findLastNMax();
    if(max >= metricsFunction(chain))
    {
        return false;
    }
    return true;
}

bool SimulationRunner::run()
{
    iterationNumber = 0;
    while(iterationNumber < iterationsGuard)
    {
        std::cout<<"ITERATION: " << iterationNumber << ", ";

        for(int i=0;i<chain.size();i++)
        {
            chain.getPoint(i)->iterate();
        }
        for(int i=0;i<chain.size();i++)
        {
            chain.getPoint(i)->moveByTotalForce();
        }

        chain.setCopy(cRecalc->recalculateChain(&chain));
        addToStorage(chain);

        double max = findLastNMax();
        std::cout<<"MAX: "<<max<<std::endl;
        if(isBreakConditionMet())
        {
            chain.setCopy(findBestChain());
            std::cout<<"algorithms ends after: " << iterationNumber <<" iterations."<<std::endl;
            end();
            return 0;
        }

        iterationNumber++;
    }
    return 1;
}

void SimulationRunner::end()
{
    std::cout<<"===================="<<std::endl;
    chain.print();
    std::cout<<"metrics score: " << metricsFunction(chain)<<std::endl;
    std::cout<<"Energy required: " << chain.findMaxEnergy()<<std::endl;

    if(isFifoEnabled)
    {
        Pipe pipe(fifoPath);
        pipe.write(chain.stringify());
        pipe.close();
    }
}

void SimulationRunner::setMetricsFunction(std::function<double (Chain &c)> ms)
{
    this->metricsFunction = ms;
}
