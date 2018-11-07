#include <iostream>
#include "sources/Chain.h"
#include "sources/Pipe.h"
#include "sources/Parsers/PlainDataParser.h"
#include "sources/ContinuousPlane.h"
#include "sources/FixedDistanceChainRecalculator.h"
#include <math.h>

using namespace std;
using namespace GNEB;

#define PIPE false


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

int main()
{
	Chain *chain = new Chain(); 
	//auto parser = new Parser::PlainDataParser("../data/data1.dat");
	auto plane = PlaneStrategy::getInstance();
    auto cPlane = new ContinuousPlane();
    cPlane->setFunction(func);
    plane->setStrategy(cPlane);
    auto cRecalculator = new FixedDistanceChainRecalculator();
    chain->setFirst(new Point(-2.3, 0, plane->getZ(-2.3, 0)));
    chain->setLast(new Point(2.3, 0, plane->getZ(2.3, 0)));
    chain->calculateInterpolation(3);

    Pipe pipe("../PythonVisualisation/plotFIFO");
    if(PIPE)
    {
        pipe.write(chain->stringify());
    }
    //
    std::vector<Chain> mementoStorage;
    
    int N = 30;

    int i=0;
    while(i < 50)
    {
        std::cout<<"ITERATION: " << i << std::endl;

        for(int i=0;i<chain->size();i++)
        {
            chain->getPoint(i)->iterate();
        }
        for(int i=0;i<chain->size();i++)
        {
            chain->getPoint(i)->moveByTotalForce();
        }
        std::cout<<"BEFORE RECALCULATION: "<<std::endl;
        chain->print();
        
        Chain temp = cRecalculator->recalculateChain(chain);
        double max = 0;
        if(i > N)
        {
            for(int j=0;j<N;j++)
            {
                if(mementoStorage[i - j - 2].length3D() > max)
                    max = mementoStorage[i - j - 2].length3D();
            }
        }
        else
            max = 100;

        std::cout<<"MAX: "<<max<<std::endl;
        if(max >= temp.length3D())
        {
            chain->setCopy(&temp);
            chain->print();
            std::cout<<"this one: "<<chain->length3D()<<std::endl;
            if(PIPE)
            {
                pipe.write(chain->stringify());
            }
        }
        else
        {
            std::cout<<"break happened"<<std::endl;
            //find min
            Chain min = Chain();
            min.setCopy(&mementoStorage[0]);

            for(Chain c: mementoStorage)
            {
                if(c.length3D() < min.length3D())
                {
                    min.setCopy(&c);
                }

            }
            chain->setCopy(&min);
            std::cout<<"algorithms ends after: " << i <<" iterations."<<std::endl;
            break;
        }

        mementoStorage.push_back(*chain);
        for(int k=0; k< i;k++)
        {
            std::cout<<"score: "<<mementoStorage[k].length3D();
        }
        
        i++;
    }

    std::cout<<"===================="<<std::endl;
    for(Chain c: mementoStorage)
    {
        std::cout<<c.length3D()<<std::endl;
    }
    std::cout<<"===================="<<std::endl;
    std::cout<<"len: " << chain->length3D()<<std::endl;
    chain->print();
    if(PIPE)
    {
        pipe.write(chain->stringify());
    }
//    delete pipe;
    return 0;
}
