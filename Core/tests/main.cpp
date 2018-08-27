#include <iostream>
#include "Plane.h"
#include "Parsers/PlainDataParser.h"
#include <deque>
#include <assert.h>
#include "MovingImage.h"

using namespace std;
using namespace GNEB;

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

void TestPlainParserProperFile(string path)
{
    Parser::PlainDataParser *parser = new Parser::PlainDataParser(path);
    parser->parse();
    assert(parser->getXSize() == 10);
    assert(parser->getYSize() == 10);
    assert(parser->getXpos() == 0);
    assert(parser->getYpos() == 0);
    assert(parser->getDx() == 1);
    assert(parser->getDy() == 1);
    delete parser;
    parser = nullptr;
    std::cout<<"[PASSED]"<<std::endl;
}

void TestPlainParserWrongFile(string path)
{
    Parser::PlainDataParser *parser = new Parser::PlainDataParser(path);
    assert(parser->parse().size() == 0);
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

    assert(plane->getXnum() == 10);
    assert(plane->getYnum() == 10);
    assert(plane->getXpos() == 0);
    assert(plane->getYpos() == 0);
    assert(plane->getZpos() == 0);
    assert(plane->getDx() == 1);
    assert(plane->getDy() == 1);
    assert(plane->getPoints().size() == 10);
    assert(plane->getPoints()[0].size() == 10);
}

void TestMovingImageFunctions()
{
    MovingImage *m = new MovingImage(1,2,3);
    assert(m->getVector() == Eigen::Vector3d(1,2,3));
    std::cout<<"[PASSED]"<<std::endl;
}
