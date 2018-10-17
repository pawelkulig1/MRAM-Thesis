#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Hello

#include <boost/test/unit_test.hpp>

#include "../sources/PlaneStrategy.h"
#include "../sources/Chain.h"
#include "../sources/ContinuousPlane.h"
#include "../sources/FixedDistanceChainRecalculator.h"

double exampleFunction(double x, double y)
{
    return 0;
}

BOOST_AUTO_TEST_CASE(SimpleLineRecalculation)
{
    /*auto plane = PlaneStrategy::getInstance();
    auto chain = Chain::getInstance();
    auto cPlane = new ContinuousPlane();
    auto chainRecalculator = new FixedDistanceChainRecalculator();
    cPlane->setFunction(exampleFunction);
    plane->setStrategy(cPlane);
    chain->setChainRecalculator(chainRecalculator);
    chain->setFirst(new Point(-3, 2, 0));
    chain->setLast(new Point(3, 2, 0));
    chain->addToChain(new MovingImage(-2, 2, 0));
    chain->addToChain(new MovingImage(-0, 2, 0));
    chain->addToChain(new MovingImage(2, 2, 0));
    chain->resetImages();

    BOOST_CHECK_EQUAL(chain->getPoint(0)->getX(), -1.5);
    BOOST_CHECK_EQUAL(chain->getPoint(0)->getY(), 2);
    BOOST_CHECK_EQUAL(chain->getPoint(0)->getZ(), 0);
    
    BOOST_CHECK_EQUAL(chain->getPoint(1)->getX(), 0);
    BOOST_CHECK_EQUAL(chain->getPoint(1)->getY(), 2);
    BOOST_CHECK_EQUAL(chain->getPoint(1)->getZ(), 0);

    BOOST_CHECK_EQUAL(chain->getPoint(2)->getX(), 1.5);
    BOOST_CHECK_EQUAL(chain->getPoint(2)->getY(), 2);
    BOOST_CHECK_EQUAL(chain->getPoint(2)->getZ(), 0);*/
}

BOOST_AUTO_TEST_CASE(HeavyLineRecalculation)
{ 
    auto plane = PlaneStrategy::getInstance();
    auto chain = Chain::getInstance();
    auto cPlane = new ContinuousPlane();
    auto chainRecalculator = new FixedDistanceChainRecalculator();
    chain->clearChain();
    cPlane->setFunction(exampleFunction);
    plane->setStrategy(cPlane);
    chain->setChainRecalculator(chainRecalculator);
    chain->setFirst(new Point(-3, 2, 0));
    chain->setLast(new Point(3, 2, 0));
  
    //chain->print();

    int amount = 23;

    double dx = 6.0 / (amount + 2);
    std::cout<<dx<<std::endl;
    for(int i=0;i<=amount;i++)
    {
        chain->addToChain(new MovingImage(-3.0 + dx * (i + 1.0), 2, 0));
    }
    
    //chain->print();
    chain->resetImages();
    double error = 1;

    for(int i=0;i<=amount;i++)
    {
        BOOST_CHECK_CLOSE(chain->getPoint(i)->getX(), -3.0 + dx * (i + 1.0), error);
        BOOST_CHECK_EQUAL(chain->getPoint(i)->getY(), 2);
    }
    //chain->print();
}


BOOST_AUTO_TEST_CASE(SimpleCurveRecalculation)
{
    /*auto plane = PlaneStrategy::getInstance();
    auto chain = Chain::getInstance();
    auto cPlane = new ContinuousPlane();
    auto chainRecalculator = new FixedDistanceChainRecalculator();
    chain->clearChain();
    cPlane->setFunction(exampleFunction);
    plane->setStrategy(cPlane);
    chain->setChainRecalculator(chainRecalculator);
    chain->setFirst(new Point(-3, 2, 0));
    chain->setLast(new Point(3, 2, 0));
    chain->addToChain(new MovingImage(-2, 1, 0));
    chain->addToChain(new MovingImage(0, 0, 0));
    chain->addToChain(new MovingImage(2, 1, 0));
    //chain->print();
    chain->resetImages();
    chain->print();

    double error = 10;

    BOOST_CHECK_CLOSE(chain->getPoint(0)->getX(), -1.617, error);
    BOOST_CHECK_CLOSE(chain->getPoint(0)->getY(), 0.809, error);
    BOOST_CHECK_CLOSE(chain->getPoint(0)->getZ(), 0, error);
    
    BOOST_CHECK_CLOSE(chain->getPoint(1)->getX(), 0.025, error);
    BOOST_CHECK_CLOSE(chain->getPoint(1)->getY(), 0.012, error);
    BOOST_CHECK_CLOSE(chain->getPoint(1)->getZ(), 0, error);

    BOOST_CHECK_CLOSE(chain->getPoint(2)->getX(), 1.617, error);
    BOOST_CHECK_CLOSE(chain->getPoint(2)->getY(), 0.809, error);
    BOOST_CHECK_CLOSE(chain->getPoint(2)->getZ(), 0, error);*/

}

BOOST_AUTO_TEST_CASE(MediumCurveRecalculation)
{ 
/*
    auto plane = PlaneStrategy::getInstance();
    auto chain = Chain::getInstance();
    auto cPlane = new ContinuousPlane();
    auto chainRecalculator = new FixedDistanceChainRecalculator();
    chain->clearChain(); //need for tests because of singleton
    cPlane->setFunction(exampleFunction);
    plane->setStrategy(cPlane);
    chain->setChainRecalculator(chainRecalculator);
    chain->setFirst(new Point(-3, 2, 0));
    chain->setLast(new Point(3, 2, 0));
    chain->addToChain(new MovingImage(-2.5, 1.5, 0));
    chain->addToChain(new MovingImage(-2,   1,   0));
    chain->addToChain(new MovingImage(-1.5, 0.8, 0));
    chain->addToChain(new MovingImage(-1,   0.5, 0));
    chain->addToChain(new MovingImage(0,    0,   0));
    chain->addToChain(new MovingImage(1,    0.3, 0));
    chain->addToChain(new MovingImage(1.5,  0.8, 0));
    chain->addToChain(new MovingImage(2,    1,   0));
    chain->addToChain(new MovingImage(2.5,  1.5, 0));
    chain->resetImages();

    double error = 10;

    BOOST_CHECK_CLOSE(chain->getPoint(0)->getX(), -2.5, error);
    BOOST_CHECK_CLOSE(chain->getPoint(0)->getY(), 1.5, error);
    BOOST_CHECK_CLOSE(chain->getPoint(0)->getZ(), 0, error);
    
    BOOST_CHECK_CLOSE(chain->getPoint(1)->getX(), -2, error);
    BOOST_CHECK_CLOSE(chain->getPoint(1)->getY(), 1, error);
    BOOST_CHECK_CLOSE(chain->getPoint(1)->getZ(), 0, error);

    BOOST_CHECK_CLOSE(chain->getPoint(2)->getX(), -1.27, error);
    BOOST_CHECK_CLOSE(chain->getPoint(2)->getY(), 0.65, error);
    BOOST_CHECK_CLOSE(chain->getPoint(2)->getZ(), 0, error);
    
    BOOST_CHECK_CLOSE(chain->getPoint(3)->getX(), -0.62, error);
    BOOST_CHECK_CLOSE(chain->getPoint(3)->getY(), 0.314, error);
    BOOST_CHECK_CLOSE(chain->getPoint(3)->getZ(), 0, error);
    
    BOOST_CHECK_CLOSE(chain->getPoint(4)->getX(), 0.025, error);
    BOOST_CHECK_CLOSE(chain->getPoint(4)->getY(), 0.012, error);
    BOOST_CHECK_CLOSE(chain->getPoint(4)->getZ(), 0, error);

    BOOST_CHECK_CLOSE(chain->getPoint(5)->getX(), 1, error);
    BOOST_CHECK_CLOSE(chain->getPoint(5)->getY(), 0.4, error);
    BOOST_CHECK_CLOSE(chain->getPoint(5)->getZ(), 0, error);

    BOOST_CHECK_CLOSE(chain->getPoint(6)->getX(), -1.617, error);
    BOOST_CHECK_CLOSE(chain->getPoint(6)->getY(), 0.809, error);
    BOOST_CHECK_CLOSE(chain->getPoint(6)->getZ(), 0, error);
    
    BOOST_CHECK_CLOSE(chain->getPoint(7)->getX(), 0.025, error);
    BOOST_CHECK_CLOSE(chain->getPoint(7)->getY(), 0.012, error);
    BOOST_CHECK_CLOSE(chain->getPoint(7)->getZ(), 0, error);

    BOOST_CHECK_CLOSE(chain->getPoint(8)->getX(), 1.617, error);
    BOOST_CHECK_CLOSE(chain->getPoint(8)->getY(), 0.809, error);
    BOOST_CHECK_CLOSE(chain->getPoint(8)->getZ(), 0, error);*/
}

