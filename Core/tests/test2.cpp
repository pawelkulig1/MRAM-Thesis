#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Hello
#include <boost/test/unit_test.hpp>
#include "../Parsers/PlainDataParser.h"
#include "../Plane.h"
//#include "../MovingImage.h"
#include "../Chain.h"
#include "../Point.h"



//BOOST_AUTO_TEST_SUITE(whole_suite)

BOOST_AUTO_TEST_CASE(testParser) {
   //Parser::PlainDataParser *parser = new Parser::PlainDataParser("tests/data.dat");
   //parser->parse();


   Plane *p = Plane::getInstance();
   BOOST_CHECK_EQUAL(p->getPoints().size(), 0);
   /*BOOST_CHECK_EQUAL(parser->getXSize(), 10);
   BOOST_CHECK_EQUAL(parser->getYSize(), 10);
   BOOST_CHECK_CLOSE(parser->getXpos(), 0, 1e-5);
   BOOST_CHECK_CLOSE(parser->getYpos(), 0, 1e-5);
   BOOST_CHECK_CLOSE(parser->getDx(), 1, 1e-5);
   BOOST_CHECK_CLOSE(parser->getDy(), 1, 1e-5);*/
   //delete parser;
}


BOOST_AUTO_TEST_CASE(testParser2) {
   Parser::PlainDataParser *parser = new Parser::PlainDataParser("tests/data2.dat");
   try
   {
       //parser->parse();
   }
   catch(...)
   {
       
   }
   //BOOST_CHECK_EQUAL(parser->parse().size(), 0);
   //delete parser;
}


BOOST_AUTO_TEST_CASE(testParser3) {
   Parser::PlainDataParser *parser = new Parser::PlainDataParser("tests/data.dat");
   Plane *plane = Plane::getInstance();
   plane->initializeWithParser(parser);

   BOOST_CHECK_EQUAL(plane->getXnum(), 10);
   BOOST_CHECK_EQUAL(plane->getYnum(), 10);
   BOOST_CHECK_EQUAL(plane->getXpos(), 0);
   BOOST_CHECK_EQUAL(plane->getYpos(), 0);
   BOOST_CHECK_EQUAL(plane->getZpos(), 0);
   BOOST_CHECK_EQUAL(plane->getDx(), 1);
   BOOST_CHECK_EQUAL(plane->getDy(), 1);
   BOOST_CHECK_EQUAL(plane->getPoints().size(), 10);
   BOOST_CHECK_EQUAL(plane->getPoints()[0].size(), 10);
   delete parser;
   plane = nullptr;
}

BOOST_AUTO_TEST_CASE(testPoint1) {
   Point *m = new Point(0, 0, 0);
   BOOST_CHECK_EQUAL(m->getVector(), Eigen::Vector3d(0, 0, 0));
   delete m;
}

BOOST_AUTO_TEST_CASE(testMovingImageCorrect)
{
    MovingImage *mi = new MovingImage(1, 1, 1);
}

BOOST_AUTO_TEST_CASE(testMovingImageCorrectDerivative)
{
    auto plane = Plane::getInstance();
    auto point = plane->getPointXY(1,1);
    double z = point->getZ();

    MovingImage *mi = new MovingImage(1, 1, z);

    mi->print();
    double error = 1;
    BOOST_CHECK_CLOSE(mi->calculateDerivative()[0], 1, error); 
    BOOST_CHECK_CLOSE(mi->calculateDerivative()[1], 10, error); 
    BOOST_CHECK_CLOSE(mi->calculateDerivative()[2], 0, error); 
}

BOOST_AUTO_TEST_CASE(testMovingImageCorrectTau)
{
    double z = Plane::getInstance()->getPointXY(2, 2)->getZ();
    double z_next = Plane::getInstance()->getPointXY(2, 3)->getZ();
    double z_prev = Plane::getInstance()->getPointXY(2, 1)->getZ();

    
    MovingImage *mi = new MovingImage(2, 2, z);
    MovingImage *mi_next = new MovingImage(2, 3, z_next);
    MovingImage *mi_prev = new MovingImage(2, 1, z_prev);
    
    mi->setNext(mi_next);
    mi->setPrevious(mi_prev);
    double error = 10; //percent of error TODO check values

    BOOST_CHECK_CLOSE(mi->calculateTau()[0], 0, error); //TODO calculate if correct
    BOOST_CHECK_CLOSE(mi->calculateTau()[1], 0.1, error);//TODO calculate if correct
    BOOST_CHECK_CLOSE(mi->calculateTau()[2], 1, error); //TODO calculate if correct
}

BOOST_AUTO_TEST_CASE(testMovingImageCorrectTangent)
{
    double z = Plane::getInstance()->getPointXY(2, 2)->getZ();
    double z_next = Plane::getInstance()->getPointXY(2, 3)->getZ();
    double z_prev = Plane::getInstance()->getPointXY(2, 1)->getZ();

    
    MovingImage *mi = new MovingImage(2, 2, z);
    MovingImage *mi_next = new MovingImage(2, 3, z_next);
    MovingImage *mi_prev = new MovingImage(2, 1, z_prev);
    
    mi->setNext(mi_next);
    mi->setPrevious(mi_prev);
    double error = 10; //percent of error TODO check values

    BOOST_CHECK_CLOSE(mi->calculateTangent()[0], -1, error); //TODO calculate if correct
    BOOST_CHECK_CLOSE(mi->calculateTangent()[1], -9.9, error);//TODO calculate if correct
    BOOST_CHECK_CLOSE(mi->calculateTangent()[2], 1, error); //TODO calculate if correct
}

BOOST_AUTO_TEST_CASE(testMovingImageCorrectSpring)
{
    double z = Plane::getInstance()->getPointXY(3, 3)->getZ();
    double z_next = Plane::getInstance()->getPointXY(4, 4)->getZ();
    double z_prev = Plane::getInstance()->getPointXY(1, 1)->getZ(); 
    MovingImage *mi = new MovingImage(3, 3, z);
    MovingImage *mi_next = new MovingImage(4, 4, z_next);
    MovingImage *mi_prev = new MovingImage(1, 1, z_prev);
    mi->print();
    mi_next->print();
    mi_prev->print();
    mi->setNext(mi_next);
    mi->setPrevious(mi_prev);
    std::cout<<mi->calculateTau()<<std::endl;
    double error = 1; //percent of error TODO check values
    BOOST_CHECK_CLOSE(mi->calculateSpring()[0], -1, error); //TODO calculate if correct
    BOOST_CHECK_CLOSE(mi->calculateSpring()[1], -1, error);//TODO calculate if correct
    BOOST_CHECK_CLOSE(mi->calculateSpring()[2], -11, error); //TODO calculate if correct
}


BOOST_AUTO_TEST_CASE(testMovingImageCorrectTotalForce)
{

    double z = Plane::getInstance()->getPointXY(3, 3)->getZ();
    double z_next = Plane::getInstance()->getPointXY(4, 4)->getZ();
    double z_prev = Plane::getInstance()->getPointXY(1, 1)->getZ(); 
    MovingImage *mi = new MovingImage(3, 3, z);
    MovingImage *mi_next = new MovingImage(4, 4, z_next);
    MovingImage *mi_prev = new MovingImage(1, 1, z_prev);
    mi->setNext(mi_next);
    mi->setPrevious(mi_prev);
    double error = 1; //percent of error TODO check values
    Eigen::Vector3d temp = mi->iterate();
    BOOST_CHECK_CLOSE(temp[0], -0.09, error); //TODO calculate if correct
    BOOST_CHECK_CLOSE(temp[1], 8.91, error);//TODO calculate if correct
    BOOST_CHECK_CLOSE(temp[2], -12, error); //TODO calculate if correct
}


BOOST_AUTO_TEST_CASE(testChain1) {
    Chain *c = Chain::getInstance();
    Parser::PlainDataParser *parser = new Parser::PlainDataParser("tests/data.dat");
    Plane *plane = Plane::getInstance();
    plane->initializeWithParser(parser);
    
    c->setFirst(plane->getPointXY(2, 2));
    c->setLast(plane->getPointXY(8, 8));
   
    BOOST_CHECK_EQUAL(c->getFirst()->getX(), 2);
    BOOST_CHECK_EQUAL(c->getFirst()->getY(), 2);
    BOOST_CHECK_EQUAL(c->getLast()->getX(), 8);
    BOOST_CHECK_EQUAL(c->getLast()->getY(), 8);

    delete parser;
}

BOOST_AUTO_TEST_CASE(testChainInterpolation)
{
    Chain *c = Chain::getInstance();
    Parser::PlainDataParser *parser = new Parser::PlainDataParser("tests/data.dat");
    Plane *plane = Plane::getInstance();
    plane->initializeWithParser(parser);

    c->setFirst(plane->getPointXY(8, 1));
    c->setLast(plane->getPointXY(8, 8));
   
    c->calculateInterpolation(6);
    

    auto it = c->begin();
    auto temp = plane->getPointXY(8, 2);
    BOOST_CHECK_EQUAL(it++->getVector(), temp->getVector());
    
    temp = plane->getPointXY(8, 3);
    BOOST_CHECK_EQUAL(it++->getVector(), temp->getVector());

    temp = plane->getPointXY(8, 4);
    BOOST_CHECK_EQUAL(it++->getVector(), temp->getVector());

    temp = plane->getPointXY(8, 5);
    BOOST_CHECK_EQUAL(it++->getVector(), temp->getVector());

    temp = plane->getPointXY(8, 6);
    BOOST_CHECK_EQUAL(it++->getVector(), temp->getVector());

    temp = plane->getPointXY(8, 7);
    BOOST_CHECK_EQUAL(it++->getVector(), temp->getVector());

    delete parser;
}

BOOST_AUTO_TEST_CASE(testChainNextAndPrevious)
{
    int SIZE = 24;
    double startX = 8;
    double startY = 1;
    double endX = 2;
    double endY = 1;

    Chain *c = Chain::getInstance();
    Parser::PlainDataParser *parser = new Parser::PlainDataParser("tests/data.dat");
    Plane *plane = Plane::getInstance();
    plane->initializeWithParser(parser);

    c->setFirst(plane->getPointXY(startX, startY));
    c->setLast(plane->getPointXY(endX, endY));
   
    c->calculateInterpolation(SIZE);

    auto it = c->begin();
    auto it_next = it + 1;

    c->getFirst()->print();
    for(auto it2 = c->begin();it2<c->end();it2++)
        it2->print();
    c->getLast()->print();
    
    
    BOOST_CHECK_EQUAL(it->previous->getVector(), c->getFirst()->getVector());
    BOOST_CHECK_EQUAL(it++->next->getVector(), it_next++->getVector());
    
    auto it_prev = c->begin();
    for(int i=0;i<SIZE-2;i++)
    {
        BOOST_CHECK_EQUAL(it->previous->getVector(), it_prev++->getVector());
        BOOST_CHECK_EQUAL(it++->next->getVector(), it_next++->getVector());
    }

    BOOST_CHECK_EQUAL(it->previous->getVector(), it_prev++->getVector());
    BOOST_CHECK_EQUAL(it->next->getVector(), c->getLast()->getVector());

    delete parser;
}



BOOST_AUTO_TEST_CASE(testChainXhAndYh)
{
    int SIZE = 24;
    double startX = 8;
    double startY = 1;
    double endX = 5;
    double endY = 5;
    Chain *c = Chain::getInstance();
    Parser::PlainDataParser *parser = new Parser::PlainDataParser("tests/data.dat");
    Plane *plane = Plane::getInstance();
    plane->initializeWithParser(parser);

    c->setFirst(plane->getPointXY(startX, startY));
    c->setLast(plane->getPointXY(endX, endY));
   
    c->calculateInterpolation(SIZE);
    auto it = c->begin();

    Point *tempX_h;
    Point *tempY_h;

    for(int i=0;i<SIZE-2;i++)
    {
        tempX_h = plane->getPointXY(it->getX() + 1, it->getY());
        tempY_h = plane->getPointXY(it->getX(), it->getY() + 1);
        BOOST_CHECK(*(it->x_h) == *(tempX_h));
        BOOST_CHECK(*(it++->y_h) == *(tempY_h));
    }

    delete parser;
}

//TODO test chain bad data

