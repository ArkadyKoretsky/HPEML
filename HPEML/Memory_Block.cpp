#include "Header.h"

// constructors
template<typename scalar, typename T>
inline Memory_Block<scalar, T>::Memory_Block(size_t row, size_t col) : _row(row), _col(col), _mat(new scalar[row * col]) {}