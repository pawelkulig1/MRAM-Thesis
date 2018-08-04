#include <string>
#include "myVector.h"

using namespace GNEB;


//double MyVector::getLength()
//{
//	double temp[3] = {xb - xe, yb - ye, zb - ze};
//	/*TODO Make temp static*/
//	return sqrt(temp[0] * temp[0] + temp[1] * temp[1] + temp[2] * temp[2]);
//}
//
//double MyVector::angleBetweenVectors(MyVector *v1, MyVector *v2)
//{
//	return acos(((*v1) * v2)/(v1->getLength() * v2->getLength()));
//}
//
//double MyVector::operator*(MyVector *v2)
//{
//	return ((xb - xe) * (v2->xb - v2->xe)) + \
//			((yb - ye) * (v2->yb - v2->ye)) + \
//			((zb - ze) * (v2->zb - v2->ze));
//}
//
//MyVector MyVector::operator%(MyVector *v2)
//{
//	//this->getLength() * v2->getLength() * sin(angleBetweenVectors(this, v2));
//	return *this;
//}

MyVector::MyVector() {
    x = 0;
    y = 0;
    z = 0;
}


MyVector::MyVector(double x, double y, double z) {

}

MyVector::MyVector(float *tab) {

}

MyVector::MyVector(double *tab) {

}

double MyVector::operator*(Vector *vector) {

    return ((x * vector->getX()) + (y * vector->getY()) + (z * vector->getZ()));
}

Vector *MyVector::operator%(Vector *vector) {
    throw (std::string("Not implemented yet"));
//    return *vector;
}

double MyVector::abs() {
    return sqrt(x * x + y * y + z * z);
}

double MyVector::operator^(Vector *vector) {
    return acos(((*this) * vector) / (abs() * vector->abs()));
}


