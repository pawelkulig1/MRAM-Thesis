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

template <class T>
planeFunction<T> *planeFunction<T>::getInstance()
{
	if(instance == nullptr)
	{
		instance = new planeFunction<T>;
	}
	return instance;
}

template <class T>
T planeFunction<T>::operator()(T x, T y)
{
	return function(x, y);
}

template <class T>
void planeFunction<T>::setFunction(std::function<T(T, T)> function)
{
	this->function = function;
}

template <class T>
std::function<T(T, T)> planeFunction<T>::getFunction()
{
	return function;
}


#endif //__PLANE_FUNCTION_H__