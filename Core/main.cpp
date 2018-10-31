#include <iostream>
#include "sources/Chain.h"
#include "sources/Pipe.h"
#include "sources/Parsers/PlainDataParser.h"
#include "sources/ContinuousPlane.h"
#include "sources/FixedDistanceChainRecalculator.h"
#include <math.h>

using namespace std;
using namespace GNEB;

double func(double x, double y)
{
    double data[6][4] = {
        {5, 1, 0, 0},
        {-1, 1, -2, 0},
        {-1, 1, 2, 0},
        {1, 1, 0, 1},
        {-1, 1, 0, -1},
        {3, 1,  2,  -1}
    };


    double out = 0;
    for(int i=0;i<6;i++)
    {
        out += data[i][0] * exp(-(pow(x + data[i][2], 2) + \
				pow(y + data[i][3], 2))/(2 * pow(data[i][1], 2)));
    }
    return out;
}

int main()
{
	Chain *c = Chain::getInstance();
	//auto parser = new Parser::PlainDataParser("../data/data1.dat");
	auto plane = PlaneStrategy::getInstance();
    auto cPlane = new ContinuousPlane();
    cPlane->setFunction(func);
    plane->setStrategy(cPlane);
    auto cRecalculator = new FixedDistanceChainRecalculator();
    c->setChainRecalculator(cRecalculator);
    c->setFirst(new Point(-2.3, 0, plane->getZ(-2.3, 0)));
    c->setLast(new Point(2.3, 0, plane->getZ(2.3, 0)));
    c->calculateInterpolation(5);

    c->print();
     
    Pipe *pipe = new Pipe("../PythonVisualisation/plotFIFO");
    pipe->write(c->stringify());
    for(int i=0;i<13;i++)
    {
        std::cout<<"ITERATION: " << i << std::endl;
        for(auto it=c->begin();it<c->end();it++)
        {
            it->iterate();
        }
        for(auto it=c->begin();it<c->end();it++)
        {
            it->moveByTotalForce();
        }
        //c->print();
        c->resetImages();
        //c->print();
        pipe->write(c->stringify());
    }

    std::cout<<"===================="<<std::endl;

    c->print();
    delete pipe;
}
