#include "SimulationBuilder.h"
#include "AbstractChainRecalculator.h"
#include "commonDefines.h"
#include <vector>
#include "Point.h"
#include "ContinuousPlane.h"
#include "PlaneStrategy.h"
#include "MovingImage.h"

using namespace GNEB;
SimulationBuilder::SimulationBuilder()
{

}

Chain SimulationBuilder::buildChain()
{
    Chain mainChain;
    ConfigParser cp(MAIN_CONFIG_PATH);

    std::vector<double> vec = cp.getVector<double>("chain.firstPoint");
    mainChain.setFirst(new Point(vec[0], vec[1], vec[2]));
    
    std::vector<double> vec2= cp.getVector<double>("chain.lastPoint");
    mainChain.setLast(new Point(vec2[0], vec2[1], vec2[2]));

    bool isInterpolationOn = cp.getValue<bool>("chain.linearInterpolation");
    if(isInterpolationOn)
    {
        int N = cp.getValue<int>("chain.linearInterpolationPoints");
        mainChain.calculateInterpolation(N);
    }
    else
    {
        std::vector<std::vector<double>> vec = cp.getMatrix<double>("chain.initialChain");
        for(std::vector v: vec)
        {
            mainChain.addToChain(new MovingImage(v[0], v[1], v[2]));
        }
    }

    return mainChain;

}

Chain SimulationBuilder::buildContinuous(std::function<double (double, double)> func)
{
    PlaneStrategy *plane = PlaneStrategy::getInstance();
    ContinuousPlane *cPlane = new ContinuousPlane();
    cPlane->setFunction(func);
    plane->setStrategy(cPlane);
    
    return buildChain();
}
