#pragma once
#pragma once
#ifndef  Int64_Class
#define Int64_Class

#include <immintrin.h>
#include <iostream>

class Int64 // Type of scalar field
{
	int _num;

public:
	class vec;

	// constructors
	inline Int64() : _num(0) {}
	inline Int64(int& num) : _num(num) {}
	inline Int64(int&& num) : _num(num) {}
	inline Int64(Int64& F) : _num(F._num) {}
	inline Int64(Int64&& F) : _num(std::move(F._num)) {}

	/* Assignment Operators - START */
	inline Int64& operator=(Int64& F)
	{
		if (this != &F)
			_num = F._num;
		return *this;
	}

	inline Int64& operator=(Int64&& F)
	{
		if (this != &F)
			_num = std::move(F._num);
		return *this;
	}

	inline Int64& operator=(int& num)
	{
		if (_num != num)
			_num = num;
		return *this;
	}

	inline Int64& operator=(int&& num)
	{
		if (_num != num)
			_num = std::move(num);
		return *this;
	}

	inline Int64& operator = (vec& V)
	{
		_mm256_storeu_si256(&_num, V.data());
		return *this;
	}

	inline Int64& operator = (vec&& V)
	{
		_mm256_storeu_si256(&_num, V.data());
		return *this;
	}
	/* Assignment Operators - END */

	// Naive Sum
	inline friend Int64 operator + (Int64& A, Int64& B) { return Int64(A.data() + B.data()); }
	inline friend Int64 operator + (Int64& A, Int64&& B) { return Int64(A.data() + B.data()); }
	inline friend Int64 operator + (Int64&& A, Int64& B) { return Int64(A.data() + B.data()); }
	inline friend Int64 operator + (Int64&& A, Int64&& B) { return Int64(A.data() + B.data()); }

	// Naive Sub
	inline friend Int64 operator - (Int64& A, Int64& B) { return Int64(A.data() - B.data()); }
	inline friend Int64 operator - (Int64& A, Int64&& B) { return Int64(A.data() - B.data()); }
	inline friend Int64 operator - (Int64&& A, Int64& B) { return Int64(A.data() - B.data()); }
	inline friend Int64 operator - (Int64&& A, Int64&& B) { return Int64(A.data() - B.data()); }

	// Naive Multiplication
	inline friend Int64 operator * (Int64& A, Int64& B) { return Int64(A.data() * B.data()); }
	inline friend Int64 operator * (Int64& A, Int64&& B) { return Int64(A.data() * B.data()); }
	inline friend Int64 operator * (Int64&& A, Int64& B) { return Int64(A.data() * B.data()); }
	inline friend Int64 operator * (Int64&& A, Int64&& B) { return Int64(A.data() * B.data()); }

	// Naive Division
	inline friend Int64 operator / (Int64& A, Int64& B) { return Int64(A.data() / B.data()); }
	inline friend Int64 operator / (Int64& A, Int64&& B) { return Int64(A.data() / B.data()); }
	inline friend Int64 operator / (Int64&& A, Int64& B) { return Int64(A.data() / B.data()); }
	inline friend Int64 operator / (Int64&& A, Int64&& B) { return Int64(A.data() / B.data()); }

	// Getters
	inline int data() { return _num; }
	inline int* adress() { return &_num; }

	/* Double class - END */

	/* vec class - START */

	// output operator (most for debug purpose)
	inline friend std::ostream& operator << (std::ostream& out, Int64& F)
	{
		out << F.data();
		return out;
	}

	inline friend std::ostream& operator << (std::ostream& out, Int64&& F)
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
		inline vec(Int64* p) : _v(_mm256_loadu_si256(p->adress())) {}
		inline vec(Int64& F) : _v(_mm256_broadcastq_epi64(F.adress())) {}
		inline vec(Int64&& F) : _v(_mm256_broadcastq_epi64(F.adress())) {}
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
			_v = _mm256_loadu_pd(p);
			return *this;
		}

		inline vec& operator = (Int64* p)
		{
			_v = _mm256_loadu_si256(p->adress());
			return *this;
		}

		inline vec& operator = (Int64& F)
		{
			_v = _mm256_loadu_si256(F.adress());
			return *this;
		}

		inline vec& operator = (Int64&& F)
		{
			_v = _mm256_loadu_si256(F.adress());
			return *this;
		}

		// geters and seters
		inline __m256i data() { return _v; }
		inline __m256i* adress() { return &_v; }

		// sum operator
		inline friend vec operator+(Int64::vec& A, Int64::vec& B) { return _mm256_add_epi64(A.data(), B.data()); }
		inline friend vec operator+(Int64::vec& A, Int64::vec&& B) { return _mm256_add_epi64(A.data(), B.data()); }
		inline friend vec operator+(Int64::vec&& A, Int64::vec& B) { return _mm256_add_epi64(A.data(), B.data()); }
		inline friend vec operator+(Int64::vec&& A, Int64::vec&& B) { return _mm256_add_epi64(A.data(), B.data()); }

		// sub operator
		inline friend vec operator-(Int64::vec& A, Int64::vec& B) { return _mm256_sub_epi64(A.data(), B.data()); }
		inline friend vec operator-(Int64::vec& A, Int64::vec&& B) { return _mm256_sub_epi64(A.data(), B.data()); }
		inline friend vec operator-(Int64::vec&& A, Int64::vec& B) { return _mm256_sub_epi64(A.data(), B.data()); }
		inline friend vec operator-(Int64::vec&& A, Int64::vec&& B) { return _mm256_sub_epi64(A.data(), B.data()); }

		// multiplication operator
		inline friend vec operator*(Int64::vec& A, Int64::vec& B) { return _mm256_mullo_epi64(A.data(), B.data()); }
		inline friend vec operator*(Int64::vec& A, Int64::vec&& B) { return _mm256_mullo_epi64(A.data(), B.data()); }
		inline friend vec operator*(Int64::vec&& A, Int64::vec& B) { return _mm256_mullo_epi64(A.data(), B.data()); }
		inline friend vec operator*(Int64::vec&& A, Int64::vec&& B) { return _mm256_mullo_epi64(A.data(), B.data()); }


		// division operator
		inline friend vec operator/(Int64::vec& A, Int64::vec& B) { return _mm256_castps_si256(_mm256_div_ps(_mm256_castsi256_ps(A.data()), _mm256_castsi256_ps(B.data()))); }
		inline friend vec operator/(Int64::vec& A, Int64::vec&& B) { return _mm256_castps_si256(_mm256_div_ps(_mm256_castsi256_ps(A.data()), _mm256_castsi256_ps(B.data()))); }
		inline friend vec operator/(Int64::vec&& A, Int64::vec& B) { return _mm256_castps_si256(_mm256_div_ps(_mm256_castsi256_ps(A.data()), _mm256_castsi256_ps(B.data()))); }
		inline friend vec operator/(Int64::vec&& A, Int64::vec&& B) { return _mm256_castps_si256(_mm256_div_ps(_mm256_castsi256_ps(A.data()), _mm256_castsi256_ps(B.data()))); }


		// A * B + C
		inline vec mul_add(Int64::vec& A, Int64::vec& B, Int64::vec& C) { return  _mm256_castpd_si256(_mm256_fmadd_pd(_mm256_castsi256_pd(A.data()), _mm256_castsi256_pd(B.data()), _mm256_castsi256_pd(C.data()))); }
		inline vec mul_add(Int64::vec& A, Int64::vec& B, Int64::vec&& C) { return  _mm256_castpd_si256(_mm256_fmadd_pd(_mm256_castsi256_pd(A.data()), _mm256_castsi256_pd(B.data()), _mm256_castsi256_pd(C.data()))); }
		inline vec mul_add(Int64::vec& A, Int64::vec&& B, Int64::vec& C) { return  _mm256_castpd_si256(_mm256_fmadd_pd(_mm256_castsi256_pd(A.data()), _mm256_castsi256_pd(B.data()), _mm256_castsi256_pd(C.data()))); }
		inline vec mul_add(Int64::vec& A, Int64::vec&& B, Int64::vec&& C) { return  _mm256_castpd_si256(_mm256_fmadd_pd(_mm256_castsi256_pd(A.data()), _mm256_castsi256_pd(B.data()), _mm256_castsi256_pd(C.data()))); }
		inline vec mul_add(Int64::vec&& A, Int64::vec& B, Int64::vec& C) { return  _mm256_castpd_si256(_mm256_fmadd_pd(_mm256_castsi256_pd(A.data()), _mm256_castsi256_pd(B.data()), _mm256_castsi256_pd(C.data()))); }
		inline vec mul_add(Int64::vec&& A, Int64::vec& B, Int64::vec&& C) { return  _mm256_castpd_si256(_mm256_fmadd_pd(_mm256_castsi256_pd(A.data()), _mm256_castsi256_pd(B.data()), _mm256_castsi256_pd(C.data()))); }
		inline vec mul_add(Int64::vec&& A, Int64::vec&& B, Int64::vec& C) { return  _mm256_castpd_si256(_mm256_fmadd_pd(_mm256_castsi256_pd(A.data()), _mm256_castsi256_pd(B.data()), _mm256_castsi256_pd(C.data()))); }
		inline vec mul_add(Int64::vec&& A, Int64::vec&& B, Int64::vec&& C) { return  _mm256_castpd_si256(_mm256_fmadd_pd(_mm256_castsi256_pd(A.data()), _mm256_castsi256_pd(B.data()), _mm256_castsi256_pd(C.data()))); }


		// A * B - C
		inline vec mul_sub(Int64::vec& A, Int64::vec& B, Int64::vec& C) { return  _mm256_castpd_si256(_mm256_fmsub_pd(_mm256_castsi256_pd(A.data()), _mm256_castsi256_pd(B.data()), _mm256_castsi256_pd(C.data()))); }
		inline vec mul_sub(Int64::vec& A, Int64::vec& B, Int64::vec&& C) { return  _mm256_castpd_si256(_mm256_fmsub_pd(_mm256_castsi256_pd(A.data()), _mm256_castsi256_pd(B.data()), _mm256_castsi256_pd(C.data()))); }
		inline vec mul_sub(Int64::vec& A, Int64::vec&& B, Int64::vec& C) { return  _mm256_castpd_si256(_mm256_fmsub_pd(_mm256_castsi256_pd(A.data()), _mm256_castsi256_pd(B.data()), _mm256_castsi256_pd(C.data()))); }
		inline vec mul_sub(Int64::vec& A, Int64::vec&& B, Int64::vec&& C) { return  _mm256_castpd_si256(_mm256_fmsub_pd(_mm256_castsi256_pd(A.data()), _mm256_castsi256_pd(B.data()), _mm256_castsi256_pd(C.data()))); }
		inline vec mul_sub(Int64::vec&& A, Int64::vec& B, Int64::vec& C) { return  _mm256_castpd_si256(_mm256_fmsub_pd(_mm256_castsi256_pd(A.data()), _mm256_castsi256_pd(B.data()), _mm256_castsi256_pd(C.data()))); }
		inline vec mul_sub(Int64::vec&& A, Int64::vec& B, Int64::vec&& C) { return  _mm256_castpd_si256(_mm256_fmsub_pd(_mm256_castsi256_pd(A.data()), _mm256_castsi256_pd(B.data()), _mm256_castsi256_pd(C.data()))); }
		inline vec mul_sub(Int64::vec&& A, Int64::vec&& B, Int64::vec& C) { return  _mm256_castpd_si256(_mm256_fmsub_pd(_mm256_castsi256_pd(A.data()), _mm256_castsi256_pd(B.data()), _mm256_castsi256_pd(C.data()))); }
		inline vec mul_sub(Int64::vec&& A, Int64::vec&& B, Int64::vec&& C) { return  _mm256_castpd_si256(_mm256_fmsub_pd(_mm256_castsi256_pd(A.data()), _mm256_castsi256_pd(B.data()), _mm256_castsi256_pd(C.data()))); }
	};
};
#endif // ! Int64_Class