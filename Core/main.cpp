#include <iostream>
#include "Chain.h"
#include "Parsers/PlainDataParser.h"
#include "Point.h"
#include <deque>
#include "Plane.h"


using namespace std;
using namespace GNEB;

int main()
{
	Chain *c = Chain::getInstance();	
	Parser::PlainDataParser *parser = new Parser::PlainDataParser("tests/data.dat");
	Plane *plane = Plane::getInstance();
	plane->initializeWithParser(parser);
	c->setFirst(plane->getPointXY(8, 1));
	c->setLast(plane->getPointXY(8, 8));
    c->calculateInterpolation(6);
    for_each(c->begin(), c->end(), [](MovingImage p){p.print();});
    cout<<endl;
    for_each(c->begin(), c->end(), [](MovingImage p){p.iterate();});	
    for_each(c->begin(), c->end(), [](MovingImage p){p.print();});
    cout<<endl;

}
