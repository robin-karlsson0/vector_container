#ifndef VEC_H
#define VEC_H

#include <iostream>
#include <algorithm>
#include <vector>


//typedef long long int50; 

//
// Constructors:
//   vec             : Initialize empty vector with zero elements
//   vec(int)        : Initialize vector with the sepecified number of 'zero elements'
//   vec(array, int) : Initialize vector from an input c-style array and its length
//
// Operator overloadings
//   +  : 
//   -  : 
//   =  : 
//   [] : 
//
// Class methods
//   size()   : 
//   max()    : 
//   min()    : 
//   argmax() : 
//   argmin() : 
//   print()  : 
//


const int DEFAULT_VEC_PRINT_LENGTH = 10;

template <class T>
class Vec
{
private:
	std::vector<T> data;

	typename std::vector<T>::const_iterator begin()
	{
		return data.begin();

	}

	typename std::vector<T>::const_iterator end()
	{
		return data.end();
	}

public:
	// Initialize empty vector with zero elements
	Vec() {
		data.resize(0);
	};
	// Initialize vector with the sepecified number of 'zero elements'
	Vec(const unsigned int size)
	{
		data.resize(size);
	}
	// Initialize vector from an input c-style array and its length
	Vec(const T *input_array, const unsigned int input_size)
	{
		data.resize(input_size);
		std::copy(input_array, input_array + input_size, data.begin());
	};

	// Create a new Vec object and return a copy of it. Each element is the sum of the
	// cooresponding elements of the left and right Vec objects.
	// - Return an empty vector if adding vectors of different length.
	Vec<T> operator+ (Vec<T> &vec_rh)
	{
		// Check size compatibility
		if (this->size() != vec_rh.size()) {
			std::cerr << "ERROR: Vectors must be of equal size when adding them (operator+)" << std::endl;
			Vec<T> vec_empty;
			return vec_empty;
		}
		Vec<T> vec_sum(data.size());
		for (int i = 0; i < data.size(); i++) {
			vec_sum[i] += (vec_rh[i] + data[i]);
		}
		return vec_sum;
	}

	// Create a new Vec object and return a copy of it. Each element is the sum of the
	// cooresponding elements of the left and right Vec objects.
	Vec<T> operator- (Vec<T> &vec_rh) {
		// Check size compatibility
		if (data.size() != vec_rh.size()) {
			std::cerr << "ERROR: Vectors must be of equal size when adding them (operator-)" << std::endl;
			Vec<T> vec_empty;
			return vec_empty;
		}
		Vec<T> vec_sub(data.size());
		for (int i = 0; i < data.size(); i++) {
			vec_sub[i] += (data[i] - vec_rh[i]);
		}
		return vec_sub;
	}

	// Copy the contents of the right-hand vector into the left-hand vector.
	Vec<T>& operator= (Vec<T> vec_rh)
	{
		data.assign(vec_rh.begin(), vec_rh.end());
		return *this;
	}

	// Directly access the element specified by the given index.
	T& operator[] (const unsigned int index)
	{
		return data.at(index);
	}

	// Return the number of elements in the vector.
	unsigned int size() {
		return data.size();
	}

	// Return largest element.
	T& max() {
		return *std::max_element(data.begin(), data.end());
	}

	// Return smallest element.
	T& min() {
		return *std::min_element(data.begin(), data.end());
	}

	// Return the index of the largest element.
	unsigned int argmax() {
		return std::distance(data.begin(), std::max_element(data.begin(), data.end()));
	}

	// Return the index of the smallest element.
	unsigned int argmin() {
		return std::distance(data.begin(), std::min_element(data.begin(), data.end()));
	}

	// Return the index of the smallest element.

	// Print a specified number of vector elements to screen.
	// If the specified number is higher than the actual element number, only the actual elements
	// will be printed.
	void print(const unsigned int elem_to_print = DEFAULT_VEC_PRINT_LENGTH) {

		if (elem_to_print >= data.size()) {
			typename std::vector<T>::const_iterator it;
			std::cout << "[ ";
			for (it = data.begin(); it != data.end(); ++it) {
				std::cout << *it << " ";
			}
			std::cout << "]";
		}
		else
		{
			int i = 0;
			typename std::vector<T>::const_iterator it = data.begin();
			while (i < elem_to_print) {
				std::cout << *(it++) << " ";
				i++;
			}
		}

	}

};

#endif