#include "Header.h"

// constructors


/* Assignment Operators - START */
template<typename scalar>
inline Matrix<scalar>& Matrix<scalar>::operator = (const Matrix& M)
{
	if (this != &M)
	{
		this->_row = M.rows();
		this->_col = M.cols();
		size_t sizeOfMatrix = this->_row * this->_col;
		scalar* matrix = M.data();
		for (size_t i = 0; i < sizeOfMatrix; ++i)
			this->_mat[i] = matrix[i];
	}

	return *this;
}

template<typename scalar>
inline Matrix<scalar>& Matrix<scalar>::operator = (Matrix& M)
{
	if (this != &M)
	{
		this->_row = M.rows();
		this->_col = M.cols();
		size_t sizeOfMatrix = this->_row * this->_col;
		scalar* matrix = M.data();
		for (size_t i = 0; i < sizeOfMatrix; ++i)
			this->_mat[i] = matrix[i];
	}

	return *this;
}

template<typename scalar>
inline Matrix<scalar>& Matrix<scalar>::operator = (Matrix&& M)
{
	if (this != &M)
	{
		this->_row = M.rows();
		this->_col = M.cols();
		size_t sizeOfMatrix = this->_row * this->_col;
		scalar* matrix = M.data();
		for (size_t i = 0; i < sizeOfMatrix; ++i)
			this->_mat[i] = matrix[i];
	}

	return *this;
}
/* Assignment Operators - END */

/* Sum Operator - START */
template <typename scalar>
inline Matrix<scalar> operator + (Matrix<scalar>& A, Matrix<scalar>& B)
{
	size_t row = A.rows(), col = A.cols();
	if (row != B.rows() || col != B.cols())
		throw "Can't Sum! Wrong Dimensions!";

	Matrix<scalar> matrix(row, col);
	size_t i, sizeOfMatrix = row * col, vecsize = VECSIZE;
	scalar *dataOfA = A.data(), *dataOfB = B.data(), *result = matrix.data();
	
	if (sizeOfMatrix >= vecsize)
	{
		for (i = 0; i < sizeOfMatrix - vecsize; i += vecsize)
			result[i] = scalar::vec(dataOfA + i) + scalar::vec(dataOfB + i);

		for (; i < sizeOfMatrix; ++i)
			result[i] = dataOfA[i] + dataOfB[i];
	}

	else
	{
		for (i = 0; i < sizeOfMatrix; ++i)
			result[i] = dataOfA[i] + dataOfB[i];
	}

	return matrix;
}

template <typename scalar>
inline Matrix<scalar> operator + (Matrix<scalar>& A, Matrix<scalar>&& B)
{
	size_t row = A.rows(), col = A.cols();
	if (row != B.rows() || col != B.cols())
		throw "Can't Sum! Wrong Dimensions!";

	Matrix<scalar> matrix(row, col);
	size_t i, sizeOfMatrix = row * col, vecsize = VECSIZE;
	scalar* dataOfA = A.data(), * dataOfB = B.data(), * result = matrix.data();

	if (sizeOfMatrix >= vecsize)
	{
		for (i = 0; i < sizeOfMatrix - vecsize; i += vecsize)
			result[i] = scalar::vec(dataOfA + i) + scalar::vec(dataOfB + i);

		for (; i < sizeOfMatrix; ++i)
			result[i] = dataOfA[i] + dataOfB[i];
	}

	else
	{
		for (i = 0; i < sizeOfMatrix; ++i)
			result[i] = dataOfA[i] + dataOfB[i];
	}

	return matrix;
}

template <typename scalar>
inline Matrix<scalar> operator + (Matrix<scalar>&& A, Matrix<scalar>& B)
{
	size_t row = A.rows(), col = A.cols();
	if (row != B.rows() || col != B.cols())
		throw "Can't Sum! Wrong Dimensions!";

	Matrix<scalar> matrix(row, col);
	size_t i, sizeOfMatrix = row * col, vecsize = VECSIZE;
	scalar* dataOfA = A.data(), * dataOfB = B.data(), * result = matrix.data();

	if (sizeOfMatrix >= vecsize)
	{
		for (i = 0; i < sizeOfMatrix - vecsize; i += vecsize)
			result[i] = scalar::vec(dataOfA + i) + scalar::vec(dataOfB + i);

		for (; i < sizeOfMatrix; ++i)
			result[i] = dataOfA[i] + dataOfB[i];
	}

	else
	{
		for (i = 0; i < sizeOfMatrix; ++i)
			result[i] = dataOfA[i] + dataOfB[i];
	}

	return matrix;
}

template <typename scalar>
inline Matrix<scalar> operator + (Matrix<scalar>&& A, Matrix<scalar>&& B)
{
	size_t row = A.rows(), col = A.cols();
	if (row != B.rows() || col != B.cols())
		throw "Can't Sum! Wrong Dimensions!";

	Matrix<scalar> matrix(row, col);
	size_t i, sizeOfMatrix = row * col, vecsize = VECSIZE;
	scalar* dataOfA = A.data(), * dataOfB = B.data(), * result = matrix.data();

	if (sizeOfMatrix >= vecsize)
	{
		for (i = 0; i < sizeOfMatrix - vecsize; i += vecsize)
			result[i] = scalar::vec(dataOfA + i) + scalar::vec(dataOfB + i);

		for (; i < sizeOfMatrix; ++i)
			result[i] = dataOfA[i] + dataOfB[i];
	}

	else
	{
		for (i = 0; i < sizeOfMatrix; ++i)
			result[i] = dataOfA[i] + dataOfB[i];
	}

	return matrix;
}
/* Sum Operator - END */

/* Sub Operator - START */
template <typename scalar>
inline Matrix<scalar> operator - (Matrix<scalar>& A, Matrix<scalar>& B)
{
	size_t row = A.rows(), col = A.cols();
	if (row != B.rows() || col != B.cols())
		throw "Can't Sub! Wrong Dimensions!";

	Matrix<scalar> matrix(row, col);
	size_t i, sizeOfMatrix = row * col, vecsize = VECSIZE;
	scalar* dataOfA = A.data(), * dataOfB = B.data(), * result = matrix.data();

	if (sizeOfMatrix >= vecsize)
	{
		for (i = 0; i < sizeOfMatrix - vecsize; i += vecsize)
			result[i] = scalar::vec(dataOfA + i) - scalar::vec(dataOfB + i);

		for (; i < sizeOfMatrix; ++i)
			result[i] = dataOfA[i] - dataOfB[i];
	}

	else
	{
		for (i = 0; i < sizeOfMatrix; ++i)
			result[i] = dataOfA[i] - dataOfB[i];
	}

	return matrix;
}

template <typename scalar>
inline Matrix<scalar> operator - (Matrix<scalar>& A, Matrix<scalar>&& B)
{
	size_t row = A.rows(), col = A.cols();
	if (row != B.rows() || col != B.cols())
		throw "Can't Sub! Wrong Dimensions!";

	Matrix<scalar> matrix(row, col);
	size_t i, sizeOfMatrix = row * col, vecsize = VECSIZE;
	scalar* dataOfA = A.data(), * dataOfB = B.data(), * result = matrix.data();

	if (sizeOfMatrix >= vecsize)
	{
		for (i = 0; i < sizeOfMatrix - vecsize; i += vecsize)
			result[i] = scalar::vec(dataOfA + i) - scalar::vec(dataOfB + i);

		for (; i < sizeOfMatrix; ++i)
			result[i] = dataOfA[i] - dataOfB[i];
	}

	else
	{
		for (i = 0; i < sizeOfMatrix; ++i)
			result[i] = dataOfA[i] - dataOfB[i];
	}

	return matrix;
}

template <typename scalar>
inline Matrix<scalar> operator - (Matrix<scalar>&& A, Matrix<scalar>& B)
{
	size_t row = A.rows(), col = A.cols();
	if (row != B.rows() || col != B.cols())
		throw "Can't Sub! Wrong Dimensions!";

	Matrix<scalar> matrix(row, col);
	size_t i, sizeOfMatrix = row * col, vecsize = VECSIZE;
	scalar* dataOfA = A.data(), * dataOfB = B.data(), * result = matrix.data();

	if (sizeOfMatrix >= vecsize)
	{
		for (i = 0; i < sizeOfMatrix - vecsize; i += vecsize)
			result[i] = scalar::vec(dataOfA + i) - scalar::vec(dataOfB + i);

		for (; i < sizeOfMatrix; ++i)
			result[i] = dataOfA[i] - dataOfB[i];
	}

	else
	{
		for (i = 0; i < sizeOfMatrix; ++i)
			result[i] = dataOfA[i] - dataOfB[i];
	}

	return matrix;
}

template <typename scalar>
inline Matrix<scalar> operator - (Matrix<scalar>&& A, Matrix<scalar>&& B)
{
	size_t row = A.rows(), col = A.cols();
	if (row != B.rows() || col != B.cols())
		throw "Can't Sub! Wrong Dimensions!";

	Matrix<scalar> matrix(row, col);
	size_t i, sizeOfMatrix = row * col, vecsize = VECSIZE;
	scalar* dataOfA = A.data(), * dataOfB = B.data(), * result = matrix.data();

	if (sizeOfMatrix >= vecsize)
	{
		for (i = 0; i < sizeOfMatrix - vecsize; i += vecsize)
			result[i] = scalar::vec(dataOfA + i) - scalar::vec(dataOfB + i);

		for (; i < sizeOfMatrix; ++i)
			result[i] = dataOfA[i] - dataOfB[i];
	}

	else
	{
		for (i = 0; i < sizeOfMatrix; ++i)
			result[i] = dataOfA[i] - dataOfB[i];
	}

	return matrix;
}

/* Arithmetic Operators - END */