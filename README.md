# Vector class for handling generic data arrays.

Robin Karlsson 28.4.2018

### Usage examples

```c++
  Vec<int> a(4);                            // Initialize a vector of 4 zero elements.
  
  int init_array[] = {0,1,2,3};             // Create an array to initialize a vector.
  
  Vec<int> b(init_array,4);      		   
  
  Vec<int> c = a + b;                       //Initialize vector by adding two vectors.
  
  int max_val = b.max();                    //Returns the largest element in the vector.
  
  Vec<int> d = Vec<int>::vec_dist_L1(a,b);  //Return a vector corresponding to the distance between
                                              vectors 'a' and 'b'.
```

### Constructors
```
  vec<T>             : Initialize empty vector with zero elements
  vec<T>(int)        : Initialize vector with the sepecified number of 'zero elements'
  vec<T>(array, int) : Initialize vector from an input c-style array and its length
```

### Operator overloadings
```
  +  : Element-wise addition.
  -  : Element-wise subtraction.
  *  : Element-wise multiplicaiton.
  /  : Element-wise division.
  =  : Copy RHS vector to the LHS vector.
  [] : Access vector element by index.
```

### Class methods
```
  size()        : Number of elements.
  push_back()   : Add an element to the back of the vector.
  pop_back()    : Remove element at the back of the vector.
  remove( int ) : Remove the element specified by the index.
  max()         : Largest element value.
  min()         : Smallest element value.
  argmax()      : Index of the largest element value.
  argmin()      : Index of the smallest element value.
  sum()         : Sum of all elements.
  avg()         : Average of all elements.
  norm_L0()     : L0 norm.
  norm_L1()     : L1 norm.
  norm_L2()     : L2 norm.
  norm_max()    : Max norm.
  norm_L1_avg() : Average L1 norm for all elements.
  print( int )  : Write elements to the standard output up to the specified element index.
```
### Static class methods
```
  vec_dist_L1( vec_a, vec_b ) : Return a vector corresponding to the distance between two vectors.
```
