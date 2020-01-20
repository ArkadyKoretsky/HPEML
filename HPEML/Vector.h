#ifndef Vector_Class
#define Vector_Class

#include "Matrix.h"

template <typename scalar>
class Vector : public Matrix<scalar>
{
	using Matrix<scalar>::Matrix;

	// constructors
	Vector() : Memory_Block<scalar, Matrix<scalar>>::Memory_Block() {} // empty constructor
	Vector(size_t len) : Matrix<scalar>::Matrix(len, 1) {} // Vector of size len
	Vector(size_t len, scalar val) : Matrix<scalar>::Matrix(len, 1, val) {} // Vector filled by val
	Vector(size_t len, string type) : Matrix<scalar>::Matrix(len, 1, type) {} //rand Vector ...
	Vector(initializer_list<scalar> list);
	Vector(vector<scalar>& vec);
	Vector(vector<scalar>&& vec_vecs);
	Vector(const Vector& V); // lvalue copy constructor
	Vector(Vector& V); // lvalue copy constructor
	Vector(Vector&& V); // rvalue copy constructor
};

#endif // !Vector_Class