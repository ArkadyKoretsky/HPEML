#include "Header.h"
template<typename scalar, typename T>
Memory_Block<scalar, T>::Memory_Block()
{
}
template <typename scalar, typename T>
Memory_Block < typename scalar, typename T>::Memory_Block(size_t row, size_t col)
{
	_row = row;
	_col = col;
}
template <typename scalar, typename T>
Memory_Block < typename scalar, typename T>::Memory_Block(size_t row, size_t col, scalar val)
{
	Memory_Block(size_t row, size_t col);
	_mat = val;
}

template<typename scalar, typename T>
Memory_Block<scalar, T>::Memory_Block(size_t row, size_t col, std::string type)
{
}

template<typename scalar, typename T>
Memory_Block<scalar, T>::Memory_Block(std::initializer_list<std::initializer_list<scalar>> list_lists)
{
}

template<typename scalar, typename T>
Memory_Block<scalar, T>::Memory_Block(std::vector<std::vector<scalar>>& vec_vecs)
{
}

template<typename scalar, typename T>
Memory_Block<scalar, T>::Memory_Block(std::vector<std::vector<scalar>>&& vec_vecs)
{
}

template<typename scalar, typename T>
Memory_Block<scalar, T>::Memory_Block(const Memory_Block& M)
{
	_mat = M._mat;
	_row = M._row;
	_col = M._col;
}

template<typename scalar, typename T>
Memory_Block<scalar, T>::Memory_Block(Memory_Block&& M)
{
}

template<typename scalar, typename T>
inline scalar& Memory_Block<scalar, T>::operator()(size_t i, size_t j)
{
	return _mat + _col * i + j;
}

template<typename scalar, typename T>
inline scalar* Memory_Block<scalar, T>::operator[](size_t i)
{
	return _mat + _col * i;
}

template<typename scalar, typename T>
T Memory_Block<scalar, T>::operator()(size_t row_1, size_t row_2, size_t col_1, size_t col_2)
{
	size_t vecsize = VECSIZE, i, j, k;
	if (col_2 >= vecsize)
	{
		for (i = row_1, k = 0; i < row_2; i++)
		{
			for (j = c_1; j < col_2 - vecsize; j += vecsize, k += vecsize)
			{
				_mm256_storeu_ps(T + k, _mm256_loadu_ps(_mat + i * _col + j));
			}

			for (; j < col_2; j++, k++)
			{
				T[k] = _mat[i * _col + j];
			}
		}
	}
	else
	{
		for (i = row_1, k = 0; i < row_2; i++)
		{
			for (j = col_1; j < col_2; j++, k++)
			{
				T[k] = _mat[i * _col + j];
			}
		}
	}
	return T();
}

template<typename scalar, typename T>
inline scalar* Memory_Block<scalar, T>::get_data()
{
	return _mat;
}

template<typename scalar, typename T>
inline size_t Memory_Block<scalar, T>::get_rows()
{
	return size_t();
}

template<typename scalar, typename T>
inline size_t Memory_Block<scalar, T>::get_cols()
{
	return _col;
}

template<typename scalar, typename T>
inline void Memory_Block<scalar, T>::set_data(scalar* data)
{
	_mat = data;
}

template<typename scalar, typename T>
inline void Memory_Block<scalar, T>::set_rows(size_t rows)
{
	_row = rows;
}

template<typename scalar, typename T>
inline void Memory_Block<scalar, T>::set_cols(size_t cols)
{
	_col = cols;
}
