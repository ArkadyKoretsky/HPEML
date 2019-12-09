#include "Header.h"

template <typename scalar>
Matrix<scalar>& operator+=(Matrix<scalar>& A, Matrix<scalar>& B)
{
	if (A._row != B._row || A._col != B._col)
		throw "Matrices Have Different Dimensions!";
	else
	{

		size_t vecsize = VECSIZE, matrixSize = A._row * A._col, i;

		if (matrixSize >= vecsize)
		{
			for (i = 0; i < matrixSize - vecsize; i += vecsize)
				_mm256_storeu_ps(A._mat + i, _mm256_add_ps(_mm256_loadu_ps(A._mat + i), _mm256_loadu_ps(B._mat + i)));

			for (; i < matrixSize; i++)
				A._mat[i] += B._mat[i];
		}
		else
		{
			for (i = 0; i < matrixSize; i++)
				A._mat[i] += B._mat[i];
		}

		return A;
	}
}