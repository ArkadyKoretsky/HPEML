#ifndef Vector_Class
#define Vector_Class

#include "Matrix.h"

template <typename scalar>
class Vector : public Matrix<scalar>
{
	// constructors
	Vector(); // empty constructor
	Vector(size_t len); // Vector of size len
	Vector(size_t len, scalar val); // Vector filled by val
	Vector(size_t row, size_t col, std::string type); //rand Vector ...
	Vector(std::initializer_list<scalar> list);
	Vector(std::vector<scalar>& vec);
	Vector(std::vector<scalar>&& vec_vecs);
	Vector(const Vector& V); // lvalue copy constructor
	Vector(Vector& V); // lvalue copy constructor
	Vector(Vector&& V); // rvalue copy constructor
};

#endif // !Vector_Class