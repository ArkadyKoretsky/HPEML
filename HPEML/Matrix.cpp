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

	return *this;
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

	return *this;
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

	return *this;
}

/* Arithmetic Operators - START */

/* Sum Operator - START */
template <typename scalar>
inline Matrix<scalar> operator+(Matrix<scalar>& A, Matrix<scalar>& B)
{
	if (A._row != B._row || A._col != B._col)
		throw "Can't Sum! Wrong Dimensions!";

	Matrix<scalar> matrix(A._row, A._col);
	size_t i, sizeOfMatrix = A._row * A._col, vecsize = VECSIZE;
	
	if (sizeOfMatrix >= vecsize)
	{
		for (i = 0; i < sizeOfMatrix - vecsize; i += vecsize)
			matrix[i] = scalar::vec(A._mat + i) + scalar::vec(B._mat + i);

		for (; i < sizeOfMatrix; ++i)
			matrix[i] = A._mat[i] + B._mat[i];
	}

	else
	{
		for (i = 0; i < sizeOfMatrix; ++i)
			matrix[i] = A._mat[i] + B._mat[i];
	}

	return matrix;
}

template <typename scalar>
inline Matrix<scalar> operator+(Matrix<scalar>& A, Matrix<scalar>&& B)
{
	if (A._row != B._row || A._col != B._col)
		throw "Can't Sum! Wrong Dimensions!";

	Matrix<scalar> matrix(A._row, A._col);
	size_t i, sizeOfMatrix = A._row * A._col, vecsize = VECSIZE;

	if (sizeOfMatrix >= vecsize)
	{
		for (i = 0; i < sizeOfMatrix - vecsize; i += vecsize)
			matrix[i] = scalar::vec(A._mat + i) + scalar::vec(B._mat + i);

		for (; i < sizeOfMatrix; ++i)
			matrix[i] = A._mat[i] + B._mat[i];
	}

	else
	{
		for (i = 0; i < sizeOfMatrix; ++i)
			matrix[i] = A._mat[i] + B._mat[i];
	}

	return matrix;
}

template <typename scalar>
inline Matrix<scalar> operator+(Matrix<scalar>&& A, Matrix<scalar>& B)
{
	if (A._row != B._row || A._col != B._col)
		throw "Can't Sum! Wrong Dimensions!";

	Matrix<scalar> matrix(A._row, A._col);
	size_t i, sizeOfMatrix = A._row * A._col, vecsize = VECSIZE;

	if (sizeOfMatrix >= vecsize)
	{
		for (i = 0; i < sizeOfMatrix - vecsize; i += vecsize)
			matrix[i] = scalar::vec(A._mat + i) + scalar::vec(B._mat + i);

		for (; i < sizeOfMatrix; ++i)
			matrix[i] = A._mat[i] + B._mat[i];
	}

	else
	{
		for (i = 0; i < sizeOfMatrix; ++i)
			matrix[i] = A._mat[i] + B._mat[i];
	}

	return matrix;
}

template <typename scalar>
inline Matrix<scalar> operator+(Matrix<scalar>&& A, Matrix<scalar>&& B)
{
	if (A._row != B._row || A._col != B._col)
		throw "Can't Sum! Wrong Dimensions!";

	Matrix<scalar> matrix(A._row, A._col);
	size_t i, sizeOfMatrix = A._row * A._col, vecsize = VECSIZE;

	if (sizeOfMatrix >= vecsize)
	{
		for (i = 0; i < sizeOfMatrix - vecsize; i += vecsize)
			matrix[i] = scalar::vec(A._mat + i) + scalar::vec(B._mat + i);

		for (; i < sizeOfMatrix; ++i)
			matrix[i] = A._mat[i] + B._mat[i];
	}

	else
	{
		for (i = 0; i < sizeOfMatrix; ++i)
			matrix[i] = A._mat[i] + B._mat[i];
	}

	return matrix;
}
/* Sum Operator - END */

/* Arithmetic Operators - END */