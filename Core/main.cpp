#include <iostream>
#include "sources/FixedDistanceChainRecalculator.h"
#include <math.h>
#include "sources/SimulationBuilder.h"
#include "sources/commonDefines.h"
#include "sources/SimulationRunner.h"
#include <time.h>

using namespace std;
using namespace GNEB;
using boost::any_cast;

#define PIPE false
#define DEBUG false


double func(double x, double y)
{
    double data[6][4] = {
        {25, 1, 0, 0},
        {-10, 1, -2.3, 0},
        {-10, 1, 2.3, 0},
        {0, 1, 0, 1},
        {0, 1, 0, -1},
        {25, 1,  2,  -1}
    };
    //height, width, x , y

    double out = 0;
    for(int i=0;i<6;i++)
    {
        out += data[i][0] * exp(-(pow(x + data[i][2], 2) + \
				pow(y + data[i][3], 2))/(2 * pow(data[i][1], 2)));
    }
    return out;
}

double metricsFunction(Chain &c)
{
    double max = c.getPoint(0)->getZ() + 1 * c.length2D();
    for(int i=0;i<c.size();i++)
    {
        if(c.getPoint(i)->getZ() + 1 * c.length2D() > max)
        {
            max = c.getPoint(i)->getZ() + 1 * c.length2D();
        }
    }
    return max;
}


int main()
{
    SimulationBuilder sb;
    Chain c;
    c.setCopy(sb.buildContinuous(func));
    SimulationRunner SM(c);
    SM.setMetricsFunction(metricsFunction);
    FixedDistanceChainRecalculator fdcr;
    SM.setChainRecalculator(fdcr);
    SM.run();
    return 0;
}
