#ifndef HPEML
#define HPEML // stands for: High Performance Extendable Math Library

#define VECSIZE 8
#define I_BLOCKSIZE 32
#define J_BLOCKSIZE 32
#define K_BLOCKSIZE 32
#define UNROLL_1 4 // UNROLL_1 * VECSIZE <= min{I_BLOCKSIZE, J_BLOCKSIZE, K_BLOCKSIZE}
#define UNROLL_2 2 //UNROLL_2 * VECSIZE <= min{I_BLOCKSIZE, J_BLOCKSIZE, K_BLOCKSIZE}

#include<iostream>
#include<vector>
#include "Float.h"
using namespace std;

/* class Memory_Block - START */
template <typename scalar, typename T> // CRTP (Curiously Recurring Template Pattern)
class Memory_Block // Base type of Matrix
{
protected:
	scalar* _mat;
	size_t _row;
	size_t _col;

public:
	// constructors
	Memory_Block(); // empty constructor
	Memory_Block(size_t row, size_t col); // matrix of size (rows_, cols_)
	Memory_Block(size_t row, size_t col, scalar val); // matrix filled by val
	Memory_Block(size_t row, size_t col, std::string type); // rand or one matrix ...
	Memory_Block(std::initializer_list<std::initializer_list<scalar>> list_lists);
	Memory_Block(vector<vector<scalar>>& vec_vecs);
	Memory_Block(std::vector<std::vector<scalar>>&& vec_vecs);
	Memory_Block(const Memory_Block& M); // lvalue copy constructor
	Memory_Block(Memory_Block& M); // lvalue copy constructor
	Memory_Block(Memory_Block&& M); // rvalue copy constructor

	// accessors
	inline scalar& operator () (size_t i, size_t j); // access to element (i, j)
	inline scalar* operator [] (size_t i); // access to row i

	// extractors
	T operator () (size_t upperRow, size_t lowerRow, size_t leftCol, size_t rightCol);  // sub-matrix: (upperRow : lowerRow, leftCol : rightCol)
	T sub(vector<size_t> row_list, vector<size_t> col_list);

	// sub-matrix: row_list - is a list of row nambers, col_list - is a list of column nambers
	// if (row_list.size() == 0) then - all rows
	// if (col_list.size() == 0) then - all columns

	// geters and seters
	inline scalar* data();
	inline size_t rows();
	inline size_t cols();

	// assignment
	inline Memory_Block& operator = (const Memory_Block& M);
	inline Memory_Block& operator = (Memory_Block& M);
	inline Memory_Block& operator = (vector<vector<scalar>>& vec_vecs);
	inline Memory_Block& operator = (vector<vector<scalar>>&& vec_vecs);
	inline Memory_Block& operator = (Memory_Block&& M);

	// input\output operators
	friend ostream& operator << (ostream& out, Memory_Block& m);
	friend ostream& operator << (ostream& out, Memory_Block&& m);
	friend Memory_Block& operator << (Memory_Block& M, T x);
	friend Memory_Block& operator , (Memory_Block& M, T x);

	// destructor
	~Memory_Block();
};
/* class Memory_Block - END */


/* class Matrix - START */
template <typename scalar>
class Matrix : public Memory_Block<scalar, Matrix<scalar>> // Type of Matrix
{
public:
	// constructors
	using Memory_Block<scalar, Matrix<scalar>>::Memory_Block;

	Matrix(const Matrix& M);
	Matrix(Matrix& M);
	Matrix(Matrix&& M);

	// assignment operators
	inline Matrix& operator = (const Matrix& M);
	inline Matrix& operator = (Matrix& M);
	inline Matrix& operator = (vector<vector<scalar>>& vec_vecs);
	inline Matrix& operator = (vector<vector<scalar>>&& vec_vecs);
	inline Matrix& operator = (Matrix&& M);

	/* Arithmetic Operators - START */

	// operator += with matrices
	friend Matrix& operator += (Matrix& A, Matrix& B);
	friend Matrix& operator += (Matrix& A, Matrix&& B);
	friend Matrix& operator += (Matrix&& A, Matrix& B);
	friend Matrix& operator += (Matrix&& A, Matrix&& B);

	// operator -= with matrices
	friend Matrix& operator -= (Matrix& A, Matrix& B);
	friend Matrix& operator -= (Matrix& A, Matrix&& B);
	friend Matrix& operator -= (Matrix&& A, Matrix& B);
	friend Matrix& operator -= (Matrix&& A, Matrix&& B);


	// operator *= with scalar
	friend Matrix& operator *= (Matrix& M, scalar c);
	friend Matrix& operator *= (Matrix&& M, scalar c);

	// operator += with scalar
	friend Matrix& operator += (Matrix& M, scalar c);
	friend Matrix& operator += (Matrix&& M, scalar c);

	// operator -= with scalar
	friend Matrix& operator -= (Matrix& M, scalar c);
	friend Matrix& operator -= (Matrix&& M, scalar c);

	// operator /= with scalar
	friend Matrix& operator /= (Matrix& M, scalar c);
	friend Matrix& operator /= (Matrix&& M, scalar c);

	// operator + with matrices
	friend Matrix operator + (Matrix& A, Matrix& B);
	friend Matrix operator + (Matrix& A, Matrix&& B);
	friend Matrix operator + (Matrix&& A, Matrix& B);
	friend Matrix operator + (Matrix&& A, Matrix&& B);

	// operator - with matrices
	friend Matrix operator - (Matrix& A, Matrix& B);
	friend Matrix operator - (Matrix& A, Matrix&& B);
	friend Matrix operator - (Matrix&& A, Matrix& B);
	friend Matrix operator - (Matrix&& A, Matrix&& B);

	// operator * with matrices
	friend Matrix operator * (Matrix& A, Matrix& B);
	friend Matrix operator * (Matrix& A, Matrix&& B);
	friend Matrix operator * (Matrix&& A, Matrix& B);
	friend Matrix operator * (Matrix&& A, Matrix&& B);

	friend Matrix operator + (Matrix& A, scalar c); //4 times
	friend Matrix operator - (Matrix& A, scalar c); //4 times
	friend Matrix operator * (Matrix& A, scalar c); //4 times
	friend Matrix operator / (Matrix& A, scalar c); //2 times

	/* Arithmetic Operators - END */

	// product with transpose
	friend Matrix product(Matrix&& A, char mode_a, Matrix&& B, char mode_b); // 4 times

	// Element-wise product
	friend Matrix dot_product(Matrix&& a, Matrix&& b); //4 times

	Matrix trans(bool inplace);
	Matrix conj(bool inplace);
	Matrix diag();
};
/* class Matrix - END */


/* class Vector - START */
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
/* class Vector - END */

#endif // !HPEML

