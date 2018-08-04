#ifndef __VECTOR_STRATEGY_H__
#define __VECTOR_STRATEGY_H__


class Vector
{

	Vector *strategy = nullptr;
protected:
    double x, y, z;

public:
    Vector();
    Vector(double x, double y, double z);
    /*
	Constructor creating vector from 3 points
    */
    Vector(float *tab);
    /*
	tab is array of size 3 - like above 3 consequent parameters are next coordinates describing vector
    */
    Vector(double *tab);

	virtual double operator*(Vector *)=0;
	/*
	 * dot product operator
	 */
	virtual Vector *operator%(Vector *)=0;
	/*
	 * cross product operator
	 */
	virtual double abs()=0;
	/*
	 * Absolute value (length) of vector in 3D cartesian system
	 */
	virtual double operator^(Vector *)=0;
	/*
	 * ^ operator returns angle between 2 vectors in cartesian coordinate system
	 */

    Vector *getStrategy() const;

    void setStrategy(Vector *strategy);

    double getX() const;

    void setX(double x);

    double getY() const;

    void setY(double y);

    double getZ() const;

    void setZ(double z);
};



#endif //__VECTOR_STRATEGY_H__
