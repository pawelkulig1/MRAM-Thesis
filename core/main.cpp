#include <iostream>
#include <Eigen/Dense>
#include <array>

#include "vector.h"
#include "planeFunction.h"

#define toDegrees(x) (x * 180 / M_PI)

double func(double x, double y)
{
	return x+y;
}

float func2(float x, float y)
{
	return x*y;
}


int main()
{	

	auto planeFunc = (planeFunction<double>::getInstance());
	planeFunc->setFunction(func);
	std::cout<<(*planeFunc)(1,2)<<std::endl;

	auto plane2 = planeFunction<double>::getInstance();

	plane2->setFunction(func2);
	std::cout<<(*plane2)(1,2)<<std::endl;
	std::cout<<(*planeFunc)(1,2)<<std::endl;

	// planeFunction<double>();
	// int x = planeFunction<double>::dupa;
	//func->
	// const int Q = 5;
	// std::array<Eigen::Vector3d, Q> R;
	// R[0] = Eigen::Vector3d(0, 1, 0);
	// R[Q-1] = Eigen::Vector3d(3, 1, 0);

	// for(int v=1;v<Q-1;v++)
	// 	R[v] = *R.begin() + v * (*(R.end()-1) - (*R.begin()))/(Q-1);

	// std::for_each(R.begin(), R.end(), [](Eigen::Vector3d vec){std::cout<<vec<<std::endl<<std::endl;});

	//std::array<Eigen::Vector3d, howMany> m;
	/*std::array<std::array<Eigen::Vector3d, 3>, Q> m;
	double wi = acos(M_I.dot(M_F)/(M_I.norm() * M_F.norm()));
	double dwi = wi/(Q-1);
	auto k = Eigen::Vector3d(0,0,0);
	for(int i=0;i<3;i++)
	{
		k = m[i][0].cross(m[i][Q-1])/(m[i][0].cross(m[i][Q-1]).norm());
		for(int v=0;v<Q;v++)
		{
			m[i][v] = M_I[i] * cos(dwi*(v)) + (k.cross(m[i][0])) * sin(dwi*v); // (v) instead of (v-1) because indexes goes from 0 not from 1
			std::cout<<m[i][v]<<std::endl;
		}
	}*/

	return 0;
}
