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