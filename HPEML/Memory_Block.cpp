#include "Header.h"
template<typename scalar, typename T>
Memory_Block<scalar, T>::Memory_Block() : _mat(nullptr), _row(0), _col(0) {}

template <typename scalar, typename T>
Memory_Block < typename scalar, typename T>::Memory_Block(size_t row, size_t col) : _mat(nullptr), _row(row), _col(col) {}

template <typename scalar, typename T>
Memory_Block < typename scalar, typename T>::Memory_Block(size_t row, size_t col, scalar val) : _mat(val) { Memory_Block(size_t row, size_t col); }

template<typename scalar, typename T>
Memory_Block<scalar, T>::Memory_Block(size_t row, size_t col, string type) {}

template<typename scalar, typename T>
Memory_Block<scalar, T>::Memory_Block(initializer_list<initializer_list<scalar>> list_lists) {}

template<typename scalar, typename T>
Memory_Block<scalar, T>::Memory_Block(vector<vector<scalar>>& vec_vecs) {}

template<typename scalar, typename T>
Memory_Block<scalar, T>::Memory_Block(vector<vector<scalar>>&& vec_vecs) {}

template<typename scalar, typename T>
Memory_Block<scalar, T>::Memory_Block(const Memory_Block& M) : _mat(M._mat), _row(M._row), _col(M._col) {}

template<typename scalar, typename T>
Memory_Block<scalar, T>::Memory_Block(Memory_Block&& M) : _mat(M._mat), _row(M._row), _col(M._col) {}

template<typename scalar, typename T>
inline scalar& Memory_Block<scalar, T>::operator()(size_t i, size_t j) { return _mat + _col * i + j; }

template<typename scalar, typename T>
inline scalar* Memory_Block<scalar, T>::operator[](size_t i) { return _mat + _col * i; }

template<typename scalar, typename T>
T Memory_Block<scalar, T>::operator()(size_t upperRow, size_t lowerRow, size_t leftCol, size_t rightCol)
{
	size_t vecsize = VECSIZE, i, j, k;
	if (rightCol >= vecsize)
	{
		for (i = upperRow, k = 0; i < lowerRow; i++)
		{
			for (j = leftCol; j < rightCol - vecsize; j += vecsize, k += vecsize)
				_mm256_storeu_ps(T + k, _mm256_loadu_ps(_mat + i * _col + j));

			for (; j < rightCol; j++, k++)
				T[k] = _mat[i * _col + j];
		}
	}
	else
	{
		for (i = upperRow, k = 0; i < lowerRow; i++)
		{
			for (j = leftCol; j < rightCol; j++, k++)
				T[k] = _mat[i * _col + j];
		}
	}
	return T();
}

template<typename scalar, typename T>
inline scalar* Memory_Block<scalar, T>::get_data() { return _mat; }

template<typename scalar, typename T>
inline size_t Memory_Block<scalar, T>::get_rows() { return size_t(); }

template<typename scalar, typename T>
inline size_t Memory_Block<scalar, T>::get_cols() { return _col; }

template<typename scalar, typename T>
inline void Memory_Block<scalar, T>::set_data(scalar* data) { _mat = data; }

template<typename scalar, typename T>
inline void Memory_Block<scalar, T>::set_rows(size_t rows) { _row = rows; }

template<typename scalar, typename T>
inline void Memory_Block<scalar, T>::set_cols(size_t cols) { _col = cols; }

template<typename scalar, typename T>
inline Memory_Block& Memory_Block<scalar, T>::operator=(const Memory_Block& M)
{
	if (this != &M)
	{
		delete[] _mat;
		_mat = M._mat;
		_row = M._row;
		_col = M._col;
	}
	return *this;
}


template<typename scalar, typename T>
inline Memory_Block& Memory_Block<scalar, T>::operator=(Memory_Block&& M)
{
	if (this != &M)
	{
		delete[] _mat;
		_mat = M._mat;
		_row = M._row;
		_col = M._col;
	}
	return *this;
}

template<typename scalar, typename T>
Memory_Block<scalar, T>::~Memory_Block() { delete[] _mat; }

ostream& operator<<(ostream& out, Memory_Block& M)
{
	for (size_t i = 0; i < M._row; i++)
	{
		for (size_t j = 0; j < M._col; j++)
		{
			out << M.operator(i, j) << " ";
		}
		out << endl;
	}
	return out;
}

ostream& operator<<(ostream& out, Memory_Block&& M)
{
	for (size_t i = 0; i < M._row; i++)
	{
		for (size_t j = 0; j < M._col; j++)
		{
			out << M.operator(i, j) << " ";
		}
		out << endl;
	}
	return out;
}
