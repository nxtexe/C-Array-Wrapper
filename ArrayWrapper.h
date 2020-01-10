#pragma once
#ifndef __ARRAYWRAP__
#define __ARRAYWRAP__
#include <iostream>//declaration of ostream
#include<sstream>//declaration of stringstream

/*
 * Written by Nathan Johnson
 * Date: January 9, 2020
 *
 * Array is a template wrapper class for the C array object. It's purpose and functionality
 * is similar to that of vector class, but harbour's more python-esque methods and usage since python
 * is my first love.
 * 
 * NOTES:
   1. Uses an exhorbitant amount of memory due to the fact that whenever the array runs out of memory
      2 times memory is dynamically allocated. Causes O(log n) in time complexity but O(n) in space
	  space complexity.
   2. The above mentioned quirk gave way to some interesting results. For example using the Array class
      to store characters from a document of 685, 684 characters then printing those characters in a loop
	  vector class came out on top with ~200ms and < 2MB of memory used why my Array class came in at ~500 - 700ms
	  and over 2MB of memory. However on a file of 4, 862, 971 characters my Array class came out on top in time but
	  lost due to ludacris memory requirements; my Array class finished in <2s using up to 19MB of memory while 
	  vector took over 5s but used only 8MB of memory.
   3. Implementation may be unsafe due to the use of pointer arithmetic to access individual elements, instead of using [],
      this was used to avoid additional function calls for sake of speed but that argument is up for debate.
 * TODO:
   1. Implement () operator overload to take 2 values, start and end and return an Array object with the elements in
      starting index "start" and ending inedx "end" inclusive stored in arr
 */

int cmp(const void* a, const void* b);//compare function to be passed to std::qsort algorithm, see sort member function

template<class T>
class Array;//forward declaration of class for inclusion in params list of operator overload below

template<class T>
std::ostream& operator<< (std::ostream&, Array<T>&);//template operator overload for Array class to be printed as easily as just passing the class t0 the operator, printed in format [element, ....]

template<class T>
class Array {
	private:
		T* arr;//pointer of type T
		unsigned int len;//number of elements in arr
		unsigned int cap;//max capacity
	public:
		Array(const unsigned int&, const T&); //param 1 array size param 2 init value
		Array(const unsigned int&);//param size
		Array();//arr allocated to store 1 object
		~Array();//destructor uses delete[] arr
		const unsigned int length() const;//read only method for len
		void sort();//uses std::qsort to sort sequence in ascending order
		void pop();//removes last element in sequence
		void reverse();//reverses order of sequence
		const std::string& __str__() const;//used to convert sequence to string representation of [element,....]
		const unsigned int append(const T&);//adds element to the end of the array
		T& operator[](const unsigned int&);//access arr elements by obj[]
		T& operator()(const unsigned int&); //access arr elements by obj(num1)
};

template<class T>
Array<T>::Array(const unsigned int& size, const T& val) {
	arr = new T[size];//allocate size elements of memory of sizeof(T) per element
	len = size;
	cap = size;
	for (unsigned int i = 0; i < len; i++)
		*(arr + i) = val;//asssign values
}

template<class T>
Array<T>::Array(const unsigned int& size) {
	arr = new T[size];
	len = size;
	cap = size;
	//default constructor called for each element, maybe the slowest constructor
}

template<class T>
Array<T>::Array() {
	arr = new T[1];
	len = 0;//mimics empty array, even though value has been stored by default constructor
	cap = 1;
}

template<class T>
Array<T>::~Array()
{
	delete[] arr;//free memory explicitly
}

template<class T>
T& Array<T>::operator()(const unsigned int& index) {
	if (index >= len) {
		std::cerr << "Index out of range";
		return *(arr);//return first element
	}
	else if (index < 0 && (index + len) >= 0)//makes possible for user to access elements using negative indexing, for example -1 represents last element -2 second to last and so on
		return *(arr + (index + len));//use pointer arithmetic to access elements
	else if (index < 0 && (index + len) < 0) {
		std::cerr << "Index out of range";
		return *(arr);
	}
	else
		return *(arr + index);
}

template<class T>
T& Array<T>::operator[](const unsigned int& index) {//documentation same as () operator overload
	if (index >= len) {
		std::cerr << "Index out of range";
		return *(arr);
	}
	else if (index < 0 && (index + len) >= 0)
		return *(arr + (index + len));
	else if (index < 0 && (index + len) < 0) {
		std::cerr << "Index out of range";
		return *(arr);
	}
	else
		return *(arr + index);
}

template<class T>
const unsigned int Array<T>::length() const {
	return len;
}

template<class T>
const unsigned int Array<T>::append(const T& val) {
	/*if (len == 0) {
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
	return (len - 1);*/

	if (len == 0) {//implies constructor was called without arguments
		*(arr) = val;//store in first index
		++len;
		return (len - 1);//return index
	}
	else if (len == cap) {//if maximum capacity has been reached
		cap = 2 * len;//double capacity
		T* temp = new T[cap];//allocate 2len memory addresses of sizeof(T) for each element
		for (unsigned int i = 0; i < len; i++)
			*(temp + i) = *(arr + i);//copy existing values into temp
		*(temp + len++) = val;//store new val at end of arr
		arr = temp;//copy temp into arr
		return (len - 1);//return index of new element
	}
	else if (len < cap) {//if maximum capacity has not been reached
		*(arr + len++) = val;//normal assignment
		return (len - 1);//once more return index
	}
	return 0;//else return 0 if failure occurs for example somehow len > capacity
}

template<class T>
void Array<T>::pop() {
	/*T* temp = new T[--len];
	for (unsigned int i = 0; i < len; i++)
		*(temp + i) = *(arr + i);
	arr = temp;*/
	--len;//virtually hides last element
}

int cmp(const void* a, const void* b) {
	return (*(int*)a - *(int*)b);//returns positive if a > b, returns negative vice versa and 0 if a == b
}

template<class T>
void Array<T>::sort() {
	//param 1 array object, param 2 length of array object, param 3 size of each element in bytes and
	//param 4 pointer to cmp function
	std::qsort(this->arr, this->len, sizeof(*this->arr), cmp);
}

template<class T>
void Array<T>::reverse() {//O(n) time, would not recommend using this on a large array :/, like ew no
	//might take forever and large amounts of memory
	T* temp = new T[cap];
	int index = len - 1;
	for (unsigned int i = 0; i <= len; i++)
		*(temp + i) = *(arr + index--);

	for (unsigned int i = 0; i <= len; i++)
		*(arr + i) = *(temp + i);
}

template<class T>
const std::string& Array<T>::__str__() const {
	static std::string as_string;
	std::stringstream iostream;//store each character as they are encountered
	iostream << "[";
	//to escape all escape characters
	for (unsigned int i = 0; i < len; i++) {//encloses each element in quotes
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
	as_string = iostream.str();//copies elements as string
	return as_string;
}

template<class T>
std::ostream& operator<< (std::ostream& os, Array<T>& obj) {
	os << obj.__str__();//makes printing array elements as simple as calling shift operator without explictly calling string methods, save a line of code
	return os;
}
#endif
