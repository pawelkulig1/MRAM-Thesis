#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Hello

#include <boost/test/unit_test.hpp>

#include "../sources/PlaneStrategy.h"
#include "../sources/Chain.h"
#include "../sources/ContinuousPlane.h"
#include "../sources/FixedDistanceChainRecalculator.h"

//#define TEST 1


double exampleFunction(double x, double y)
{
    return 0;
}

BOOST_AUTO_TEST_CASE(SimpleLineRecalculation)
{
    auto plane = PlaneStrategy::getInstance();
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
    BOOST_CHECK_EQUAL(chain->getPoint(2)->getZ(), 0);
}

BOOST_AUTO_TEST_CASE(SimpleLineRecalculation2)
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
    chain->addToChain(new MovingImage(1.9, 2, 0));
    chain->addToChain(new MovingImage(2, 2, 0));
    chain->addToChain(new MovingImage(2.1, 2, 0));
    chain->resetImages();

    BOOST_CHECK_EQUAL(chain->getPoint(0)->getX(), -1.5);
    BOOST_CHECK_EQUAL(chain->getPoint(0)->getY(), 2);
    BOOST_CHECK_EQUAL(chain->getPoint(0)->getZ(), 0);
    
    BOOST_CHECK_EQUAL(chain->getPoint(1)->getX(), 0);
    BOOST_CHECK_EQUAL(chain->getPoint(1)->getY(), 2);
    BOOST_CHECK_EQUAL(chain->getPoint(1)->getZ(), 0);

    BOOST_CHECK_EQUAL(chain->getPoint(2)->getX(), 1.5);
    BOOST_CHECK_EQUAL(chain->getPoint(2)->getY(), 2);
    BOOST_CHECK_EQUAL(chain->getPoint(2)->getZ(), 0);
}

BOOST_AUTO_TEST_CASE(SimpleVerticalLineRecalculation)
{
    auto plane = PlaneStrategy::getInstance();
    auto chain = Chain::getInstance();
    auto cPlane = new ContinuousPlane();
    auto chainRecalculator = new FixedDistanceChainRecalculator();
    chain->clearChain();
    cPlane->setFunction(exampleFunction);
    plane->setStrategy(cPlane);
    chain->setChainRecalculator(chainRecalculator);
    chain->setFirst(new Point(0, 0, 0));
    chain->setLast(new Point(0, 4, 0));
    chain->addToChain(new MovingImage(0, 1, 0));
    chain->addToChain(new MovingImage(0, 2, 0));
    chain->addToChain(new MovingImage(0, 3, 0));
    chain->resetImages();

    BOOST_CHECK_EQUAL(chain->getPoint(0)->getX(), 0);
    BOOST_CHECK_EQUAL(chain->getPoint(0)->getY(), 1);
    BOOST_CHECK_EQUAL(chain->getPoint(0)->getZ(), 0);
    
    BOOST_CHECK_EQUAL(chain->getPoint(1)->getX(), 0);
    BOOST_CHECK_EQUAL(chain->getPoint(1)->getY(), 2);
    BOOST_CHECK_EQUAL(chain->getPoint(1)->getZ(), 0);

    BOOST_CHECK_EQUAL(chain->getPoint(2)->getX(), 0);
    BOOST_CHECK_EQUAL(chain->getPoint(2)->getY(), 3);
    BOOST_CHECK_EQUAL(chain->getPoint(2)->getZ(), 0);
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
  
    int amount = 101;

    double dx = 6.0 / (amount + 1);
    for(int i=0;i<amount;i++)
    {
        chain->addToChain(new MovingImage(-3.0 + dx * (i + 1.0), 2, 0));
    }
    
    chain->resetImages();
    double error = 1;

    for(int i=0;i<amount;i++)
    {
        if(i == amount/2 && amount%2 == 1){
            BOOST_CHECK_SMALL(chain->getPoint(i)->getX(), 0.01);
            BOOST_CHECK_EQUAL(chain->getPoint(i)->getY(), 2);
            continue;
        }

        BOOST_CHECK_CLOSE(chain->getPoint(i)->getX(), -3.0 + dx * (i + 1.0), error);
        BOOST_CHECK_EQUAL(chain->getPoint(i)->getY(), 2);
    }
}

BOOST_AUTO_TEST_CASE(HeavyLineRecalculationMove)
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
  
    int amount = 21;

    double dx = 6.0 / (amount + 1);
    double er = 0.2;
    for(int i=0;i<amount;i++)
    {
        chain->addToChain(new MovingImage(-3.0 + dx * (i + 1.0) + er, 2, 0));
    }
    
    chain->resetImages();
    double error = 1;

    for(int i=0;i<amount;i++)
    {
        if(i == amount/2 && amount%2 == 1){
            BOOST_CHECK_SMALL(chain->getPoint(i)->getX(), 0.01);
            BOOST_CHECK_EQUAL(chain->getPoint(i)->getY(), 2);
            continue;
        }
        BOOST_CHECK_CLOSE(chain->getPoint(i)->getX(), -3.0 + dx * (i + 1.0), error);
        BOOST_CHECK_EQUAL(chain->getPoint(i)->getY(), 2);
    }
}

BOOST_AUTO_TEST_CASE(HeavyLineRecalculationBothAxes)
{ 
    auto plane = PlaneStrategy::getInstance();
    auto chain = Chain::getInstance();
    auto cPlane = new ContinuousPlane();
    auto chainRecalculator = new FixedDistanceChainRecalculator();
    chain->clearChain();
    cPlane->setFunction(exampleFunction);
    plane->setStrategy(cPlane);
    chain->setChainRecalculator(chainRecalculator);
    chain->setFirst(new Point(-5, -2, 0));
    chain->setLast(new Point(5, 2, 0));
  
    int amount = 101;

    double dy = 4.0 / (amount + 1);
    double dx = 10.0 / (amount + 1);
    for(int i=0;i<amount;i++)
    {
        chain->addToChain(new MovingImage(-5.0 + dx * (i + 1), -2.0 + dy * (i + 1),  0));
    }
    
    chain->resetImages();
    double error = 1;

    for(int i=0;i<amount;i++)
    {
        if(i == amount/2 && amount%2 == 1){
            BOOST_CHECK_SMALL(chain->getPoint(i)->getX(), 0.01);
            BOOST_CHECK_SMALL(chain->getPoint(i)->getY(), 0.01);
            continue;
        }
        BOOST_CHECK_CLOSE(chain->getPoint(i)->getX(), -5.0 + dx * (i + 1), error);
        BOOST_CHECK_CLOSE(chain->getPoint(i)->getY(), -2.0 + dy * (i + 1.0), error);
    }
}


BOOST_AUTO_TEST_CASE(SimpleCurveRecalculation)
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
    chain->addToChain(new MovingImage(-2, 1, 0));
    chain->addToChain(new MovingImage(0, 0, 0));
    chain->addToChain(new MovingImage(2, 1, 0));

    chain->resetImages();

    double error = 10;

    BOOST_CHECK_CLOSE(chain->getPoint(0)->getX(), -1.617, error);
    BOOST_CHECK_CLOSE(chain->getPoint(0)->getY(), 0.809, error);
    BOOST_CHECK_CLOSE(chain->getPoint(0)->getZ(), 0, error);
    
    BOOST_CHECK_SMALL(chain->getPoint(1)->getX(), 0.1);
    BOOST_CHECK_SMALL(chain->getPoint(1)->getY(), 0.1);
    BOOST_CHECK_SMALL(chain->getPoint(1)->getZ(), 0.01);

    BOOST_CHECK_CLOSE(chain->getPoint(2)->getX(), 1.617, error);
    BOOST_CHECK_CLOSE(chain->getPoint(2)->getY(), 1, error);
    BOOST_CHECK_CLOSE(chain->getPoint(2)->getZ(), 0, error);
}

BOOST_AUTO_TEST_CASE(MediumCurveRecalculation)
{ 
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
    
    BOOST_CHECK_SMALL(chain->getPoint(4)->getX(), 0.1);
    BOOST_CHECK_SMALL(chain->getPoint(4)->getY(), 0.1);
    BOOST_CHECK_SMALL(chain->getPoint(4)->getZ(), 0.1);

    BOOST_CHECK_CLOSE(chain->getPoint(5)->getX(), 0.74, error);
    BOOST_CHECK_CLOSE(chain->getPoint(5)->getY(), 0.22, error);
    BOOST_CHECK_CLOSE(chain->getPoint(5)->getZ(), 0, error);

    BOOST_CHECK_CLOSE(chain->getPoint(6)->getX(), 1.35, error);
    BOOST_CHECK_CLOSE(chain->getPoint(6)->getY(), 0.64, error);
    BOOST_CHECK_CLOSE(chain->getPoint(6)->getZ(), 0, error);
    
    BOOST_CHECK_CLOSE(chain->getPoint(7)->getX(), 2, error);
    BOOST_CHECK_CLOSE(chain->getPoint(7)->getY(), 1, error);
    BOOST_CHECK_CLOSE(chain->getPoint(7)->getZ(), 0, error);

    BOOST_CHECK_CLOSE(chain->getPoint(8)->getX(), 2.51, error);
    BOOST_CHECK_CLOSE(chain->getPoint(8)->getY(), 1.51, error);
    BOOST_CHECK_CLOSE(chain->getPoint(8)->getZ(), 0, error);
}

BOOST_AUTO_TEST_CASE(NanVerification)
{

    auto plane = PlaneStrategy::getInstance();
    auto chain = Chain::getInstance();
    auto cPlane = new ContinuousPlane();
    auto chainRecalculator = new FixedDistanceChainRecalculator();
    chain->clearChain(); //need for tests because of singleton
    cPlane->setFunction(exampleFunction);
    plane->setStrategy(cPlane);
    chain->setChainRecalculator(chainRecalculator);
    chain->setFirst(new Point(-2.3, 0, 1.13846));
    chain->setLast(new Point(2.3, 0, -0.600892));
    chain->addToChain(new MovingImage(-2.21443, 1.32455, 2.47805));
    chain->addToChain(new MovingImage(-0.978451, 1.98929, 1.06334));
    chain->addToChain(new MovingImage(0.170001, 2.56238, -0.0307538));
    chain->addToChain(new MovingImage(1.44751, 2.2412, -0.0844369));
    chain->addToChain(new MovingImage(1.98865, 1.08761, -0.291743));
    chain->resetImages();
    
    double error =10000;

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
    
    BOOST_CHECK_SMALL(chain->getPoint(4)->getX(), 0.1);
    BOOST_CHECK_SMALL(chain->getPoint(4)->getY(), 0.1);
    BOOST_CHECK_SMALL(chain->getPoint(4)->getZ(), 0.1);
}

