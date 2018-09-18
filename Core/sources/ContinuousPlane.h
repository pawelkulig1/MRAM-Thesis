#pragma once

#include <deque>
#include <functional>
#include "AbstractPlane.h"

namespace GNEB
{
    class ContinuousPlane: public AbstractPlane
    {
    private:
        std::function<double(double, double)> planeFunction; 
        double dx, dy;

    public:
        ContinuousPlane();
        Eigen::Vector3d calculateDerivative(double x, double y) override;
        Eigen::Vector3d calculateDerivative(Point *p) override;
        double getZ(double x, double y) override;
        double getZ(Point *p) override;
        Point *getClosestPoint(double x, double y) override;
        Point *getClosestPoint(Point *p) override;
        void initializeWithParser(ParserInterface *pi) override;

        void setFunction(std::function<double(double, double)> f);
        //double getD() override;
        //double getDy() override;

    };
}
