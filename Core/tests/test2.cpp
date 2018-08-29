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
   Parser::PlainDataParser *parser = new Parser::PlainDataParser("tests/data.dat");
   //parser->parse();

   /*BOOST_CHECK_EQUAL(parser->getXSize(), 10);
   BOOST_CHECK_EQUAL(parser->getYSize(), 10);
   BOOST_CHECK_CLOSE(parser->getXpos(), 0, 1e-5);
   BOOST_CHECK_CLOSE(parser->getYpos(), 0, 1e-5);
   BOOST_CHECK_CLOSE(parser->getDx(), 1, 1e-5);
   BOOST_CHECK_CLOSE(parser->getDy(), 1, 1e-5);*/
   delete parser;
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
   delete parser;
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

}

BOOST_AUTO_TEST_CASE(testParser4) {
   Point *m = new Point(0, 0, 0);
   BOOST_CHECK_EQUAL(m->getVector(), Eigen::Vector3d(0, 0, 0));
   delete m;
}


BOOST_AUTO_TEST_CASE(testParser5) {
   Chain *c = Chain::getInstance();
   Parser::PlainDataParser *parser = new Parser::PlainDataParser("tests/data.dat");
   Plane *plane = Plane::getInstance();
   plane->initializeWithParser(parser);
   //delete plane;
   //delete c;
   //delete parser;
//    MovingImage *mi = new MovingImage(1, 2, 3);
//    mi->getX();
//    StationaryImage *st = new StationaryImage(1, 2, 3);
   //st->getX();
   //c->setFirst(plane->getPointXY(8, 1));
   //c->setLast(plane->getPointXY(8, 8));
   //BOOST_CHECK_EQUAL(c->getFirst()->getX(), 8);
   //BOOST_CHECK_EQUAL(c->getFirst()->getY(), 1);
   //BOOST_CHECK_EQUAL(c->getLast()->getX(), 8);
   //BOOST_CHECK_EQUAL(c->getLast()->getY(), 8);

}
//}
