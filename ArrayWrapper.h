#pragma once
#ifndef __ARRAYWRAP__
#define __ARRAYWRAP__
#include <iostream>
#include <cstdlib>
#include<time.h>
#include<chrono>
#include<stdlib.h>
#include<sstream>

int cmp(const void* a, const void* b);

template<class T>
class Array;

template<class T>
std::ostream& operator<< (std::ostream&, Array<T>&);

template<class T>
class Array {
	private:
		T* arr;
		unsigned long long int len;
	public:
		Array(const int&, const T&); //param 1 array size param 2 init value
		Array(const T&);
		Array();
		~Array();
		const unsigned long long int length() const;
		void sort();
		void pop();
		void reverse();
		const std::string& __str__() const;
		const unsigned long long int append(const T&);
		T& operator[](const int&);
		T& operator()(const int&); //access arr elements by obj(num1)
};

#include "ArrayWrapper.h"

template<class T>
Array<T>::Array(const int& size, const T& val) {
	arr = new T[size];
	len = size;
	for (int i = 0; i < len; i++)
		*(arr + i) = val;
}

template<class T>
Array<T>::Array(const T& size) {
	arr = new T[size];
	len = size;
	for (int i = 0; i < len; i++)
		*(arr + i) = 0;
}

template<class T>
Array<T>::Array() {
	arr = new T[1];
	len = 0;
}

template<class T>
Array<T>::~Array()
{
	delete[] arr;
}

template<class T>
T& Array<T>::operator()(const int& index) {
	if (index >= len)
		std::cerr << "Index out of range";
	else if (index < 0 && (index + len) >= 0)
		return *(arr + (index + len));
	else if (index < 0 && (index + len) < 0)
		std::cerr << "Index out of range";
	else
		return *(arr + index);
}

template<class T>
T& Array<T>::operator[](const int& index) {
	if (index >= len)
		std::cerr << "Index out of range";
	else if (index < 0 && (index + len) >= 0)
		return *(arr + (index + len));
	else if (index < 0 && (index + len) < 0)
		std::cerr << "Index out of range";
	else
		return *(arr + index);
}

template<class T>
const unsigned long long int Array<T>::length() const {
	return len;
}

template<class T>
const unsigned long long int Array<T>::append(const T& val) {
	if (len == 0) {
		*(arr) = val;
		++len;
		return (len - 1);
	}
	T* temp = new T[len + 1];
	for (int i = 0; i < len; i++)
		*(temp + i) = *(arr + i);
	len += 1;
	*(temp + (len - 1)) = val;
	arr = temp;
	return (len - 1);
}

template<class T>
void Array<T>::pop() {
	T* temp = new T[--len];
	for (int i = 0; i < len; i++)
		*(temp + i) = *(arr + i);
	arr = temp;
}

int cmp(const void* a, const void* b) {
	return (*(int*)a - *(int*)b);
}

template<class T>
void Array<T>::sort() {
	std::qsort(this->arr, this->len, sizeof(*this->arr), cmp);
}

template<class T>
void Array<T>::reverse() {
	T* temp = new T[len];
	int index = len - 1;
	for (int i = 0; i <= len; i++)
		*(temp + i) = *(arr + index--);

	for (int i = 0; i <= len; i++)
		*(arr + i) = *(temp + i);
}

template<class T>
const std::string& Array<T>::__str__() const {
	static std::string as_string;
	std::stringstream iostream;
	iostream << "[";
	for (int i = 0; i < len; i++) {
		if (*(arr + i) == '\"')
			iostream << "\'";
		else if (*(arr + i) == '\'')
			iostream << "\"";
		else
			iostream << "\'";
		switch (*(arr + i)) {
			case '\'':
				iostream << "\\'";
				break;

			case '\"':
				iostream << "\\\"";
				break;

			case '\?':
				iostream << "\\?";
				break;

			case '\\':
				iostream << "\\\\";
				break;

			case '\a':
				iostream << "\\a";
				break;

			case '\b':
				iostream << "\\b";
				break;

			case '\f':
				iostream << "\\f";
				break;

			case '\n':
				iostream << "\\n";
				break;

			case '\r':
				iostream << "\\r";
				break;

			case '\t':
				iostream << "\\t";
				break;

			case '\v':
				iostream << "\\v";
				break;

			default:
				iostream << *(arr + i);
		}
		if (*(arr + i) == '\"')
			iostream << "\'";
		else if (*(arr + i) == '\'')
			iostream << "\"";
		else
			iostream << "\'";
		if (i < (len - 1))
			iostream << ", ";
	}
	iostream << "]";
	as_string = iostream.str();
	return as_string;
}

template<class T>
std::ostream& operator<< (std::ostream& os, Array<T>& obj) {
	os << obj.__str__();
	return os;
}
#endif
