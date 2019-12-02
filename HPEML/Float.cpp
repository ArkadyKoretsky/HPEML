#include "Header.h"

// constructors
inline Float::Float() : _num(0) {}
inline Float::Float(float& num) : _num(num) {}
inline Float::Float(float&& num) : _num(num) {}
inline Float::Float(Float& F) { _num = F._num; }
inline Float::Float(Float&& F) { _num = F._num; }

/* vec class - START */

// assignment operators
inline Float::vec& Float::vec::operator=(vec& V)
{
	if (this != &V)
	{
		this->_v = V._v;
	}
}

// sum operators
inline Float::vec operator+(Float::vec& A, Float::vec& B) { return _mm256_add_ps(A._v, B._v); }
inline Float::vec operator+(Float::vec& A, Float::vec&& B) { return _mm256_add_ps(A._v, B._v); }
inline Float::vec operator+(Float::vec&& A, Float::vec& B) { return _mm256_add_ps(A._v, B._v); }
inline Float::vec operator+(Float::vec&& A, Float::vec&& B) { return _mm256_add_ps(A._v, B._v); }

/* vec class - START */