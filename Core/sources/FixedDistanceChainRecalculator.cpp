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
    Point *PreviousPoint;
    if(i == 0)
    {
        LineFirstPoint = first;
    }
    else
    {
        LineFirstPoint = chain->getPoint(i - 1);
    }

    if(pointNumber == 0)
    {
        PreviousPoint = first;
    }
    else
    {
        PreviousPoint = &chainCopy[pointNumber - 1];
    }

    outPoint = getDistantPointOnFunction(dl, LineFirstPoint, chain->getPoint(i), PreviousPoint);

    return outPoint;
}


Eigen::Vector3d FixedDistanceChainRecalculator::getDistantPointOnFunction(double len, Point *p1, Point *p2, Point *lPoint)
{
//    std::cout<<"distantPointOnFunction beginning!"<<std::endl;
    double x0 = lPoint->getX(); //middle of circle
    double y0 = lPoint->getY();
    double A = (p1->getY() - p2->getY()) / (p1->getX() - p2->getX());
    double C = p2->getY() - A * p2->getX();
    double repeatingPart = sqrt(pow(A, 2) * pow(len, 2) - pow(A, 2) * pow(x0, 2) - 2*A*C*x0 + 2*A*x0*y0 - pow(C, 2) + 2*C*y0 + pow(len, 2) - pow(y0, 2));
    double x1 = (-A*C + A*y0 + x0 - repeatingPart)/(pow(A, 2) + 1);
    
    double max = p1->getX() >= p2->getX() ? p1->getX() : p2->getX();
    double min = p1->getX() >= p2->getX() ? p2->getX() : p1->getX();
    
    std::function<double(double)> func = getFunctionConnectingPoints(p1, p2);

    //std::cout<<"pointOnFunction: " << "x0: "<<x0<<" y0: "<<y0<<" p1->x: "<<p1->getX() << " p2->x: "<<p2->getX()<<std::endl;

    if(x1 <= max && x1 >= min)
        return Eigen::Vector3d(x1, func(x1), 0);
    
    x1 = (-A*C + A*y0 + x0 + repeatingPart)/(pow(A, 2) + 1);

    if(x1 <= max && x1 >= min) // numeric error more points error is rising
        return Eigen::Vector3d(x1, func(x1), 0);
    
    std::cout<<"FixedDistanceChainRecalculator::getDistantPointOnFunction, LINE: " << __LINE__ << " calculated point in: "<< x1 << " constraints: "<< min << ", " << max <<" "<<std::endl;
    
    if(x1 > max)
    {
  //      std::cout<<"max: "<<max<<std::endl;
        return Eigen::Vector3d(max, func(max), 0);
    }

    if(x1 < min)
    {
//        std::cout<<"min: "<<min<<std::endl;
        return Eigen::Vector3d(min, func(min), 0);
    }
    
    //throw("FixedDistanceChainRecalculator::getDistantPointOnFunction:");
    
    return Eigen::Vector3d(0,0,0); //avoid warning
}

Eigen::Vector3d FixedDistanceChainRecalculator::getDistantPointOnFunction(double len, Point *p1, Point *p2)
{
    std::cout<<"this should not be happening!"<<std::endl;
    double x0 = p1->getX(); //middle of circle
    double y0 = p1->getY();
    double A = (p1->getY() - p2->getY()) / (p1->getX() - p2->getX());
    double C = p2->getY() - A * p2->getX();
    double repeatingPart = sqrt(pow(A, 2) * pow(len, 2) - pow(A, 2) * pow(x0, 2) - 2*A*C*x0 + 2*A*x0*y0 - pow(C, 2) + 2*C*y0 + pow(len, 2) - pow(y0, 2));
    double x1 = (-A*C + A*y0 + x0 - repeatingPart)/(pow(A, 2) + 1);
    
    double max = p1->getX() >= p2->getX() ? p1->getX() : p2->getX();
    double min = p1->getX() >= p2->getX() ? p2->getX() : p1->getX();
    
    std::function<double(double)> func = getFunctionConnectingPoints(p1, p2);

    if(x1 <= max*1.1 && x1 >= min*1.1)
        return Eigen::Vector3d(x1, func(x1), 0);
    
    x1 = (-A*C + A*y0 + x0 + repeatingPart)/(pow(A, 2) + 1);

    if(x1 <= max*1.1 && x1 >= min*1.1)
        return Eigen::Vector3d(x1, func(x1), 0);
    
    std::cout<<"FixedDistanceChainRecalculator::getDistantPointOnFunction, LINE: " << __LINE__ << " calculated point in: "<< x1 << " constraints: "<< p1->getX() << ", " << p2->getX() <<" "<<std::endl;
    throw("FixedDistanceChainRecalculator::getDistantPointOnFunction:");
    return Eigen::Vector3d(0,0,0); //avoid warning
}

std::deque<MovingImage> FixedDistanceChainRecalculator::recalculateChain()
{
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
