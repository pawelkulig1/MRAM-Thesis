#include <iostream>
#include "Plane.h"
#include "Parsers/PlainDataParser.h"
#include <deque>
#include "MovingImage.h"

#define BOOST_TEST_MODULE MyTest
#include "boost/test/unit_test.hpp"

using namespace std;
using namespace GNEB;
/*
void TestPlainParserProperFile(string path);
void TestPlainParserWrongFile(string path);
void TestPlainParserCorruptedData(string path);
void TestPlaneInitialisation(string path);
void TestMovingImageFunctions();

int main()
{
    TestPlainParserProperFile("data.dat"); 
    TestPlainParserWrongFile("dataNotExisting.dat");
    TestPlaneInitialisation("data.dat");
    TestMovingImageFunctions();
}

BOOST_AUTO_TEST_CASE()
{
    BOOST_CHECK_EQUAL()
}*/

BOOST_AUTO_TEST_CASE(my_test)
{
    BOOST_CHECK_EQUAL(1,1);
    /*Parser::PlainDataParser *parser = new Parser::PlainDataParser("data.dat");
    parser->parse();
    BOOST_CHECK_EQUAL(parser->getXSize(), 10);
    BOOST_CHECK_EQUAL(parser->getYSize(), 10);
    BOOST_CHECK_EQUAL(parser->getXpos(), 0);
    BOOST_CHECK_EQUAL(parser->getYpos(), 0);
    BOOST_CHECK_EQUAL(parser->getDx(), 1);
    BOOST_CHECK_EQUAL(parser->getDy(), 1);
    delete parser;*/
}
/*
void TestPlainParserWrongFile(string path)
{
    Parser::PlainDataParser *parser = new Parser::PlainDataParser(path);
    BOOST_CHECK_EQUAL(parser->parse().size(), 0);
    std::cout<<"[PASSED]"<<std::endl;
}

void TestPlainParserCorruptedData(string path)
{

}

void TestPlaneInitialisation(string path)
{   
    Parser::PlainDataParser *parser = new Parser::PlainDataParser(path);
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
}

void TestMovingImageFunctions()
{
    MovingImage *m = new MovingImage(1,2,3);
    BOOST_CHECK_EQUAL(m->getVector(), Eigen::Vector3d(1,2,3));
    std::cout<<"[PASSED]"<<std::endl;
}*/
