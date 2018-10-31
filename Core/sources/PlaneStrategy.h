#pragma once
#include "AbstractPlane.h"

namespace GNEB
{
    class Point;
//    class AbstractPlane;
    class ParserInterface;

    class PlaneStrategy
    {
    private:
        static PlaneStrategy *instance;
        AbstractPlane *strategy;
        PlaneStrategy();

    public:
        static PlaneStrategy *getInstance();
        void setStrategy(AbstractPlane *pl);
        AbstractPlane *getStrategy();

        void throwIfStrategyNotSet();
        Eigen::Vector3d calculateDerivative(double x, double y);
        Eigen::Vector3d calculateDerivative(Point *p);
        double getZ(Point *p);
        double getZ(double x, double y);
        Point *getClosestPoint(double x, double y);
        Point *getClosestPoint(Point *p);
        void initializeWithParser(ParserInterface *pi);


    };
}
