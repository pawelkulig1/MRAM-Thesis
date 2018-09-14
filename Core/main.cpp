#include <iostream>
#include "Chain.h"
#include "defines.h"
#include "Pipe.h"
using namespace std;
using namespace GNEB;

int main()
{
	Chain *c = Chain::getInstance();
	Parser::PlainDataParser *parser = new Parser::PlainDataParser("../data/data1.dat");
	Plane *plane = Plane::getInstance();
	plane->initializeWithParser(parser);
	c->setFirst(plane->getPointXY(-0.9182, -1.499));
	c->setLast(plane->getPointXY(0, 1.54));
    c->calculateInterpolation(6);
    Pipe *pipe = new Pipe("../PythonVisualisation/plotFIFO");
    pipe->write(c->stringify());
    for(int i=0;i<20;i++)
    {
        for(auto it=c->begin();it<c->end();it++)
        {
            it->iterate();
        }

        for(auto it=c->begin();it<c->end();it++)
        {
            it->moveByTotalForce();
        }
        pipe->write(c->stringify());
        cout<<"=================================="<<std::endl;
    }

    delete pipe;
    cout<<endl;
}
