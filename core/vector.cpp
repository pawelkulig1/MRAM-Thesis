#include "vector.h"

using namespace GNEB;


Vector::Vector(double xb, double yb, double zb, double xe, double ye, double ze) : 
		xb(xb), yb(yb), zb(zb), xe(xe), ye(ye), ze(ze) 
{
}

Vector::Vector(float *tab):
		xb(tab[0]), yb(tab[1]), zb(tab[2]), xe(tab[3]), ye(tab[4]), ze(tab[5]) 
{
}

Vector::Vector(double *tab):
		xb(tab[0]), yb(tab[1]), zb(tab[2]), xe(tab[3]), ye(tab[4]), ze(tab[5]) 
{
}

double Vector::getLength()
{
	double temp[3] = {xb - xe, yb - ye, zb - ze};
	/*TODO Make temp static*/
	return sqrt(temp[0] * temp[0] + temp[1] * temp[1] + temp[2] * temp[2]);
}

double Vector::angleBetweenVectors(Vector *v1, Vector *v2)
{
	return acos(((*v1) * v2)/(v1->getLength() * v2->getLength()));
}

double Vector::operator*(Vector *v2)
{
	return ((xb - xe) * (v2->xb - v2->xe)) + \
			((yb - ye) * (v2->yb - v2->ye)) + \
			((zb - ze) * (v2->zb - v2->ze));
}

Vector Vector::operator%(Vector *v2)
{
	//this->getLength() * v2->getLength() * sin(angleBetweenVectors(this, v2));
	return *this;
}
