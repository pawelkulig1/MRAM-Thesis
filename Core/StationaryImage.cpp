#include "StationaryImage.h"

using namespace GNEB;

StationaryImage::StationaryImage(double x, double y, double z): x(x), y(y), z(z) {}

double StationaryImage::getX()
{
	return this->x;
}

double StationaryImage::getY()
{
	return this->y;
}

double StationaryImage::getZ()
{
	return this->z;
}

void StationaryImage::setX(double)
{
	throw("Error in StationaryImage.cpp::setX(double) const value cannot be changed!");
}

void StationaryImage::setY(double)
{
	throw("Error in StationaryImage.cpp::setY(double) const value cannot be changed!");
}

void StationaryImage::setZ(double)
{
	throw("Error in StationaryImage.cpp::setZ(double) const value cannot be changed!");
}

