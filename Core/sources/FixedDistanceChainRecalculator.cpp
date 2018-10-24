#include "FixedDistanceChainRecalculator.h"
#include "Point.h"
#include "Chain.h"
#include "StationaryImage.h"

FixedDistanceChainRecalculator::FixedDistanceChainRecalculator() : AbstractChainRecalculator()
{

}

std::function<double(double)> FixedDistanceChainRecalculator::getFunctionConnectingPoints(Point *p1, Point *p2){
    if(p1->getX() == p2->getX()) //cannot use simplified equation
    {
        double tempX = p1->getX();
        return [tempX](double x){return tempX;};
    }
    else
    {
        double a, b;
        a = (p1->getY() - p2->getY()) / (p1->getX() - p2->getX());
        b = p2->getY() - a * p2->getX();
        return [a, b](double x){return a * x + b;};
    }
}

Eigen::Vector3d FixedDistanceChainRecalculator::findNumberOfFunction(int pointNumber)
{
    auto chain = Chain::getInstance();
    auto first = chain->getFirst();
    auto last = chain->getLast();

    double cLen = chain->length();

    double dl = cLen / (chainCopy.size() + 1); // +1 because chain is chain + 2 (first and last) and number of lines connecting n points is n - 1
   
    //std::cout<<"cLen: "<<cLen<<std::endl;

    int i = 0; 
    double distSum = distanceBetweenPoints(first, &chainCopy[0]);
    double prevDistSum = 0;

    while(dl * (pointNumber + 1) >= distSum)
    {
        if(i == chainCopy.size() - 1)
            break;
        prevDistSum = distSum;
        distSum += distanceBetweenPoints(&chainCopy[i], &chainCopy[i+1]);
        i++;
    }

    //get proper output 
    Eigen::Vector3d outPoint;
    Point *LineFirstPoint;
    Point *LineSecondPoint;
    Point *PreviousPoint;
    std::cout<<"i: "<<i<<std::endl;
    if(i == 0)
    {
        LineFirstPoint = first;
    }
    else
    {
        LineFirstPoint = chain->getPoint(i - 1);
    }

    if(i == chainCopy.size()-1)
    {
        LineSecondPoint = chain->getLast();
    }
    else
    {
        LineSecondPoint = chain->getPoint(i);
    }

    if(pointNumber == 0)
    {
        PreviousPoint = first;
    }
    else
    {
        PreviousPoint = &chainCopy[pointNumber - 1];
    }

    outPoint = getDistantPointOnFunction(dl, LineFirstPoint, LineSecondPoint, PreviousPoint);

    return outPoint;
}


Eigen::Vector3d FixedDistanceChainRecalculator::getDistantPointOnFunction(double len, Point *p1, Point *p2, Point *lPoint)
{
    double x0 = lPoint->getX(); //middle of circle
    double y0 = lPoint->getY();
    double A = (p1->getY() - p2->getY()) / (p1->getX() - p2->getX());
    double C = p2->getY() - A * p2->getX();
    double B = -1;

    /*if(p1->getX() == p2->getX()){ //TODO
        B = 0;
        A = -1;
        C = p1->getX();
    }*/
    double repeatingPart = sqrt(pow(A, 2) * pow(len,2) - pow(A, 2) * pow(x0, 2) - 2 * A * B * x0 * y0 - 2 * A * C * x0 + 
            pow(B, 2) * pow(len, 2) - pow(B, 2) * pow(y0, 2) - 2 * B * C * y0 - pow(C, 2));
    double x1 = (-A * B * y0 - A * C + pow(B, 2) * x0 - B * repeatingPart)/(pow(A, 2) + pow(B, 2));
    
    std::function<double(double)> func = getFunctionConnectingPoints(p1, p2);

    if(getChainDirection()[0] > 0) //increasing x
    {
        return Eigen::Vector3d(x1, func(x1), 0);
    }
    else
    {
        x1 = (-A * B * y0 - A * C + pow(B, 2) * x0 + B * repeatingPart)/(pow(A, 2) + 1);
        return Eigen::Vector3d(x1, func(x1), 0);
    }
    return Eigen::Vector3d(0,0,0); //avoid warning
}

Eigen::Vector3d FixedDistanceChainRecalculator::getChainDirection()
{
    auto chain = Chain::getInstance();
    return chain->getLast()->getVector() - chain->getFirst()->getVector();
}

std::deque<MovingImage> FixedDistanceChainRecalculator::recalculateChain()
{
    chainCopy.erase(chainCopy.begin(), chainCopy.end());
    auto chain = Chain::getInstance();
    for(int i=0;i<chain->size();i++)
    {
        chainCopy.push_back(*chain->getPoint(i));
    }
   // double cLen = chain->length();
    Eigen::Vector3d tempVec;
    for(int i=0;i<chainCopy.size();i++)
    {
        tempVec = findNumberOfFunction(i);
        chainCopy[i].moveToCords(tempVec[0], tempVec[1]);
    }

    return chainCopy;
}
