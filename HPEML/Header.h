//
//  Header.h
//  Classes
//
//  Created by Dan Lemberg on 18/05/2019.
//  Copyright © 2019 Dan Lemberg. All rights reserved.
//

#ifndef Header_h
#define Header_h

#include <immintrin.h>
#include <iostream>
#include <vector>
#include <utility>
using namespace std;

/* Definition Section - START */
#define architecture_256

#ifdef architecture_128
#define vectypefloat __m128
#else
#ifdef architecture_256
#define vectypefloat __m256
#else
#ifdef architecture_512
#define vectypefloat __m512
#else
//??????????????????
#endif
#endif
#endif

#define VECSIZE 8
#define I_BLOCKSIZE 32
#define J_BLOCKSIZE 32
#define K_BLOCKSIZE 32
#define UNROLL_1 4 // UNROLL_1 * VECSIZE <= min{I_BLOCKSIZE, J_BLOCKSIZE, K_BLOCKSIZE}
#define UNROLL_2 2 //UNROLL_2 * VECSIZE <= min{I_BLOCKSIZE, J_BLOCKSIZE, K_BLOCKSIZE}
#define ITER_NUM 1
/* Definition Section - END */


/* class System - START */
class System
{
	//...
};
/* class System - END */


/* class Float - START */
class Float // Type of scalar field
{
	float _num;

public:
	class vec;

	// constructors
	inline Float();
	inline Float(float& num);
	inline Float(float&& num);
	inline Float(Float& F);
	inline Float(Float&& F) noexcept;

	// assignment
	inline Float& operator = (Float& F);
	inline Float& operator = (Float&& F) noexcept;
	inline Float& operator = (float& num);
	inline Float& operator = (float&& num);
	inline Float& operator = (vec& V);  //_mm256_storeu_ps
	inline Float& operator = (vec&& V); //_mm256_storeu_ps

	// naive sum operator
	inline friend Float operator + (Float& A, Float& B);
	inline friend Float operator + (Float& A, Float&& B);
	inline friend Float operator + (Float&& A, Float& B);
	inline friend Float operator + (Float&& A, Float&& B);

	// naive sub operator
	inline friend Float operator - (Float& A, Float& B);
	inline friend Float operator - (Float& A, Float&& B);
	inline friend Float operator - (Float&& A, Float& B);
	inline friend Float operator - (Float&& A, Float&& B);

	// naive multiplication operator
	inline friend Float operator * (Float& A, Float& B);
	inline friend Float operator * (Float& A, Float&& B);
	inline friend Float operator * (Float&& A, Float& B);
	inline friend Float operator * (Float&& A, Float&& B);

	// naive division operator
	inline friend Float operator / (Float& A, Float& B);
	inline friend Float operator / (Float& A, Float&& B);
	inline friend Float operator / (Float&& A, Float& B);
	inline friend Float operator / (Float&& A, Float&& B);

	// accessors
	inline float data();
	inline float* adress();

	//...

	class vec // Type of AVX vector
	{
		vectypefloat _v;

	public:
		// constructors
		inline vec();
		inline vec(vectypefloat& v);
		inline vec(vectypefloat&& v);
		inline vec(float* p); // or inline void load(float *p); //_mm256_loadu_ps
		inline vec(Float* p); // or inline void load(Float *p); //_mm256_loadu_ps
		inline vec(Float& F); // _mm256_broadcast_ss
		inline vec(Float&& F); // _mm256_broadcast_ss
		inline vec(vec& V);
		inline vec(vec&& V);

		// assignment
		inline vec& operator = (vec& V);
		inline vec& operator = (vec&& V) noexcept;
		inline vec& operator = (float* p); //_mm256_loadu_ps
		inline vec& operator = (Float* p); //_mm256_loadu_ps
		inline vec& operator = (Float& F); // or inline void set(Float& x); //_mm256_broadcast_ss
		inline vec& operator = (Float&& F);//or inline void set(Float&& x); //_mm256_broadcast_ss

		// geters and seters
		inline vectypefloat data();
		inline vectypefloat* adress();

		/* Arithmetic Operators - START */

		// sum operator
		inline friend vec operator + (vec& A, vec& B); //_mm256_add_ps
		inline friend vec operator + (vec& A, vec&& B); //_mm256_add_ps
		inline friend vec operator + (vec&& A, vec& B); //_mm256_add_ps
		inline friend vec operator + (vec&& A, vec&& B); //_mm256_add_ps

		// sub operator
		inline friend vec operator - (vec& A, vec& B); //_mm256_sub_ps
		inline friend vec operator - (vec& A, vec&& B); //_mm256_sub_ps
		inline friend vec operator - (vec&& A, vec& B); //_mm256_sub_ps
		inline friend vec operator - (vec&& A, vec&& B); //_mm256_sub_ps

		// multiplication operator
		inline friend vec operator * (vec& A, vec& B); //_mm256_mul_ps
		inline friend vec operator * (vec& A, vec&& B); //_mm256_mul_ps
		inline friend vec operator * (vec&& A, vec& B); //_mm256_mul_ps
		inline friend vec operator * (vec&& A, vec&& B); //_mm256_mul_ps

		// division operator
		inline friend vec operator / (vec& A, vec& B); //_mm256_div_ps
		inline friend vec operator / (vec& A, vec&& B); //_mm256_div_ps
		inline friend vec operator / (vec&& A, vec& B); //_mm256_div_ps
		inline friend vec operator / (vec&& A, vec&& B); //_mm256_div_ps

		/* Arithmetic Operators - END */

		inline friend vec mul_add(vec& A, vec& B, vec& C); //_mm256_fmadd_ps // return A * B + C
		inline friend vec mul_sub(vec& A, vec& B, vec& C); //_mm256_fmadd_ps // return A * B - C

		//...
	};
};
/* class Float - END */


/*
//class Int
//class Long
//template <size_t base> class GF; GF<base>
//class Bool
//class Double
//class Float
//class Complex_Double
//class Complex_Float
*/


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

	// Slices ??? "Probably class Slice"
	//...
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
	//...
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

	//...
};
/* class Vector - END */


#endif /* Header_h */