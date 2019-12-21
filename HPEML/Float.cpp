#include "Header.h"

/* Float class - START */

// constructors
inline Float::Float() : _num(0) {}
inline Float::Float(float& num) : _num(num) {}
inline Float::Float(float&& num) : _num(move(num)) {}
inline Float::Float(Float& F) : _num(F.data()) {}
inline Float::Float(Float&& F) noexcept : _num(move(F.data())) {}


// assignment 
inline Float& Float::operator=(Float& F)
{
	if (this != &F)
		_num = F._num;

	return *this;
}

inline Float& Float::operator=(Float&& F) noexcept
{
	if (this != &F)
		_num = move(F._num);

	return *this;
}

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

// accessors
inline float Float::data() { return _num; }
inline float* Float::adress() { return &_num; }

/* Float class - END */


/* vec class - START */

// constructors
inline Float::vec::vec() : _v(_mm256_setzero_ps()) {}
inline Float::vec::vec(vectypefloat& v) : _v(v){}
inline Float::vec::vec(vectypefloat&& v) : _v(move(v)) {}
inline Float::vec::vec(float* p) : _v(_mm256_loadu_ps(p)){}

/* Assignment Operators - START */
inline Float::vec& Float::vec::operator = (vec& V)
{
	if (this != &V)
		_v = V._v;

	return *this;
}

inline Float::vec& Float::vec::operator = (vec&& V) noexcept
{
	if (this != &V)
		_v = V._v;

	return *this;
}

inline Float::vec& Float::vec::operator=(float* p) { _v = _mm256_loadu_ps(p); }

/* Assignment Operators - END */

// sum operators
inline Float::vec operator + (Float::vec& A, Float::vec& B) 
{ 
	vectypefloat result = _mm256_add_ps(A._v, B._v);
	return Float::vec(result);
}

inline Float::vec operator + (Float::vec& A, Float::vec&& B)
{
	vectypefloat result = _mm256_add_ps(A._v, B._v);
	return Float::vec(result);
}

inline Float::vec operator + (Float::vec&& A, Float::vec& B)
{
	vectypefloat result = _mm256_add_ps(A._v, B._v);
	return Float::vec(result);
}

inline Float::vec operator + (Float::vec&& A, Float::vec&& B)
{
	vectypefloat result = _mm256_add_ps(A._v, B._v);
	return Float::vec(result);
}

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

inline vectypefloat Float::vec::data() { return _v; }
inline vectypefloat* Float::vec::adress() { return &_v; }

/* vec class - END */