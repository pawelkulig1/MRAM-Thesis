#ifndef __VECTOR_STRATEGY_H__
#define __VECTOR_STRATEGY_H__

class Vector
{
	Vector *strategy = nullptr;

public:
	Vector();
	virtual double operator*(Vector *)=0;
	/*
	 * dot product operator
	 */
	virtual Vector operator%(Vector *)=0;
	/*
	 * cross product operator
	 */
	virtual double abs(Vector *)=0;
	/*
	 * Absolute value (length) of vector in 3D cartesian system
	 */
	virtual double operator^(Vector *)=0;
	/*
	 * ^ operator returns angle between 2 vectors in cartesian coordinate system
	 */
};



#endif //__VECTOR_STRATEGY_H__
