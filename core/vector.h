#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <cmath>

namespace GNEB
{
	class Vector
	{
	private:
		double xb, yb, zb, xe, ye, ze;
		
    public:
		Vector(double xb, double yb, double zb, double xe, double ye, double ze);
		/*
		 * Constructor creating vector from 6 points - 3 coordinates of starting
		 * point and 3 coordinates of end point 
		 */
		Vector(float *tab);
		/*
		 * *tab is array of size 6 - like above 6 consequent parameters are  next coordinates of 2 points describing vector
		 */
		Vector(double *tab);
		double getLength();
		/*
		 * returns Euclidian length of vector
		 */
		double angleBetweenVectors(Vector *v1, Vector *v2);
		/*
		 * returns angle between two Vectors (ES)
		 */
		Vector operator+(Vector *v2);
		/*
		 * returns pointer to Vector being sum of 2 Vector objects
		 */
		double operator*(Vector *v2);
		/*
		 * dot product of two Vectors
		 */

		Vector operator%(Vector *v2);
		/*
		 * cross product of two Vectors
		 */
	};
}
#endif
