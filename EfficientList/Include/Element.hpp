
#include "Exception.hpp"

template <class T>
class Element{
protected:
	T info;
	Element<T>* diff;
public:
	Element<T>(T info);
	Element<T>(const Element<T>* elem);
	Element<T>(const Element<T>* diff, T info);

	T get_info() const;
	template <class T>
	friend class LinkedList;
};

template <class T>
Element<T>::Element<T>(T info) : info(info), diff(nullptr) {}

template <class T>
Element<T>::Element<T>(const Element<T>* elem) : info(elem.info), diff(elem.diff) {}

template <class T>
Element<T>::Element<T>(const Element<T>* diff, T info) : info(info), diff(diff) {}

template <class T>
T Element<T>::get_info() const {
	return info;
}

template <class T>
Element<T>* XOR(const Element<T>* a, const Element<T>* b)
{
	return reinterpret_cast<Element<T>*>(
		reinterpret_cast<uintptr_t>(a) ^
		reinterpret_cast<uintptr_t>(b));
}