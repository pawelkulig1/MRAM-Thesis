#ifndef __STATIONARY_IMAGE_H__
#define __STATIONARY_IMAGE_H__

#include "Point.h"
#include <string>

namespace GNEB
{
    class StationaryImage : public Point
    {
    public:
        StationaryImage(double x, double y, double z);
        void setX(double x) override ;
        void setY(double y) override ;
        void setZ(double z) override ;
        void print() override ;
    };
}


#endif // __STATIONARY_IMAGE_H__
