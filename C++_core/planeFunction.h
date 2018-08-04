#ifndef __PLANE_FUNCTION_H__
#define __PLANE_FUNCTION_H__

#include <functional>


template <class T>
class planeFunction
{
	std::function<T(T, T)> function;
	static planeFunction<T> *instance;
	planeFunction(){}	
	
public:
	static planeFunction<T> *getInstance();

	T operator()(T x, T y);

	void setFunction(std::function<T(T, T)> function);

	std::function<T(T, T)> getFunction();
};

template <class T> planeFunction<T> *planeFunction<T>::instance = nullptr;

#include "planeFunction.tpp"


#endif //__PLANE_FUNCTION_H__