﻿#pragma once
#include "Element.hpp"

template <class T>
class LinkedList {
private:
	Element<T>* head;
	Element<T>* tail;
	//Element<T>& operator[](const int index);
	
public:
	LinkedList<T>(const T* a, const int len);
	LinkedList<T>();

	LinkedList<T>& operator=(const LinkedList<T>& list);

	void push_back(const T info);
	void insert(const int index, const T info);
	void remove(const int index);


	Element<T>& operator[](const int index) const;
	

	int size() const;
	T get_head() const;
	T get_tail() const;
	void print() const;

	~LinkedList<T>();
};

template <class T>
LinkedList<T>::LinkedList<T>() : head(nullptr), tail(nullptr) {}

template <class T>
LinkedList<T>::LinkedList<T>(const T* a, const int len) {
	if (len < 0)
		throw InvalidLengthException("LinkedList constructor: InvalidLen");
	Element<T>* prev;
	if (!(prev = new Element<T>(a[0])))
		throw NotEnoughSpaceException("LinkedList constructor: NotEnoughSpace");
	head = tail = prev;
	if (len > 1){
		Element<T>* current;
		if (!(current = new Element<T>(a[1])))
			throw NotEnoughSpaceException("LinkedList constructor: NotEnoughSpace");
		head->diff = current;
		if (len == 2) {
			current->diff = head;//îáÿçàòåëüíî èñïðàâèòü ýòî íåäîðàçóìåíèå
			tail = current;
		}
		else {
			Element<T>* next;
			if (!(next = new Element<T>(a[2])))
				throw NotEnoughSpaceException("LinkedList constructor: NotEnoughSpace");
			for (int i = 2; i < len; ++i, next = next->diff) {
				current->diff = XOR(prev, next);
				prev = current;
				current = next;
				if (i != len - 1)
					if (!(next->diff = new Element<T>(a[i + 1])))
						throw NotEnoughSpaceException("LinkedList constructor: NotEnoughSpace");
			}
			current->diff = prev;
			tail = current;
		}
	}
}

template<class T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& list)
{
//	if (list == this) return *this;
	//if (list == nullptr) throw NullptrException("LinkedList operator=: nullptr");

	Element<T>* current = head;
	Element<T>* last = nullptr;

	if (head != nullptr) {
		Element<T>* tmp_current = current;
		while (current) {
			tmp_current = current;
			current = XOR(last, current->diff);
			delete last;
			last = tmp_current;
		}
		delete current;
		head = nullptr;
		tail = nullptr;
	}//clear old 
	if (list.head == list.tail) {
		if (!(this->head = new Element<T>(list.head->info)))
			throw NotEnoughSpaceException("LinkedList operator= not enough space");
		tail = head;
		return *this;
	}


	Element<T>* l_current = list.head;
	Element<T>* l_next = list.head->diff;
	Element<T>* l_last = nullptr;
	Element<T>* l_tmp = l_current;

	Element<T>* next = nullptr;

	if (!(this->head = new Element<T>(l_current->info))) 
		throw NotEnoughSpaceException("LinkedList operator= not enough space");

	current = head;
	last = nullptr;

	while (l_next) {

		if (!(next = new Element<T>(l_next->info)))
			throw NotEnoughSpaceException("LinkedList operator= not enough space");
		current->diff = XOR(last, next);
		last = current;
		current = next;

		l_tmp = l_next;
		l_next = XOR(l_current, l_next->diff);
		l_last = l_current;
		l_current = l_tmp;
		
		
	}
	next->diff = last;
	tail = next;
	return *this;

}

template <class T>
void LinkedList<T>::print() const {
	std::cout << "\n\nList:\n";
	Element<T>* current = head;
	Element<T>* tmp_current = current;
	Element<T>* last = nullptr;
	while (current) {
		std::cout << current->get_info() << " ";
		tmp_current = current;
		current = XOR(last, current->diff);
		last = tmp_current;
	}
}

template <class T>
int LinkedList<T>::size() const {
	int size = 0;
	if (head == nullptr) return 0;
	Element<T>* current = head;
	Element<T>* tmp_current = current;
	Element<T>* last = nullptr;
	while (current) {
		++size;
		tmp_current = current;
		current = XOR(last, current->diff);
		last = tmp_current;
	}
	return size;
}


/*
template <class T>
Element<T>& LinkedList<T>::operator[](const int index) {
	if (index < 0 || index >= this->size())
		throw InvalidLengthException("operator[] const: invalid index");
	if (index == 0) {
		return *head;
	}
	if (index == (this->size() - 1)) {
		return *tail;
	}
	Element<T>* last = nullptr;
	Element<T>* current = head;
	Element<T>* tmp_current = head;
	for (int i = 0; i < index; ++i) {
		tmp_current = current;
		current = XOR(last, current->diff);
		last = tmp_current;
	}
	return *current;
}
*/
template <class T>
Element<T>& LinkedList<T>::operator[](const int index) const{
	if (index < 0 || index >= this->size())
		throw InvalidLengthException("operator[] const: invalid index");
	if (index == 0) {
		return *head;
	}
	if (index == this->size() - 1) {
		return *tail;
	}
	Element<T>* last = nullptr;
	Element<T>* current = head;
	Element<T>* tmp_current = head;
	for (int i = 0; i < index; ++i) {
		tmp_current = current;
		current = XOR(last, current->diff);
		last = tmp_current;
	}
	return *current;
}


template <class T>
T LinkedList<T>::get_head() const {
	return head->get_info();
}

template <class T>
T LinkedList<T>::get_tail() const {
	return tail->get_info();
}



template <class T>
void LinkedList<T>::push_back(const T info) {
	Element<T>* elem;

	if (!(elem = new Element<T>(info)))
		throw NotEnoughSpaceException("LinkedList push_back: NotEnoughSpace");
	if (head == nullptr) {
		head = tail = elem;
		return;
	}
	tail->diff = XOR(tail->diff, elem);
	elem->diff = tail;
	tail = elem;
}

template <class T>
void LinkedList<T>::insert(const int index, const T info) {
	int size = this->size();
	if (index < 0 || index > size)
		throw InvalidLengthException("LinkedList insert: Wrong index");

	if (index == size)//equivalent to push_back
	{
		this->push_back(info);
		return;
	}

	Element<T>* elem;
	if (!(elem = new Element<T>(info)))
		throw NotEnoughSpaceException("LinkedList insert: NotEnoughSpace");

	if (!size)//if size == 0 which is equivalent to head == nullptr
	{
		head = tail = elem;
		head->diff = nullptr;
		return;
	}


	if (size == 1) //head == tail
	{
		tail = elem; //index must be 1 or 0 as index <= size, index = 0 processed
		tail->diff = head;
		head->diff = tail;
		return;
	}
	if (index == size) {
		tail->diff = XOR(tail->diff, elem);
		elem->diff = tail;
		tail = elem;
		return;
	}
	if (index == 0) {
		elem->diff = head;
		head->diff = XOR(head->diff, elem);
		head = elem;
		return;
	}
	if (index == size - 1) {
		tail->diff->diff = XOR(XOR(tail->diff->diff, tail), elem);
		elem->diff = XOR(tail->diff, tail);
		tail->diff = elem;
		return;
	}
	Element<T>* last = nullptr;
	Element<T>* current = head;
	Element<T>* next = head->diff;
	for (int i = 0; i < index; ++i) {
		last = current;
		current = next;
		next = XOR(next->diff, last);
	}
	current->diff = XOR(XOR(current->diff, last), elem);
	last->diff = XOR(XOR(last->diff, current), elem);
	elem->diff = XOR(last, current);
	return;
}

template <class T>
LinkedList<T>::~LinkedList() {
	if (head != nullptr) {
		Element<T>* current = head;
		Element<T>* tmp_current = current;
		Element<T>* last = nullptr;
		while (current) {
			tmp_current = current;
			current = XOR(last, current->diff);
			delete last;
			last = tmp_current;
		}
		delete current;
		head = nullptr;
		tail = nullptr;
	}
	//std::cout << "\ndestructor";
	//this->print();
	//std::cout << "destructor worked correctly, if List is empty\n\n\n";
}


template <class T>
void LinkedList<T>::remove(const int index) {
	int size = this->size();
	if (index < 0 || head == nullptr || index >= size)
		throw InvalidLengthException("LinkedList remove: InvalidIndex");
	if (size == 1) {
		delete head;
		head = tail = nullptr;
		return;
	}
	Element<T>* current = head;
	if (index == 0) {
		head->diff->diff = XOR(head->diff->diff, head);
		head = head->diff;
		delete current;
		current = nullptr;
		return;
	}
	if (index == size - 1) {
		current = tail;
		tail->diff->diff = XOR(tail->diff->diff, tail);
		tail = tail->diff;
		delete current;
		current = nullptr;
		return;
	}
	Element<T>* last = nullptr;
	Element<T>* next = head->diff;
	for (int i = 0; i < index; ++i) {
		last = current;
		current = next;
		next = XOR(next->diff, last);
	}

	last->diff = XOR(XOR(last->diff, current), next);
	next->diff = XOR(XOR(next->diff, current), last);
	delete current;
}