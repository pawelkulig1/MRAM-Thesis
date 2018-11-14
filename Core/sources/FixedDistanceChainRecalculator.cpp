#include "FixedDistanceChainRecalculator.h"
#include "Point.h"
#include "Chain.h"
#include "StationaryImage.h"
#include <time.h>
#include <memory>
#include <utility>

#define DEBUG false

FixedDistanceChainRecalculator::FixedDistanceChainRecalculator() : AbstractChainRecalculator()
{
    normalMode = true;
}

Chain FixedDistanceChainRecalculator::findNumberOfFunction(int pointNumber, Chain chain)
{
    if(pointNumber > chain.size() - 1)
        return chain;
    //auto chain = Chain::getInstance();
    StationaryImage *first = chain.getFirst();
    //auto last = originalChain->getLast();

    double cLen = originalChain->length2D();

    double dl = cLen / (chain.size() + 1); // +1 because chain is chain + 2 (first and last) and number of lines connecting n points is n - 1

    int i = 0; 
    double distSum = Point::distanceBetweenPoints2D(first, chain.at(0));
    double prevDistSum = 0;

    while(dl * (pointNumber + 1) >= distSum)
    {
        if(i == chain.size() - 1)
            break;
        prevDistSum = distSum;
        distSum += Point::distanceBetweenPoints2D(chain.at(i), chain.at(i+1));
        i++;
    }

    if(DEBUG)
        std::cout<<"DL: " << dl << std::endl;

    //get proper output 
    Point *LineFirstPoint;
    Point *LineSecondPoint;
    Point *PreviousPoint;
    
    if(i == 0)
    {
        LineFirstPoint = first;
    }
    else
    {
        LineFirstPoint = originalChain->getPoint(i - 1);
    }

    if(i == chain.size()-1)
    {
        LineSecondPoint = originalChain->getLast();
    }
    else
    {
        LineSecondPoint = originalChain->getPoint(i);
    }

    if(pointNumber == 0)
    {
        PreviousPoint = first;
    }
    else
    {
        PreviousPoint = chain.at(pointNumber - 1);
    }

    Eigen::Vector3d outPoint1, outPoint2;


    std::vector<std::pair<double, double>> outPoints;
    outPoints = getDistantPointOnFunction(dl, LineFirstPoint, LineSecondPoint, PreviousPoint);
    //normalMode = false;
    //outPoints = getDistantPointOnFunction(dl, LineFirstPoint, LineSecondPoint, PreviousPoint);
    //normalMode = true;

    if(DEBUG)
    {
        std::cout<<"outPoint 1: "<<outPoint1<<std::endl;
        std::cout<<"outPoint 2: "<<outPoint2<<std::endl;
    }

    Chain temp;
    if(outPoints.size() != 0)
    {
        outPoint1 = Eigen::Vector3d(std::get<0>(outPoints[0]), std::get<1>(outPoints[0]), 0);
        chain.getPoint(pointNumber)->moveToCords(outPoint1[0], outPoint1[1]);
        if(DEBUG)
        {
            std::cout<<"outPoint1 if: "<<std::endl;
            chain.print();
        }
        temp = findNumberOfFunction(pointNumber + 1, chain);
        if(checkChainIntegrity(temp))
        {
            return temp;
        }
    }
    
    if(outPoints.size() != 0)
    { 
        outPoint2 = Eigen::Vector3d(std::get<0>(outPoints[1]), std::get<1>(outPoints[1]), 0);
        chain.getPoint(pointNumber)->moveToCords(outPoint2[0], outPoint2[1]);
        if(DEBUG)
        {
            std::cout<<"outPoint2 if: "<<std::endl;
            chain.print();
        }
        
        temp = findNumberOfFunction(pointNumber + 1, chain);
        if(checkChainIntegrity(temp))
            return temp;
    }

    return chain;
}

bool FixedDistanceChainRecalculator::checkChainIntegrity(Chain c)
{
    //checks if all distances between points is dl +- 0.1
    double error = 0.1;
    double dl = c.length2D()/(c.size()+1);
    if((Point::distanceBetweenPoints2D(c.getFirst(), c.getPoint(0)) + error) < dl ||
           (Point::distanceBetweenPoints2D(c.getFirst(), c.getPoint(0)) - error) > dl) 
        return false;

    if((Point::distanceBetweenPoints2D(c.getLast(), c.getPoint(c.size() - 1)) + error) < dl ||
           (Point::distanceBetweenPoints2D(c.getLast(), c.getPoint(c.size() - 1)) - error) > dl) 
        return false;

    for(int i=0;i<c.size() - 1;i++)
    {
        if((Point::distanceBetweenPoints2D(c.getPoint(i), c.getPoint(i + 1)) + error) < dl ||
           (Point::distanceBetweenPoints2D(c.getPoint(i), c.getPoint(i + 1)) - error) > dl) 
        return false;
    }

    return true;
}


std::vector<std::pair<double, double>> FixedDistanceChainRecalculator::getDistantPointOnFunction(double len, Point *p1, Point *p2, Point *lPoint)
{
    std::vector<std::pair<double, double>> ret;
    //p1 is point we are going to move, circle middle is in lPoint.
    double x0 = lPoint->getX(); //middle of circle
    double y0 = lPoint->getY();
    double A = (p1->getY() - p2->getY()) / (p1->getX() - p2->getX());
    double C = p2->getY() - A * p2->getX();
    double B = -1;

    //problem with vertical line occured A-> inf, algorithm has to calculate if A will be in nice range and if not, it uses other formulas.
    double delta = 0.1;
    double dx = abs(p1->getX() - p2->getX());
    double dy = abs(p1->getY() - p2->getY());

    if(p1->getX() - delta < p2->getX() && p1->getX() + delta >= p2->getX() && dx*(1/delta) < dy)
    {
        A = 1;
        B = (-p1->getX() + p2->getX())/(p1->getY() - p2->getY());
        C = (p1->getX()*p2->getY() - p2->getX()*p1->getY())/(p1->getY() - p2->getY());
    }

    double A2 = pow(A, 2);
    double B2 = pow(B, 2);
    double C2 = pow(C, 2);
    double x02 = pow(x0, 2);
    double len2 = pow(len, 2);
    double y02 = pow(y0, 2);
    
    double underSqrt = A2*len2 - A2*x02 - 2*A*B*x0*y0 - 2*A*C*x0 + B2*len2 - B2*y02 - 2*B*C*y0 - C2;  //A2 * len2 - A2 * x02 - 2 * A * B * x0 * y0 - 2 * A * x0 + B2 * len2 - B2 * y02 - 2 * B * y0 - 1;
    
    if(DEBUG)
    {
        std::cout<<"A: " << A <<" B: " << B << " x0: " << x0 << " y0: " << y0 << "under sqrt: " << underSqrt <<std::endl;
        std::cout<<"p1:";
        p1->print();
        std::cout<<"p2: ";
        p2->print();
        std::cout<<"lPoint: ";
        lPoint->print();
    }

    if(underSqrt < 0) //possible if there are no such points on real plane - this meand previous point was set incorectly
    {
        if(DEBUG)
        {
            std::cout<<"under sqrt < 0"<<std::endl;
        }
        return ret;
    }

    //now if we now we are safe calculate sqrt
    double repeatingPart = sqrt(underSqrt);

    //final results: 
    //TODO
    double x1 = (-A * B * y0 - A * C + B2 * x0 - B * repeatingPart)/(A2 + B2); 
    double y1 = (pow(A, 2) * y0 - A * B * x0 + A * repeatingPart - B*C)/(A2 + B2);
    double x2 = (-A * B * y0 - A * C + B2 * x0 + B * repeatingPart)/(A2 + B2);
    double y2 = (pow(A, 2) * y0 - A * B * x0 - A * repeatingPart - B*C)/(A2 + B2);

    if(DEBUG)
    {
        std::cout<<"x1: "<<x1 << " y1 :" << y1 << " x2: " << x2 << " y2: " << y2<<std::endl;
    }
    Eigen::Vector3d chainDirection = getChainDirection(); //to pick one solution i decided to use chainDirection algorithm, in most cases it fits.

    double min = p1->getX() <= p2->getX() ? p1->getX() : p2->getX();
    double max = p1->getX() > p2->getX() ? p1->getX() : p2->getX();


    // two formulas to pick versions of chainDirection algorithm (y and x asix)
    if(A == 1 && B != -1)
    {
        //y chooses
        if(chainDirection[1] > 0)
        {
            ret.push_back(std::pair(x1, y1));
            ret.push_back(std::pair(x2, y2));
        }
        else
        {
            ret.push_back(std::pair(x2, y2));
            ret.push_back(std::pair(x1, y1));
        }
    }
    else
    { 
        if(chainDirection[0] > 0)
        {
            ret.push_back(std::pair(x1, y1));
            ret.push_back(std::pair(x2, y2));
        }
        else
        {
            ret.push_back(std::pair(x2, y2));
            ret.push_back(std::pair(x1, y1));
        }
    }
    return ret;
}

Eigen::Vector3d FixedDistanceChainRecalculator::getChainDirection()
{
    return originalChain->getLast()->getVector() - originalChain->getFirst()->getVector();
}

Chain FixedDistanceChainRecalculator::recalculateChain(Chain *originalChain)
{
    this->originalChain = originalChain;
    chainCopy.setCopy(originalChain);

    Eigen::Vector3d tempVec;
    Chain cp;
    cp.setCopy(originalChain);
    return findNumberOfFunction(0, cp);
}

