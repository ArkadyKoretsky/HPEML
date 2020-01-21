#pragma once
#ifndef Int_Class
#define Int_Class

#include <immintrin.h>
#include <iostream>

class Int // Type of scalar field
{
	int _num;

public:
	class vec;

	// constructors
	inline Int() : _num(0) {}
	inline Int(int& num) : _num(num) {}
	inline Int(int&& num) : _num(num) {}
	inline Int(Int& F) : _num(F._num) {}
	inline Int(Int&& F) noexcept : _num(std::move(F._num)) {}

	/* Assignment Operators - START */
	inline Int& operator=(Int& F)
	{
		if (this != &F)
			_num = F._num;
		return *this;
	}

	inline Int& operator=(Int&& F) noexcept
	{
		if (this != &F)
			_num = std::move(F._num);
		return *this;
	}

	inline Int& operator=(int& num)
	{
		if (_num != num)
			_num = num;
		return *this;
	}

	inline Int& operator=(int&& num)
	{
		if (_num != num)
			_num = std::move(num);
		return *this;
	}

	inline Int& operator = (vec& V)
	{
		_mm512_store_epi32(&_num, V.data());
		return *this;
	}

	inline Int& operator = (vec&& V)
	{
		_mm512_store_epi32(&_num, V.data());
		return *this;
	}
	/* Assignment Operators - END */

	// Naive Sum
	inline friend Int operator + (Int& A, Int& B) { return Int(A.data() + B.data()); }
	inline friend Int operator + (Int& A, Int&& B) { return Int(A.data() + B.data()); }
	inline friend Int operator + (Int&& A, Int& B) { return Int(A.data() + B.data()); }
	inline friend Int operator + (Int&& A, Int&& B) { return Int(A.data() + B.data()); }

	// Naive Sub
	inline friend Int operator - (Int& A, Int& B) { return Int(A.data() - B.data()); }
	inline friend Int operator - (Int& A, Int&& B) { return Int(A.data() - B.data()); }
	inline friend Int operator - (Int&& A, Int& B) { return Int(A.data() - B.data()); }
	inline friend Int operator - (Int&& A, Int&& B) { return Int(A.data() - B.data()); }

	// Naive Multiplication
	inline friend Int operator * (Int& A, Int& B) { return Int(A.data() * B.data()); }
	inline friend Int operator * (Int& A, Int&& B) { return Int(A.data() * B.data()); }
	inline friend Int operator * (Int&& A, Int& B) { return Int(A.data() * B.data()); }
	inline friend Int operator * (Int&& A, Int&& B) { return Int(A.data() * B.data()); }

	// Naive Division
	inline friend Int operator / (Int& A, Int& B) { return Int(A.data() / B.data()); }
	inline friend Int operator / (Int& A, Int&& B) { return Int(A.data() / B.data()); }
	inline friend Int operator / (Int&& A, Int& B) { return Int(A.data() / B.data()); }
	inline friend Int operator / (Int&& A, Int&& B) { return Int(A.data() / B.data()); }

	// Getters
	inline int data() { return _num; }
	inline int* adress() { return &_num; }

	/* Double class - END */

	/* vec class - START */

	// output operator (most for debug purpose)
	inline friend std::ostream& operator << (std::ostream& out, Int& F)
	{
		out << F.data();
		return out;
	}

	inline friend std::ostream& operator << (std::ostream& out, Int&& F)
	{
		out << F.data();
		return out;
	}

	class vec // Type of AVX vector
	{
		__m512i _v;

	public:
		// constructors
		inline vec() :_v(_mm512_setzero_epi32()) {}
		inline vec(__m512i& v) : _v(v) {}
		inline vec(__m512i&& v) : _v(std::move(v)) {}
		inline vec(int* p) : _v(_mm512_loadu_epi32(p)) {}
		inline vec(Int* p) : _v(_mm512_loadu_epi32(p->adress())) {}
		//inline vec(Int& F) : _v(_mm512_broadcastd_epi32(F.data())) {} - no suitable broadcast functions to integers  
		//inline vec(Int&& F) : _v(_mm512_broadcastd_epi32(F.data())) {} - no suitable broadcast functions to integers
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
			_v = _mm512_loadu_epi32(p);
			return *this;
		}

		inline vec& operator = (Int* p)
		{
			_v = _mm512_loadu_epi32(p->adress());
			return *this;
		}

		inline vec& operator = (Int& F)
		{
			_v = _mm512_loadu_epi32(F.adress());
			return *this;
		}

		inline vec& operator = (Int&& F)
		{
			_v = _mm512_loadu_epi32(F.adress());
			return *this;
		}

		// geters and seters
		inline __m512i data() { return _v; }
		inline __m512i* adress() { return &_v; }

		// sum operator
		inline friend vec operator + (Int::vec& A, Int::vec& B) { return _mm512_add_epi32(A.data(), B.data()); }
		inline friend vec operator + (Int::vec& A, Int::vec&& B) { return _mm512_add_epi32(A.data(), B.data()); }
		inline friend vec operator + (Int::vec&& A, Int::vec& B) { return _mm512_add_epi32(A.data(), B.data()); }
		inline friend vec operator + (Int::vec&& A, Int::vec&& B) { return _mm512_add_epi32(A.data(), B.data()); }

		// sub operator
		inline friend vec operator - (Int::vec& A, Int::vec& B) { return _mm512_sub_epi32(A.data(), B.data()); }
		inline friend vec operator - (Int::vec& A, Int::vec&& B) { return _mm512_sub_epi32(A.data(), B.data()); }
		inline friend vec operator - (Int::vec&& A, Int::vec& B) { return _mm512_sub_epi32(A.data(), B.data()); }
		inline friend vec operator - (Int::vec&& A, Int::vec&& B) { return _mm512_sub_epi32(A.data(), B.data()); }

		// multiplication operator
		inline friend vec operator * (Int::vec& A, Int::vec& B) { return _mm512_mul_epi32(A.data(), B.data()); }
		inline friend vec operator * (Int::vec& A, Int::vec&& B) { return _mm512_mul_epi32(A.data(), B.data()); }
		inline friend vec operator * (Int::vec&& A, Int::vec& B) { return _mm512_mul_epi32(A.data(), B.data()); }
		inline friend vec operator * (Int::vec&& A, Int::vec&& B) { return _mm512_mul_epi32(A.data(), B.data()); }


		// division operator
		inline friend vec operator / (Int::vec& A, Int::vec& B) { return _mm512_div_epi32(A.data(), B.data()); }
		inline friend vec operator / (Int::vec& A, Int::vec&& B) { return _mm512_div_epi32(A.data(), B.data()); }
		inline friend vec operator / (Int::vec&& A, Int::vec& B) { return _mm512_div_epi32(A.data(), B.data()); }
		inline friend vec operator / (Int::vec&& A, Int::vec&& B) { return _mm512_div_epi32(A.data(), B.data()); }


		// A * B + C
		inline vec mul_add(Int::vec& A, Int::vec& B, Int::vec& C) { return  _mm512_madd52lo_epu64(A.data(), B.data(), C.data()); }
		inline vec mul_add(Int::vec& A, Int::vec& B, Int::vec&& C) { return  _mm512_madd52lo_epu64(A.data(), B.data(), C.data());}
		inline vec mul_add(Int::vec& A, Int::vec&& B, Int::vec& C) { return  _mm512_madd52lo_epu64(A.data(), B.data(), C.data()); }
		inline vec mul_add(Int::vec& A, Int::vec&& B, Int::vec&& C) { return  _mm512_madd52lo_epu64(A.data(), B.data(), C.data());}
		inline vec mul_add(Int::vec&& A, Int::vec& B, Int::vec& C) { return  _mm512_madd52lo_epu64(A.data(), B.data(), C.data());}
		inline vec mul_add(Int::vec&& A, Int::vec& B, Int::vec&& C) { return  _mm512_madd52lo_epu64(A.data(), B.data(), C.data());}
		inline vec mul_add(Int::vec&& A, Int::vec&& B, Int::vec& C) { return  _mm512_madd52lo_epu64(A.data(), B.data(), C.data());}
		inline vec mul_add(Int::vec&& A, Int::vec&& B, Int::vec&& C) { return  _mm512_madd52lo_epu64(A.data(), B.data(), C.data());}


		// A * B - C - No Such Operation with Integers
		/*inline vec mul_add(Int::vec& A, Int::vec& B, Int::vec& C) { return  _mm512_madd52lo_epu64(A.data(), B.data(), C.data()); }
		inline vec mul_add(Int::vec& A, Int::vec& B, Int::vec&& C) { return  _mm512_madd52lo_epu64(A.data(), B.data(), C.data()); }
		inline vec mul_add(Int::vec& A, Int::vec&& B, Int::vec& C) { return  _mm512_madd52lo_epu64(A.data(), B.data(), C.data()); }
		inline vec mul_add(Int::vec& A, Int::vec&& B, Int::vec&& C) { return  _mm512_madd52lo_epu64(A.data(), B.data(), C.data()); }
		inline vec mul_add(Int::vec&& A, Int::vec& B, Int::vec& C) { return  _mm512_madd52lo_epu64(A.data(), B.data(), C.data()); }
		inline vec mul_add(Int::vec&& A, Int::vec& B, Int::vec&& C) { return  _mm512_madd52lo_epu64(A.data(), B.data(), C.data()); }
		inline vec mul_add(Int::vec&& A, Int::vec&& B, Int::vec& C) { return  _mm512_madd52lo_epu64(A.data(), B.data(), C.data()); }
		inline vec mul_add(Int::vec&& A, Int::vec&& B, Int::vec&& C) { return  _mm512_madd52lo_epu64(A.data(), B.data(), C.data()); }*/
	};
};
#endif // ! INT_Class