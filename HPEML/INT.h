#pragma once
#ifndef INT_Class
#define INT_Class

#include <immintrin.h>
#include <iostream>

class INT // Type of scalar field
{
	int _num;

public:
	class vec;

	// constructors
	inline INT() : _num(0) {}
	inline INT(int& num) : _num(num) {}
	inline INT(int&& num) : _num(num) {}
	inline INT(INT& F) : _num(F._num) {}
	inline INT(INT&& F) : _num(std::move(F._num)) {}

	/* Assignment Operators - START */
	inline INT& operator=(INT& F)
	{
		if (this != &F)
			_num = F._num;
		return *this;
	}

	inline INT& operator=(INT&& F)
	{
		if (this != &F)
			_num = std::move(F._num);
		return *this;
	}

	inline INT& operator=(int& num)
	{
		if (_num != num)
			_num = num;
		return *this;
	}

	inline INT& operator=(int&& num)
	{
		if (_num != num)
			_num = std::move(num);
		return *this;
	}

	inline INT& operator = (vec& V)
	{
		_mm256_storeu_si256(&_num, V.data());
		return *this;
	}

	inline INT& operator = (vec&& V)
	{
		_mm256_storeu_si256(&_num, V.data());
		return *this;
	}
	/* Assignment Operators - END */

	// Naive Sum
	inline friend INT operator + (INT& A, INT& B) { return INT(A.data() + B.data()); }
	inline friend INT operator + (INT& A, INT&& B) { return INT(A.data() + B.data()); }
	inline friend INT operator + (INT&& A, INT& B) { return INT(A.data() + B.data()); }
	inline friend INT operator + (INT&& A, INT&& B) { return INT(A.data() + B.data()); }

	// Naive Sub
	inline friend INT operator - (INT& A, INT& B) { return INT(A.data() - B.data()); }
	inline friend INT operator - (INT& A, INT&& B) { return INT(A.data() - B.data()); }
	inline friend INT operator - (INT&& A, INT& B) { return INT(A.data() - B.data()); }
	inline friend INT operator - (INT&& A, INT&& B) { return INT(A.data() - B.data()); }

	// Naive Multiplication
	inline friend INT operator * (INT& A, INT& B) { return INT(A.data() * B.data()); }
	inline friend INT operator * (INT& A, INT&& B) { return INT(A.data() * B.data()); }
	inline friend INT operator * (INT&& A, INT& B) { return INT(A.data() * B.data()); }
	inline friend INT operator * (INT&& A, INT&& B) { return INT(A.data() * B.data()); }

	// Naive Division
	inline friend INT operator / (INT& A, INT& B) { return INT(A.data() / B.data()); }
	inline friend INT operator / (INT& A, INT&& B) { return INT(A.data() / B.data()); }
	inline friend INT operator / (INT&& A, INT& B) { return INT(A.data() / B.data()); }
	inline friend INT operator / (INT&& A, INT&& B) { return INT(A.data() / B.data()); }

	// Getters
	inline int data() { return _num; }
	inline int* adress() { return &_num; }

	/* Double class - END */

	/* vec class - START */

	// output operator (most for debug purpose)
	inline friend std::ostream& operator << (std::ostream& out, INT& F)
	{
		out << F.data();
		return out;
	}

	inline friend std::ostream& operator << (std::ostream& out, INT&& F)
	{
		out << F.data();
		return out;
	}

	class vec // Type of AVX vector
	{
		__m256i _v;

	public:
		// constructors
		inline vec() :_v(_mm256_setzero_si256()) {}
		inline vec(__m256i& v) : _v(v) {}
		inline vec(__m256i&& v) : _v(std::move(v)) {}
		inline vec(int* p) : _v(_mm256_loadu_si256(p)) {}
		inline vec(INT* p) : _v(_mm256_loadu_si256(p->adress())) {}
		inline vec(INT& F) : _v(_mm256_broadcastd_epi32(F.adress())) {}
		inline vec(INT&& F) : _v(_mm256_broadcastd_epi32(F.adress())) {}
		inline vec(vec& V) : _v(V.data()) {}
		inline vec(vec&& V) noexcept : _v(std::move(V.data())) {}

		// assignment
		inline vec& operator = (vec& V)
		{
			if (this != &V)
				_v = V.data();
			return *this;
		}

		inline vec& operator = (vec&& V) noexcept
		{
			if (this != &V)
				_v = V.data();
			return *this;
		}
		inline vec& operator = (int* p)
		{
			_v = _mm256_loadu_si256(p);
			return *this;
		}

		inline vec& operator = (INT* p)
		{
			_v = _mm256_loadu_si256(p->adress());
			return *this;
		}

		inline vec& operator = (INT& F)
		{
			_v = _mm256_broadcastd_epi32(F.adress());
			return *this;
		}

		inline vec& operator = (INT&& F)
		{
			_v = _mm256_broadcastd_epi32(F.adress());
			return *this;
		}

		// geters and seters
		inline __m256i data() { return _v; }
		inline __m256i* adress() { return &_v; }

		// sum operator
		inline friend vec operator+(INT::vec& A, INT::vec& B) { return _mm256_add_epi32(A.data(), B.data()); }
		inline friend vec operator+(INT::vec& A, INT::vec&& B) { return _mm256_add_epi32(A.data(), B.data()); }
		inline friend vec operator+(INT::vec&& A, INT::vec& B) { return _mm256_add_epi32(A.data(), B.data()); }
		inline friend vec operator+(INT::vec&& A, INT::vec&& B) { return _mm256_add_epi32(A.data(), B.data()); }

		// sub operator
		inline friend vec operator-(INT::vec& A, INT::vec& B) { return _mm256_sub_epi32(A.data(), B.data()); }
		inline friend vec operator-(INT::vec& A, INT::vec&& B) { return _mm256_sub_epi32(A.data(), B.data()); }
		inline friend vec operator-(INT::vec&& A, INT::vec& B) { return _mm256_sub_epi32(A.data(), B.data()); }
		inline friend vec operator-(INT::vec&& A, INT::vec&& B) { return _mm256_sub_epi32(A.data(), B.data()); }

		// multiplication operator
		inline friend vec operator*(INT::vec& A, INT::vec& B) { return _mm256_mullo_epi32(A.data(), B.data()); }
		inline friend vec operator*(INT::vec& A, INT::vec&& B) { return _mm256_mullo_epi32(A.data(), B.data()); }
		inline friend vec operator*(INT::vec&& A, INT::vec& B) { return _mm256_mullo_epi32(A.data(), B.data()); }
		inline friend vec operator*(INT::vec&& A, INT::vec&& B) { return _mm256_mullo_epi32(A.data(), B.data()); }


		// division operator
		inline friend vec operator/(INT::vec& A, INT::vec& B) { return _mm256_castps_si256(_mm256_div_ps(_mm256_castsi256_ps(A.data()), _mm256_castsi256_ps(B.data()))); }
		inline friend vec operator/(INT::vec& A, INT::vec&& B) { return _mm256_castps_si256(_mm256_div_ps(_mm256_castsi256_ps(A.data()), _mm256_castsi256_ps(B.data()))); }
		inline friend vec operator/(INT::vec&& A, INT::vec& B) { return _mm256_castps_si256(_mm256_div_ps(_mm256_castsi256_ps(A.data()), _mm256_castsi256_ps(B.data()))); }
		inline friend vec operator/(INT::vec&& A, INT::vec&& B) { return _mm256_castps_si256(_mm256_div_ps(_mm256_castsi256_ps(A.data()), _mm256_castsi256_ps(B.data()))); }


		// A * B + C
		inline vec mul_add(INT::vec& A, INT::vec& B, INT::vec& C) { return  _mm256_castps_si256(_mm256_fmadd_ps(_mm256_castsi256_ps(A.data()), _mm256_castsi256_ps(B.data()), _mm256_castsi256_ps(C.data()))); }
		inline vec mul_add(INT::vec& A, INT::vec& B, INT::vec&& C) { return  _mm256_castps_si256(_mm256_fmadd_ps(_mm256_castsi256_ps(A.data()), _mm256_castsi256_ps(B.data()), _mm256_castsi256_ps(C.data()))); }
		inline vec mul_add(INT::vec& A, INT::vec&& B, INT::vec& C) { return  _mm256_castps_si256(_mm256_fmadd_ps(_mm256_castsi256_ps(A.data()), _mm256_castsi256_ps(B.data()), _mm256_castsi256_ps(C.data()))); }
		inline vec mul_add(INT::vec& A, INT::vec&& B, INT::vec&& C) { return  _mm256_castps_si256(_mm256_fmadd_ps(_mm256_castsi256_ps(A.data()), _mm256_castsi256_ps(B.data()), _mm256_castsi256_ps(C.data()))); }
		inline vec mul_add(INT::vec&& A, INT::vec& B, INT::vec& C) { return  _mm256_castps_si256(_mm256_fmadd_ps(_mm256_castsi256_ps(A.data()), _mm256_castsi256_ps(B.data()), _mm256_castsi256_ps(C.data()))); }
		inline vec mul_add(INT::vec&& A, INT::vec& B, INT::vec&& C) { return  _mm256_castps_si256(_mm256_fmadd_ps(_mm256_castsi256_ps(A.data()), _mm256_castsi256_ps(B.data()), _mm256_castsi256_ps(C.data()))); }
		inline vec mul_add(INT::vec&& A, INT::vec&& B, INT::vec& C) { return  _mm256_castps_si256(_mm256_fmadd_ps(_mm256_castsi256_ps(A.data()), _mm256_castsi256_ps(B.data()), _mm256_castsi256_ps(C.data()))); }
		inline vec mul_add(INT::vec&& A, INT::vec&& B, INT::vec&& C) { return  _mm256_castps_si256(_mm256_fmadd_ps(_mm256_castsi256_ps(A.data()), _mm256_castsi256_ps(B.data()), _mm256_castsi256_ps(C.data()))); }


		// A * B - C
		inline vec mul_sub(INT::vec& A, INT::vec& B, INT::vec& C) { return  _mm256_castps_si256(_mm256_fmsub_ps(_mm256_castsi256_ps(A.data()), _mm256_castsi256_ps(B.data()), _mm256_castsi256_ps(C.data()))); }
		inline vec mul_sub(INT::vec& A, INT::vec& B, INT::vec&& C) { return  _mm256_castps_si256(_mm256_fmsub_ps(_mm256_castsi256_ps(A.data()), _mm256_castsi256_ps(B.data()), _mm256_castsi256_ps(C.data()))); }
		inline vec mul_sub(INT::vec& A, INT::vec&& B, INT::vec& C) { return  _mm256_castps_si256(_mm256_fmsub_ps(_mm256_castsi256_ps(A.data()), _mm256_castsi256_ps(B.data()), _mm256_castsi256_ps(C.data()))); }
		inline vec mul_sub(INT::vec& A, INT::vec&& B, INT::vec&& C) { return  _mm256_castps_si256(_mm256_fmsub_ps(_mm256_castsi256_ps(A.data()), _mm256_castsi256_ps(B.data()), _mm256_castsi256_ps(C.data()))); }
		inline vec mul_sub(INT::vec&& A, INT::vec& B, INT::vec& C) { return  _mm256_castps_si256(_mm256_fmsub_ps(_mm256_castsi256_ps(A.data()), _mm256_castsi256_ps(B.data()), _mm256_castsi256_ps(C.data()))); }
		inline vec mul_sub(INT::vec&& A, INT::vec& B, INT::vec&& C) { return  _mm256_castps_si256(_mm256_fmsub_ps(_mm256_castsi256_ps(A.data()), _mm256_castsi256_ps(B.data()), _mm256_castsi256_ps(C.data()))); }
		inline vec mul_sub(INT::vec&& A, INT::vec&& B, INT::vec& C) { return  _mm256_castps_si256(_mm256_fmsub_ps(_mm256_castsi256_ps(A.data()), _mm256_castsi256_ps(B.data()), _mm256_castsi256_ps(C.data()))); }
		inline vec mul_sub(INT::vec&& A, INT::vec&& B, INT::vec&& C) { return  _mm256_castps_si256(_mm256_fmsub_ps(_mm256_castsi256_ps(A.data()), _mm256_castsi256_ps(B.data()), _mm256_castsi256_ps(C.data()))); }
	};
};
#endif // ! INT_Class