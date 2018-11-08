#pragma once
#define BOOST_TEST_DYN_LINK
// #define BOOST_TEST_MODULE "C++ Unit Tests for My Thesis" //needed for standalone module

#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>

#include "../sources/Chain.h"
#include "../sources/PlaneStrategy.h"
#include "../sources/ContinuousPlane.h"

#include "exampleFunction.h"


BOOST_DATA_TEST_CASE(BasicChain, params)
{
    Chain *c1 = new Chain();

    ContinuousPlane cp = funcNum(sample);
    PlaneStrategy::getInstance()->setStrategy(&cp);

    c1->setFirst(new Point(-3, -3, 0));
    c1->setLast(new Point(3, 3, 0));
    c1->addToChain(new MovingImage(1,1,1));
    c1->addToChain(new MovingImage(-1,-1,1));
    c1->addToChain(new MovingImage(2,2,1));
    
    BOOST_CHECK_EQUAL(c1->at(0)->getX(), 1);
    BOOST_CHECK_EQUAL(c1->at(0)->getY(), 1);
    BOOST_CHECK_EQUAL(c1->at(0)->getZ(), PlaneStrategy::getInstance()->getZ(1,1));

    BOOST_CHECK_EQUAL(c1->at(1)->getX(), -1);
    BOOST_CHECK_EQUAL(c1->at(1)->getY(), -1);
    BOOST_CHECK_EQUAL(c1->at(1)->getZ(), PlaneStrategy::getInstance()->getZ(-1,-1));

    BOOST_CHECK_EQUAL(c1->at(2)->getX(), 2);
    BOOST_CHECK_EQUAL(c1->at(2)->getY(), 2);
    BOOST_CHECK_EQUAL(c1->at(2)->getZ(), PlaneStrategy::getInstance()->getZ(2,2));

    delete c1;
}

BOOST_DATA_TEST_CASE(testChainInterpolation, params)
{
    Chain *c = new Chain();

    PlaneStrategy *planeStrategy = PlaneStrategy::getInstance();

    ContinuousPlane cp = funcNum(sample);
    planeStrategy->setStrategy(&cp);

    c->setFirst(planeStrategy->getClosestPoint(8, 1));
    c->setLast(planeStrategy->getClosestPoint(8, 8));
    c->calculateInterpolation(6);
    
    auto it = c->begin();
    auto temp = planeStrategy->getClosestPoint(8, 2);
    BOOST_CHECK_EQUAL(it++->getVector(), temp->getVector());
    
    temp = planeStrategy->getClosestPoint(8, 3);
    BOOST_CHECK_EQUAL(it++->getVector(), temp->getVector());

    temp = planeStrategy->getClosestPoint(8, 4);
    BOOST_CHECK_EQUAL(it++->getVector(), temp->getVector());

    temp = planeStrategy->getClosestPoint(8, 5);
    BOOST_CHECK_EQUAL(it++->getVector(), temp->getVector());

    temp = planeStrategy->getClosestPoint(8, 6);
    BOOST_CHECK_EQUAL(it++->getVector(), temp->getVector());

    temp = planeStrategy->getClosestPoint(8, 7);
    BOOST_CHECK_EQUAL(it++->getVector(), temp->getVector());

    delete c;
}

BOOST_DATA_TEST_CASE(testChainLenght2D, params)
{
    Chain *c = new Chain();

    ContinuousPlane cp = funcNum(sample);
    PlaneStrategy::getInstance()->setStrategy(&cp);

    c->setFirst(PlaneStrategy::getInstance()->getClosestPoint(1, 1));
    c->setLast(PlaneStrategy::getInstance()->getClosestPoint(8, 8));
    c->calculateInterpolation(6);
    
    double error = 0.01;
    BOOST_CHECK_CLOSE(c->length2D(), 9.899, error);
    delete c;
}

BOOST_AUTO_TEST_CASE(testChainLenght3D)
{
    Chain *c = new Chain();

    ContinuousPlane *cPlane = new ContinuousPlane();
    cPlane->setFunction(exampleFunction);
    PlaneStrategy *planeStrategy = PlaneStrategy::getInstance();
    planeStrategy->setStrategy(cPlane);

    c->setFirst(planeStrategy->getClosestPoint(1, 1));
    c->setLast(planeStrategy->getClosestPoint(8, 8));
    c->calculateInterpolation(6);

    double error = 0.01;
    BOOST_CHECK_CLOSE(c->length3D(), 9.899, error);
    delete c;
    delete cPlane;
}

BOOST_DATA_TEST_CASE(testChainInterpolation2, params)
{
    Chain *c = new Chain();

    PlaneStrategy *planeStrategy = PlaneStrategy::getInstance();

    ContinuousPlane cp = funcNum(sample);
    planeStrategy->setStrategy(&cp);

    c->setFirst(planeStrategy->getClosestPoint(1, 1));
    c->setLast(planeStrategy->getClosestPoint(8, 8));
    c->calculateInterpolation(6);
    
    auto it = c->begin();
    auto temp = planeStrategy->getClosestPoint(2, 2);
    BOOST_CHECK_EQUAL(it++->getVector(), temp->getVector());
    
    temp = planeStrategy->getClosestPoint(3, 3);
    BOOST_CHECK_EQUAL(it++->getVector(), temp->getVector());

    temp = planeStrategy->getClosestPoint(4, 4);
    BOOST_CHECK_EQUAL(it++->getVector(), temp->getVector());

    temp = planeStrategy->getClosestPoint(5, 5);
    BOOST_CHECK_EQUAL(it++->getVector(), temp->getVector());

    temp = planeStrategy->getClosestPoint(6, 6);
    BOOST_CHECK_EQUAL(it++->getVector(), temp->getVector());

    temp = planeStrategy->getClosestPoint(7, 7);
    BOOST_CHECK_EQUAL(it++->getVector(), temp->getVector());

    delete c;
}

BOOST_AUTO_TEST_CASE(testChainErase)
{
    Chain *c = new Chain();

    ContinuousPlane *cPlane = new ContinuousPlane();
    cPlane->setFunction(exampleFunction);
    PlaneStrategy *planeStrategy = PlaneStrategy::getInstance();
    planeStrategy->setStrategy(cPlane);

    c->setFirst(planeStrategy->getClosestPoint(1, 1));
    c->setLast(planeStrategy->getClosestPoint(8, 8));
    c->calculateInterpolation(6);
    
    c->erase();

    double error = 0.01;
    BOOST_CHECK_EQUAL(c->size(), 0);
    delete c;
    delete cPlane;
}

BOOST_DATA_TEST_CASE(testChainPointerCopy, params)
{
    Chain *c1 = new Chain();
    Chain *c2 = new Chain();

    ContinuousPlane cp = funcNum(sample);
    PlaneStrategy::getInstance()->setStrategy(&cp);

    c1->setFirst(new Point(-3, -3, 0));
    c1->setLast(new Point(3, 3, 0));
    
    c1->calculateInterpolation(5);

    c2->setCopy(c1);

    for(int i=0;i<c1->size();i++)
    {
        BOOST_CHECK_EQUAL(c1->at(i)->getX(), c2->at(i)->getX());
        BOOST_CHECK_EQUAL(c1->at(i)->getY(), c2->at(i)->getY());
        BOOST_CHECK_EQUAL(c1->at(i)->getZ(), c2->at(i)->getZ());
    }

    delete c1;
    delete c2;
}

BOOST_DATA_TEST_CASE(testChainCopy, params)
{
    Chain c1;
    Chain c2;

    ContinuousPlane cp = funcNum(sample);
    PlaneStrategy::getInstance()->setStrategy(&cp);

    c1.setFirst(new Point(-3, -3, 0));
    c1.setLast(new Point(3, 3, 0));
    
    c1.calculateInterpolation(5);

    c2.setCopy(c1);

    for(int i=0;i<c1.size();i++)
    {
        BOOST_CHECK_EQUAL(c1.at(i)->getX(), c2.at(i)->getX());
        BOOST_CHECK_EQUAL(c1.at(i)->getY(), c2.at(i)->getY());
        BOOST_CHECK_EQUAL(c1.at(i)->getZ(), c2.at(i)->getZ());
    }

}


