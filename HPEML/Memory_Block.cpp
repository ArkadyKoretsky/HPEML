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
inline scalar& Memory_Block<scalar, T>::operator()(size_t i, size_t j) { return _mat[i * _col + j]; }
template<typename scalar, typename T>
inline scalar* Memory_Block<scalar, T>::operator[](size_t i) { return _mat + i * _col }