#include "FixedDistanceChainRecalculator.h"
#include "Point.h"
#include "Chain.h"
#include "StationaryImage.h"

FixedDistanceChainRecalculator::FixedDistanceChainRecalculator() : AbstractChainRecalculator()
{
    normalMode = true;
}

Eigen::Vector3d FixedDistanceChainRecalculator::findNumberOfFunction(int pointNumber)
{
    //auto chain = Chain::getInstance();
    StationaryImage *first = chainCopy.getFirst();
    //auto last = originalChain->getLast();

    double cLen = chainCopy.length2D();

    double dl = cLen / (chainCopy.size() + 1); // +1 because chain is chain + 2 (first and last) and number of lines connecting n points is n - 1

    int i = 0; 
    double distSum = Point::distanceBetweenPoints2D(first, chainCopy.at(0));
    double prevDistSum = 0;

    while(dl * (pointNumber + 1) >= distSum)
    {
        if(i == chainCopy.size() - 1)
            break;
        prevDistSum = distSum;
        distSum += Point::distanceBetweenPoints2D(chainCopy.at(i), chainCopy.at(i+1));
        i++;
    }

    //get proper output 
    Eigen::Vector3d outPoint;
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

    if(i == chainCopy.size()-1)
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
        PreviousPoint = chainCopy.at(pointNumber - 1);
    }

    outPoint = getDistantPointOnFunction(dl, LineFirstPoint, LineSecondPoint, PreviousPoint);

    return outPoint;
}


Eigen::Vector3d FixedDistanceChainRecalculator::getDistantPointOnFunction(double len, Point *p1, Point *p2, Point *lPoint)
{
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

    double underSqrt = pow(A, 2) * pow(len,2) - pow(A, 2) * pow(x0, 2) - 2 * A * B * x0 * y0 - 2 * A * C * x0 + pow(B, 2) * pow(len, 2) - pow(B, 2) * pow(y0, 2) - 2 * B * C * y0 - pow(C, 2);

    if(underSqrt < 0) //possible if there are no such points on real plane - this meand previous point was set incorectly
    {
        throw std::string("NaN value");
    }

    //now if we now we are safe calculate sqrt
    double repeatingPart = sqrt(underSqrt);

    //final results: 
    double x1 = (-A * B * y0 - A * C + pow(B, 2) * x0 - B * repeatingPart)/(pow(A, 2) + pow(B, 2));
    double y1 = (pow(A, 2) * y0 - A * B * x0 + A * repeatingPart - B*C)/(pow(A, 2) + pow(B, 2));
    double x2 = (-A * B * y0 - A * C + pow(B, 2) * x0 + B * repeatingPart)/(pow(A, 2) + 1);
    double y2 = (pow(A, 2) * y0 - A * B * x0 - A * repeatingPart - B*C)/(pow(A, 2) + pow(B, 2));

    Eigen::Vector3d chainDirection = getChainDirection(); //to pick one solution i decided to use chainDirection algorithm, in most cases it fits.

    double retX = 0;
    double retY = 0;
    
    // two formulas so to versions of chainDirection algorithm (y and x asix)
    if(A == 1 && B != -1)
    {
        //y chooses
        if(chainDirection[1] > 0)
        {
            retX = x1;
            retY = y1;

            if(!normalMode)
            {
                retX = x2;
                retY = y2;
            }
        }
        else
        {
            retX = x2;
            retY = y2;

            if(!normalMode)
            {
                retX = x1;
                retY = y1;
            }
        }
    }
    else
    { 
        if(chainDirection[0] > 0)
        {
            retX = x1;
            retY = y1;
            if(!normalMode)
            {
                retX = x2;
                retY = y2;
            }
        }
        else
        {
            retX = x2;
            retY = y2;

            if(!normalMode)
            {
                retX = x1;
                retY = y1;
            }
        }
    }
    
    return Eigen::Vector3d(retX, retY, 0);
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
    for(int i=0;i<chainCopy.size();i++)
    {
        try{
            tempVec = findNumberOfFunction(i);
        }
        catch(std::string s)
        {
            if(s == "NaN value") //last point was setup not properly, we have to correct it.
            {
                std::cout<<"BACK IN TIME!"<<std::endl;
                i--;
                *chainCopy.getPoint(i) = *originalChain->getPoint(i); //for calculation we have to restore position of that point to initial value
                normalMode = false; //inverses chainDirection algorithm, function will pick other point now
                tempVec = findNumberOfFunction(i); //calculate once again.
                normalMode = true; //disable inversion
            }
        }
        chainCopy.getPoint(i)->moveToCords(tempVec[0], tempVec[1]);
    }
    chainCopy.print();
    return chainCopy;
}
