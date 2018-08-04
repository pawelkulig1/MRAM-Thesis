#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <cmath>

#include "vector.h"

namespace GNEB {
    class MyVector : public Vector {

    public:
        MyVector();

        MyVector(double x, double y, double z);

        MyVector(float *tab);

        MyVector(double *tab);

        double operator*(Vector *vector) override;

        Vector *operator%(Vector *vector) override;

        double abs() override;

        double operator^(Vector *vector) override;
    };
}
#endif
