#ifndef __STATIONARY_IMAGE_H__
#define __STATIONARY_IMAGE_H__

#include "Point.h"
#include <string>

namespace GNEB
{
    class StationaryImage: public Point
    {
		const double x, y, z;
    public:
        StationaryImage(double x, double y, double z);
		double getX();
		double getY();
		double getZ();
		void setX(double);
		void setY(double);
		void setZ(double);
    };
}


#endif // __STATIONARY_IMAGE_H__
