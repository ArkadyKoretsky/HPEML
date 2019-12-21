#include "Header.h"

// constructors


// assignment operators
template<typename scalar>
inline Matrix<scalar>& Matrix<scalar>::operator=(const Matrix& M)
{
	if (this != &M)
	{
		_row = M._row;
		_col = M._col;
		size_t sizeOfMatrix = _row * _col;
		for (size_t i = 0; i < sizeOfMatrix; ++i)
			_mat[i] = M._mat[i];
	}

	return *this
}

template<typename scalar>
inline Matrix<scalar>& Matrix<scalar>::operator=(Matrix& M)
{
	if (this != &M)
	{
		_row = M._row;
		_col = M._col;
		size_t sizeOfMatrix = _row * _col;
		for (size_t i = 0; i < sizeOfMatrix; ++i)
			_mat[i] = M._mat[i];
	}

	return *this
}

template<typename scalar>
inline Matrix<scalar>& Matrix<scalar>::operator=(Matrix&& M)
{
	if (this != &M)
	{
		_row = M._row;
		_col = M._col;
		size_t sizeOfMatrix = _row * _col;
		for (size_t i = 0; i < sizeOfMatrix; ++i)
			_mat[i] = M._mat[i];
	}

	return *this
}

/* Arithmetic Operators - START */


// NOT SO USEFULL
template <typename scalar>
inline Matrix<scalar> operator+(Matrix<scalar>& A, Matrix<scalar>& B)
{
	if (A._row != B._row || A._col != B._col)
		throw "Can't Add! Wrong Dimensions!";

	Matrix<scalar> matrix(A._row, A._col);
	size_t i, sizeOfMatrix = A._row * A._col, vecsize = VECSIZE;
	scalar::vec result, vecA, vecB;
	auto tempA[vecsize], tempB[vecsize];

	if (sizeOfMatrix >= vecsize)
	{
		for (i = 0; i < sizeOfMatrix - vecsize; i += vecsize)
		{
			// store 8 values to work with AVX
			for (size_t j = 0, k = i; j < vecsize; ++j, ++k)
			{
				tempA[j] = A._mat[k].data();
				tempB[j] = B._mat[k].data();
			}

			// store in AVX data type
			vecA = tempA;
			vecB = tempB;
			result = vecA + vecB;
		}


		for (; i < sizeOfMatrix; ++i)
			C[i] = A._mat[i].data() + B[i]._mat[i].data();
	}

	return matrix;
}


// check with dan if we can implement functions like this
template <typename scalar>
inline Matrix<float> operator+(Matrix<float>& A, Matrix<float>& B)
{
	if (A._row != B._row || A._col != B._col)
		throw "Can't Add! Wrong Dimensions!";

	Matrix<float> matrix(A._row, A._col);

	//TODO: Implement with normal AVX

	return matrix;
}

template <typename scalar>
inline Matrix<int> operator+(Matrix<int>& A, Matrix<int>& B)
{
	if (A._row != B._row || A._col != B._col)
		throw "Can't Add! Wrong Dimensions!";

	Matrix<int> matrix(A._row, A._col);

	//TODO: Implement with normal AVX

	return matrix;
}

/* Arithmetic Operators - END */