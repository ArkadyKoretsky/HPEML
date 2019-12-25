#include "Header.h"

// constructors
template<typename scalar, typename T>
inline Memory_Block<scalar, T>::Memory_Block(size_t row, size_t col) : _row(row), _col(col), _mat(new scalar[row * col]) {}

// getters
template<typename scalar, typename T>
inline scalar* Memory_Block<scalar, T>::data() { return _mat; }
template<typename scalar, typename T>
inline size_t Memory_Block<scalar, T>::rows() { return _row; }
template<typename scalar, typename T>
inline size_t Memory_Block<scalar, T>::cols() { return _col; }

// accessors
template<typename scalar, typename T>
inline scalar& Memory_Block<scalar, T>::operator () (size_t i, size_t j) { return _mat[i * _col + j]; }
template<typename scalar, typename T>
inline scalar* Memory_Block<scalar, T>::operator [] (size_t i) { return _mat + i * _col; }

// extractors
template<typename scalar, typename T>
T Memory_Block<scalar, T>::operator () (size_t upperRow, size_t lowerRow, size_t leftCol, size_t rightCol) // sub-matrix: (upperRow : lowerRow, leftCol : rightCol)
{
	size_t vecsize = VECSIZE, i, j, k;
	T subMemoryBlock(lowerRow - upperRow + 1, rightCol - leftCol + 1); // allocate sub matrix
	scalar* subMatrix = T.data();

	if (rightCol >= vecsize)
	{
		for (i = upperRow, k = 0; i < lowerRow; ++i)
		{
			for (j = leftCol; j < rightCol - vecsize; j += vecsize, k += vecsize)
				subMatrix[k] = scalar::vec((i,j)); // the operator () implemented above

			// TODO: continue the sub matrix extraction and fix the assignment operators at matrix class
		}
	}

	return subMemoryBlock;
}
