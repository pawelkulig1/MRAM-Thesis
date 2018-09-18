#pragma once
#include <Eigen/Dense>
#include "Parsers/PlainDataParser.h"

using namespace Parser;

namespace GNEB
{
    class Point;
    class ParserInterface;
    class AbstractPlane
    {
    public:
        virtual Eigen::Vector3d calculateDerivative(double x, double y) = 0;
        virtual Eigen::Vector3d calculateDerivative(Point *p) = 0;
        virtual double getZ(double x, double y) = 0;
        virtual double getZ(Point *p) = 0;
        virtual Point *getClosestPoint(double x, double y) = 0;
        virtual Point *getClosestPoint(Point *p) = 0;
        virtual void initializeWithParser(ParserInterface *pi) = 0;
    };
}
