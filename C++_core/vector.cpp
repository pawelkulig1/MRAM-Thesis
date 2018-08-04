#include "myVector.h"

using namespace GNEB;


Vector::Vector() {
    x = 0;
    y = 0;
    z = 0;
}

Vector::Vector(double x, double y, double z) : x(x), y(y), z(z) {

}

Vector::Vector(float *tab) : x(tab[0]), y(tab[1]), z(tab[2]) {

}

Vector::Vector(double *tab) : x(tab[0]), y(tab[1]), z(tab[2]) {

}

Vector *Vector::getStrategy() const {
    return strategy;
}

void Vector::setStrategy(Vector *strategy) {
    Vector::strategy = strategy;
}

double Vector::getX() const {
    return x;
}

void Vector::setX(double x) {
    Vector::x = x;
}

double Vector::getY() const {
    return y;
}

void Vector::setY(double y) {
    Vector::y = y;
}

double Vector::getZ() const {
    return z;
}

void Vector::setZ(double z) {
    Vector::z = z;
}
