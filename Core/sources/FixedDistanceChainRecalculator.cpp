#include "FixedDistanceChainRecalculator.h"
#include "Point.h"
#include "Chain.h"
#include "StationaryImage.h"

FixedDistanceChainRecalculator::FixedDistanceChainRecalculator() : AbstractChainRecalculator()
{

}

std::function<double(double)> FixedDistanceChainRecalculator::getFunctionConnectingPoints(Point *p1, Point *p2){
    /*if(p1->getX() - delta < p2->getX() && p1->getX() + delta >= p2->getX()) //cannot use simplified equation
    {
        double tempX = p1->getX();
        return [tempX](double x){return tempX;};
    }*/
    //else
    //{
    double a, b;
    a = (p1->getY() - p2->getY()) / (p1->getX() - p2->getX());
    b = p2->getY() - a * p2->getX();
    return [a, b](double x){return a * x + b;};
    //}
}

Eigen::Vector3d FixedDistanceChainRecalculator::findNumberOfFunction(int pointNumber)
{
    auto chain = Chain::getInstance();
    auto first = chain->getFirst();
//    auto last = chain->getLast();

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


Eigen::Vector3d FixedDistanceChainRecalculator::getDistantPointOnFunction(double len, Point *p1, Point *p2, Point *lPoint, bool option = false)
{
    //p1 is point we are going to move, circle middle is in lPoint.
    double x0 = lPoint->getX(); //middle of circle
    double y0 = lPoint->getY();
    double A = (p1->getY() - p2->getY()) / (p1->getX() - p2->getX());
    double C = p2->getY() - A * p2->getX();
    double B = -1;

    double delta = 0.1;
    double dx = abs(p1->getX() - p2->getX());
    double dy = abs(p1->getY() - p2->getY());
    std::cout << "x0: "<< x0 << " y0: " << y0 << " A: " << A << " B: " << B << " C: " << C << " dx: " << dx << " dy: " << dy << " len: " << len << std::endl;
    if(p1->getX() - delta < p2->getX() && p1->getX() + delta >= p2->getX() && dx*10 < dy)
    {
        std::cout<<"here "<<std::endl;

        A = 1;
        B = (-p1->getX() + p2->getX())/(p1->getY() - p2->getY());
        C = (p1->getX()*p2->getY() - p2->getX()*p1->getY())/(p1->getY() - p2->getY()); 
        
    }
    std::cout<<"under sqrt: " << pow(A, 2) * pow(len,2) - pow(A, 2) * pow(x0, 2) - 2 * A * B * x0 * y0 - 2 * A * C * x0 + pow(B, 2) * pow(len, 2) - pow(B, 2) * pow(y0, 2) - 2 * B * C * y0 - pow(C, 2) << std::endl;

    //A**2*r**2 - A**2*x0**2 - 2*A*B*x0*y0 - 2*A*C*x0 + B**2*r**2 - B**2*y0**2 - 2*B*C*y0 - C**2
    double repeatingPart = sqrt(pow(A, 2) * pow(len,2) - pow(A, 2) * pow(x0, 2) - 2 * A * B * x0 * y0 - 2 * A * C * x0 + pow(B, 2) * pow(len, 2) - pow(B, 2) * pow(y0, 2) - 2 * B * C * y0 - pow(C, 2));

    double x1 = (-A * B * y0 - A * C + pow(B, 2) * x0 - B * repeatingPart)/(pow(A, 2) + pow(B, 2));
    double y1 = (pow(A, 2) * y0 - A * B * x0 + A * repeatingPart - B*C)/(pow(A, 2) + pow(B, 2));
    double x2 = (-A * B * y0 - A * C + pow(B, 2) * x0 + B * repeatingPart)/(pow(A, 2) + 1);
    double y2 = (pow(A, 2) * y0 - A * B * x0 - A * repeatingPart - B*C)/(pow(A, 2) + pow(B, 2));

    std::cout<<"x1: " << x1 << " y1: " << y1 << " repPart: " << repeatingPart << " p1x: " << p1->getX() <<" p2x: " << p2->getX() << " A: " << A << " p1y: " << p1->getY() << " p2y: " << p2->getY() << std::endl;
    //std::function<double(double)> func = getFunctionConnectingPoints(p1, p2);

    Eigen::Vector3d chainDirection = getChainDirection(); //next point direction? how to guess

    double retX = 0;
    double retY = 0;
    /*Point tempP1(x1, y1, 0);
    Point tempP2(x2, y2, 0);
    double d1 = distanceBetweenPoints(&tempP1, p1);
    double d2 = distanceBetweenPoints(&tempP2, p1);
    std::cout<<"d1: " << d1 << " d2: " << d2 <<std::endl; 
    
    if(d1 >= d2)
    {
        retX = x1;
        retY = y1;
    }
    else
    {
        retX = x2;
        retY = y2;
    }*/


    if(A == 1 && B != -1)
    {
        //y chooses
        if(chainDirection[1] > 0)
        {
            retX = x1;
            retY = y1;
        }
        else
        {
            retX = x2;
            retY = y2;
        }
    }
    else
    { 
        if(chainDirection[0] > 0)
        {
            retX = x1;
            retY = y1;
        }
        else
        {
            retX = x2;
            retY = y2;
        }
    }
    
    std::cout<<"retX: " << retX << " retY: " << retY << std::endl;
    
    return Eigen::Vector3d(retX, retY, 0);


    /*if(chainDirection[0] >= 0 && chainDirection[1] >= 0) //first quarter
    {
        x1 = x1 >= x2 ? x1 : x2;
        y1 = y1 >= y2 ? y1 : y2;
        return Eigen::Vector3d(x1, y1, 0);
    }
    else if(chainDirection[0] < 0 && chainDirection[1] >= 0) //second quarter
    { 
        x1 = x1 < x2 ? x1 : x2;
        y1 = y1 >= y2 ? y1 : y2;
        return Eigen::Vector3d(x1, y1, 0);
    }
    else if(chainDirection[0] >= 0 && chainDirection[1] < 0)
    { 
        x1 = x1 >= x2 ? x1 : x2;
        y1 = y1 < y2 ? y1 : y2;
        return Eigen::Vector3d(x1, y1, 0);
    }
    else if(chainDirection[0] < 0 && chainDirection[1] < 0)
    {
        x1 = x1 < x2 ? x1 : x2;
        y1 = y1 < y2 ? y1 : y2;
        return Eigen::Vector3d(x1, y1, 0);
    }
    else
    {
        throw("This may never happen!"); //TODO
    }*/
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
        std::cout<<"============================================================="<<std::endl;
        chainCopy[i].moveToCords(tempVec[0], tempVec[1]);
    }

    return chainCopy;
}
