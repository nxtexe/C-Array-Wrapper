#include <iostream>
#include <cstdlib>
#include<time.h>
#include<chrono>
#include<stdlib.h>
int cmp(const void *a, const void *b);
class IntArray
{
  private:
	int *arr;
	int len;

  public:
	IntArray(const int &, const int &); //param 1 array size param 2 init value
	IntArray(const int &);
	IntArray();
	~IntArray();
	const int length() const;
	void sort();
	void pop();
	const int append(const int &);
	int &operator[](const int &);
	int &operator()(const int &); //access arr elements by obj(num1)
};

int main()
{
	srand(time(NULL));
	IntArray arr;
	for (int i = 1; i <= 100000; i++) {
		int random = (rand() % 100000) + 1;
		std::cout << random << std::endl;
		arr.append(random);
	}
	std::cout << std::endl;
	arr.sort();
	for(int i = 0; i < 100000; i++)
		std::cout << arr[i] << std::endl;
}

IntArray::IntArray(const int &size, const int &val)
{
	arr = new int[size];
	len = size;
	for (int i = 0; i < len; i++)
		*(arr + i) = val;
}

IntArray::IntArray(const int &size)
{
	arr = new int[size];
	len = size;
	for (int i = 0; i < len; i++)
		*(arr + i) = 0;
}

IntArray::IntArray()
{
	arr = new int[1];
	len = 1;
}

IntArray::~IntArray()
{
	delete[] arr;
}

int &IntArray::operator()(const int &index)
{
	if (index >= len)
		std::cerr << "Index out of range";
	else if (index < 0 && (index + len) >= 0)
		return *(arr + (index + len));
	else if (index < 0 && (index + len) < 0)
		std::cerr << "Index out of range";
	else
		return *(arr + index);
}

int &IntArray::operator[](const int &index)
{
	if (index >= len)
		std::cerr << "Index out of range";
	else if (index < 0 && (index + len) >= 0)
		return *(arr + (index + len));
	else if (index < 0 && (index + len) < 0)
		std::cerr << "Index out of range";
	else
		return *(arr + index);
}

const int IntArray::length() const
{
	return len;
}

const int IntArray::append(const int &val)
{
	int *temp = new int[len + 1];
	for (int i = 0; i < len; i++)
		*(temp + i) = *(arr + i);
	len += 1;
	*(temp + (len - 1)) = val;
	arr = temp;
	return (len - 1);
}

void IntArray::pop()
{
	int *temp = new int[--len];
	for (int i = 0; i < len; i++)
		*(temp + i) = *(arr + i);
	arr = temp;
}

int cmp(const void *a, const void *b)
{
	return (*(int *)a - *(int *)b);
}

void IntArray::sort()
{
	std::qsort(this->arr, this->len, sizeof(*this->arr), cmp);
}