#ifndef VEC_H
#define VEC_H

#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>

// Vector class for handling generic data arrays.
//
// Usage examples
//   Vec<int> a(4);                            Initialize a vector of 4 zero elements.
//   int init_array[] = {0,1,2,3};             Create an array to initialize a vector.
//   Vec<int> b(init_array,4);      		   
//   Vec<int> c = a + b;                       Initialize vector by adding two vectors.
//   int max_val = b.max();                    Returns the largest element in the vector.
//   Vec<int> d = Vec<int>::vec_dist_L1(a,b);  Return a vector corresponding to the distance
//                                             between vectors 'a' and 'b'.
//
// Constructors
//   vec<T>             : Initialize empty vector with zero elements
//   vec<T>(int)        : Initialize vector with the sepecified number of 'zero elements'
//   vec<T>(array, int) : Initialize vector from an input c-style array and its length
//
// Operator overloadings
//   +  : Element-wise addition.
//   -  : Element-wise subtraction.
//   *  : Element-wise multiplicaiton.
//   /  : Element-wise division.
//   =  : Copy RHS vector to the LHS vector.
//   [] : Access vector element by index.
//
// Class methods
//   size()        : Number of elements.
//   push_back()   : Add an element to the back of the vector.
//   pop_back()    : Remove element at the back of the vector.
//   remove( int ) : Remove the element specified by the index.
//   max()         : Largest element value.
//   min()         : Smallest element value.
//   argmax()      : Index of the largest element value.
//   argmin()      : Index of the smallest element value.
//   sum()         : Sum of all elements.
//   avg()         : Average of all elements.
//   norm_L0()     : L0 norm.
//   norm_L1()     : L1 norm.
//   norm_L2()     : L2 norm.
//   norm_max()    : Max norm.
//   norm_L1_avg() : Average L1 norm for all elements.
//   print( int )  : Write elements to the standard output up to the specified element index.
//
// Static class methods
//   vec_dist_L1( vec_a, vec_b ) : Return a vector corresponding to the distance between two vectors.
//
// Robin Karlsson 28.4.2018

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

	// Return true if a vector element is zero.
	bool contain_zero_element()
	{
		typename std::vector<T>::const_iterator it;
		for (it = data.begin(); it != data.end(); ++it)
		{
			if (*it == 0) {
				return true;
			}
		}
		return false;
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
		for (unsigned int i = 0; i < data.size(); i++) {
			vec_sum[i] = (vec_rh[i] + data[i]);
		}
		return vec_sum;
	}

	// Create a new Vec object and return a copy of it. Each element is the sum of the
	// cooresponding elements of the left and right Vec objects.
	// - Return an empty vector if adding vectors of different length.
	Vec<T> operator- (Vec<T> &vec_rh) {
		// Check size compatibility
		if (data.size() != vec_rh.size()) {
			std::cerr << "ERROR: Vectors must be of equal size when adding them (operator-)" << std::endl;
			Vec<T> vec_empty;
			return vec_empty;
		}
		Vec<T> vec_sub(data.size());
		for (unsigned int i = 0; i < data.size(); i++) {
			vec_sub[i] = (data[i] - vec_rh[i]);
		}
		return vec_sub;
	}

	// Create a new Vec object and return a copy of it. Each element is the element-wise multiplication of the
	// cooresponding elements of the left and right Vec objects.
	// - Return an empty vector if adding vectors of different length.
	Vec<T> operator* (Vec<T> &vec_rh)
	{
		// Check size compatibility
		if (data.size() != vec_rh.size()) {
			std::cerr << "ERROR: Vectors must be of equal size when multiplying them (operator*)" << std::endl;
			Vec<T> vec_empty;
			return vec_empty;
		}
		Vec<T> vec_mul(data.size());
		for (unsigned int i = 0; i < data.size(); i++) {
			vec_mul[i] = data[i] * vec_rh[i];
		}
		return vec_mul;
	}

	// Create a new Vec object and return a copy of it. Each element is the element-wise division of the
	// cooresponding elements of the left and right Vec objects.
	// - Return an empty vector if adding vectors of different length or division by zero.
	Vec<T> operator/ (Vec<T> &vec_rh)
	{
		// Check size compatibility
		if (data.size() != vec_rh.size()) {
			std::cerr << "ERROR: Vectors must be of equal size when dividing them (operator/)" << std::endl;
			Vec<T> vec_empty;
			return vec_empty;
		}
		// Check for zero division
		if (vec_rh.contain_zero_element()) {
			std::cerr << "ERROR: Dividing by zero (operator/)" << std::endl;
			Vec<T> vec_empty;
			return vec_empty;
		}
		Vec<T> vec_div(data.size());
		for (unsigned int i = 0; i < data.size(); i++) {
			vec_div[i] = data[i] / vec_rh[i];
		}
		return vec_div;
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
	unsigned int size() 
	{
		return data.size();
	}

	// Add an elment to the back of the vector.
	void push_back(const T elem)
	{
		data.push_back(elem);
	}

	// Remove element at the back of the vector.
	void pop_back()
	{
		data.pop_back();
	}

	// Remove element specified by the index.
	void remove(unsigned int index_to_remove)
	{
		data.erase(data.begin() + index_to_remove);
	}

	// Return largest element.
	T& max() 
	{
		return *std::max_element(data.begin(), data.end());
	}

	// Return smallest element.
	T& min() 
	{
		return *std::min_element(data.begin(), data.end());
	}

	// Return the index of the largest element.
	unsigned int argmax() 
	{
		return std::distance(data.begin(), std::max_element(data.begin(), data.end()));
	}

	// Return the index of the smallest element.
	unsigned int argmin() 
	{
		return std::distance(data.begin(), std::min_element(data.begin(), data.end()));
	}

	// Return the sum of all elements.
	T sum()
	{
		return std::accumulate(data.begin(), data.end(), 0);
	}

	// Return the average of all elements.
	T avg()
	{
		return this->sum() / data.size();
	}

	// Return the L0 norm of a vector.
	T norm_L0(const T threshold = 0)
	{
		T norm = 0;
		typename std::vector<T>::const_iterator it;
		for(it = data.begin(); it != data.end(); ++it)
		{
			norm += (abs(*it) <= threshold) ? 0 : 1;
		}
		return norm;
	}

	// Return the L1 norm of a vector.
	T norm_L1()
	{
		T norm = 0;
		typename std::vector<T>::const_iterator it;
		for (it = data.begin(); it != data.end(); ++it)
		{
			norm += (abs(*it));
		}
		return norm;
	}

	// Return the L2 norm of a vector.
	T norm_L2()
	{
		T norm = 0;
		typename std::vector<T>::const_iterator it;
		for (it = data.begin(); it != data.end(); ++it)
		{
			norm += (*it) * (*it);
		}
		return T(sqrt(norm));
	}

	// Return the max norm of a vector.
	T norm_max()
	{
		T norm_max = 0;
		typename std::vector<T>::const_iterator it;
		for (it = data.begin(); it != data.end(); ++it)
		{
			T norm = abs(*it);
			if (norm > norm_max) {
				norm_max = norm;
			}
		}
		return norm_max;
	}

	// Return the element-wise average of the L1 norm of a vector.
	T norm_L1_avg()
	{
		return this->norm_L1() / data.size();
	}

	// Print a specified number of vector elements to screen.
	// If the specified number is higher than the actual element number, only the actual elements
	// will be printed.
	void print(const unsigned int elem_to_print = DEFAULT_VEC_PRINT_LENGTH) 
	{
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
			unsigned int i = 0;
			typename std::vector<T>::const_iterator it = data.begin();
			while (i < elem_to_print) {
				std::cout << *(it++) << " ";
				i++;
			}
		}
	}

	// Create and return a new Vec object corresponding to the distance between two vectors.
	// - Return an empty vector if the two vectors have different length.
	static Vec<T> vec_dist_L1(Vec<T> &vec_a, Vec<T> &vec_b)
	{
		if (vec_a.size() != vec_b.size()) {
			std::cerr << "ERROR: Vectors must be of equal size when computing distance" << std::endl;
			Vec<T> vec_empty;
			return vec_empty;
		}
		Vec<T> vec_dist(vec_a.size());
		for (unsigned int i = 0; i < vec_a.size(); i++) {
			vec_dist[i] = abs(vec_a[i] - vec_b[i]);
		}
		return vec_dist;
	}

};

#endif