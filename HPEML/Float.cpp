#include "Header.h"

/* Float class - START */

// constructors
inline Float::Float() : _num(0) {}
inline Float::Float(float& num) : _num(num) {}
inline Float::Float(float&& num) : _num(move(num)) {}
inline Float::Float(Float& F) { _num = F._num; }
inline Float::Float(Float&& F) : _num(move(F._num)) {}

// assignment 
inline Float& Float::operator=(Float& F)
{
	if (this != &F)
		_num = F._num;

	return *this;
}

inline Float& Float::operator=(Float&& F)
{
	if (this != &F)
		_num = move(F._num);

	return *this;
}

// QUESTION: what's the purpose of operators like this? with float&
inline Float& Float::operator=(float& num)
{
	if (&_num != &num)
		_num = num;

	return *this;
}

inline Float& Float::operator=(float&& num)
{
	if (&_num != &num)
		_num = num;

	return *this;
}

// QUESTION: how to get into attributes of class vec inside Float?
// QUESTION: How to use with storeu if there isn't float* attribute inside the Float class
inline Float& Float::operator=(vec& V)
{
	return *this;
}

inline Float& Float::operator=(vec&& V)
{
	return *this;
}

// accessors
inline float Float::data() { return _num; }
inline float* Float::adress() { return &_num; }

/* Float class - END */


/* vec class - START */

// constructors
inline Float::vec::vec() : _v(_mm256_setzero_ps()) {}
inline Float::vec::vec(vectypefloat& v) : _v(v){}
inline Float::vec::vec(vectypefloat&& v) : _v(v) {}
inline Float::vec::vec(float* p) : _v(_mm256_loadu_ps(p)){}
inline Float::vec::vec(Float* p) : _v(_mm256_loadu_ps(p->_num)) {} // QUESTION: What to load?
inline Float::vec::vec(vec& V) : _v(V._v) {}
inline Float::vec::vec(vec&& V) : _v(move(V._v)) {}

// assignment operators
inline Float::vec& Float::vec::operator = (vec& V) // QUESTION: What it'll return if I'll use *this
{
	if (this != &V)
		_v = V._v;

	return *this;
}

// sum operators
inline Float::vec operator + (Float::vec& A, Float::vec& B) { return _mm256_add_ps(A._v, B._v); }
inline Float::vec operator + (Float::vec& A, Float::vec&& B) { return _mm256_add_ps(A._v, B._v); }
inline Float::vec operator + (Float::vec&& A, Float::vec& B) { return _mm256_add_ps(A._v, B._v); }
inline Float::vec operator + (Float::vec&& A, Float::vec&& B) { return _mm256_add_ps(A._v, B._v); }

// sub operators
inline Float::vec operator - (Float::vec& A, Float::vec& B) { return _mm256_sub_ps(A._v, B._v); }
inline Float::vec operator - (Float::vec& A, Float::vec&& B) { return _mm256_sub_ps(A._v, B._v); }
inline Float::vec operator - (Float::vec&& A, Float::vec& B) { return _mm256_sub_ps(A._v, B._v); }
inline Float::vec operator - (Float::vec&& A, Float::vec&& B) { return _mm256_sub_ps(A._v, B._v); }

// multiplication operator
inline Float::vec operator * (Float::vec& A, Float::vec& B) { return _mm256_mul_ps(A._v, B._v); }
inline Float::vec operator * (Float::vec& A, Float::vec&& B) { return _mm256_mul_ps(A._v, B._v); }
inline Float::vec operator * (Float::vec&& A, Float::vec& B) { return _mm256_mul_ps(A._v, B._v); }
inline Float::vec operator * (Float::vec&& A, Float::vec&& B) { return _mm256_mul_ps(A._v, B._v); }

// division operator
inline Float::vec operator / (Float::vec& A, Float::vec& B) { return _mm256_div_ps(A._v, B._v); }
inline Float::vec operator / (Float::vec& A, Float::vec&& B) { return _mm256_div_ps(A._v, B._v); }
inline Float::vec operator / (Float::vec&& A, Float::vec& B) { return _mm256_div_ps(A._v, B._v); }
inline Float::vec operator / (Float::vec&& A, Float::vec&& B) { return _mm256_div_ps(A._v, B._v); }

/* vec class - START */