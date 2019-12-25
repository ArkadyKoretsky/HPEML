#include "Header.h"

/* Float class - START */

// constructors
inline Float::Float() : _num(0) {}
inline Float::Float(float& num) : _num(num) {}
inline Float::Float(float&& num) : _num(move(num)) {}
inline Float::Float(Float& F) : _num(F.data()) {}
inline Float::Float(Float&& F) noexcept : _num(move(F.data())) {}

/* Assignment Operators - START */
inline Float& Float::operator = (Float& F)
{
	if (this != &F)
		_num = F.data();

	return *this;
}

inline Float& Float::operator = (Float&& F) noexcept
{
	if (this != &F)
		_num = move(F.data());

	return *this;
}

inline Float& Float::operator = (float& num)
{
	if (&_num != &num)
		_num = num;

	return *this;
}

inline Float& Float::operator = (float&& num)
{
	if (&_num != &num)
		_num = num;

	return *this;
}

inline Float& Float::operator = (Float::vec& V)
{
	_mm256_storeu_ps(&_num, V.data());
	return *this;
}

inline Float& Float::operator = (Float::vec&& V)
{
	_mm256_storeu_ps(&_num, V.data());
	return *this;
}
/* Assignment Operators - END */

// Naive Sum
inline Float operator + (Float& A, Float& B) { return Float(A.data() + B.data()); }
inline Float operator + (Float& A, Float&& B) { return Float(A.data() + B.data()); }
inline Float operator + (Float&& A, Float& B) { return Float(A.data() + B.data()); }
inline Float operator + (Float&& A, Float&& B) { return Float(A.data() + B.data()); }

// Naive Sub
inline Float operator - (Float& A, Float& B) { return Float(A.data() - B.data()); }
inline Float operator - (Float& A, Float&& B) { return Float(A.data() - B.data()); }
inline Float operator - (Float&& A, Float& B) { return Float(A.data() - B.data()); }
inline Float operator - (Float&& A, Float&& B) { return Float(A.data() - B.data()); }

// Naive Multiplication
inline Float operator * (Float& A, Float& B) { return Float(A.data() * B.data()); }
inline Float operator * (Float& A, Float&& B) { return Float(A.data() * B.data()); }
inline Float operator * (Float&& A, Float& B) { return Float(A.data() * B.data()); }
inline Float operator * (Float&& A, Float&& B) { return Float(A.data() * B.data()); }

// Naive Division
inline Float operator / (Float& A, Float& B) { return Float(A.data() / B.data()); }
inline Float operator / (Float& A, Float&& B) { return Float(A.data() / B.data()); }
inline Float operator / (Float&& A, Float& B) { return Float(A.data() / B.data()); }
inline Float operator / (Float&& A, Float&& B) { return Float(A.data() / B.data()); }

// Getters
inline float Float::data() { return _num; }
inline float* Float::adress() { return &_num; }

/* Float class - END */


/* vec class - START */

// constructors
inline Float::vec::vec() : _v(_mm256_setzero_ps()) {}
inline Float::vec::vec(vectypefloat& v) : _v(v) {}
inline Float::vec::vec(vectypefloat&& v) : _v(move(v)) {}
inline Float::vec::vec(float* p) : _v(_mm256_loadu_ps(p)) {}
inline Float::vec::vec(Float* p) : _v(_mm256_loadu_ps(p->adress())) {}

/* Assignment Operators - START */
inline Float::vec& Float::vec::operator = (vec& V)
{
	if (this != &V)
		_v = V.data();

	return *this;
}

inline Float::vec& Float::vec::operator = (vec&& V) noexcept
{
	if (this != &V)
		_v = V.data();

	return *this;
}

inline Float::vec& Float::vec::operator = (float* p)
{
	_v = _mm256_loadu_ps(p);
	return *this;
}

inline Float::vec& Float::vec::operator = (Float* p)
{
	_v = _mm256_loadu_ps(p->adress());
	return *this;
}
/* Assignment Operators - END */

// Sum Operators
inline Float::vec operator + (Float::vec& A, Float::vec& B) { return Float::vec(_mm256_add_ps(A.data(), B.data())); }
inline Float::vec operator + (Float::vec& A, Float::vec&& B) { return Float::vec(_mm256_add_ps(A.data(), B.data())); }
inline Float::vec operator + (Float::vec&& A, Float::vec& B) { return Float::vec(_mm256_add_ps(A.data(), B.data())); }
inline Float::vec operator + (Float::vec&& A, Float::vec&& B) { return Float::vec(_mm256_add_ps(A.data(), B.data())); }

// Sub Operators
inline Float::vec operator - (Float::vec& A, Float::vec& B) { return Float::vec(_mm256_sub_ps(A.data(), B.data())); }
inline Float::vec operator - (Float::vec& A, Float::vec&& B) { return Float::vec(_mm256_sub_ps(A.data(), B.data())); }
inline Float::vec operator - (Float::vec&& A, Float::vec& B) { return Float::vec(_mm256_sub_ps(A.data(), B.data())); }
inline Float::vec operator - (Float::vec&& A, Float::vec&& B) { return Float::vec(_mm256_sub_ps(A.data(), B.data())); }

// Multiplication Operator
inline Float::vec operator * (Float::vec& A, Float::vec& B) { return Float::vec(_mm256_mul_ps(A.data(), B.data())); }
inline Float::vec operator * (Float::vec& A, Float::vec&& B) { return Float::vec(_mm256_mul_ps(A.data(), B.data())); }
inline Float::vec operator * (Float::vec&& A, Float::vec& B) { return Float::vec(_mm256_mul_ps(A.data(), B.data())); }
inline Float::vec operator * (Float::vec&& A, Float::vec&& B) { return Float::vec(_mm256_mul_ps(A.data(), B.data())); }

// Division Operator
inline Float::vec operator / (Float::vec& A, Float::vec& B) { return Float::vec(_mm256_div_ps(A.data(), B.data())); }
inline Float::vec operator / (Float::vec& A, Float::vec&& B) { return Float::vec(_mm256_div_ps(A.data(), B.data())); }
inline Float::vec operator / (Float::vec&& A, Float::vec& B) { return Float::vec(_mm256_div_ps(A.data(), B.data())); }
inline Float::vec operator / (Float::vec&& A, Float::vec&& B) { return Float::vec(_mm256_div_ps(A.data(), B.data())); }

// Getters
inline vectypefloat Float::vec::data() { return _v; }
inline vectypefloat* Float::vec::adress() { return &_v; }

/* vec class - END */