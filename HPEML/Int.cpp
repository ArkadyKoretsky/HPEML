#include "Header.h"

inline Int::Int() : _num(0) {}
inline Int::Int(int& num) : _num(num) {}
inline Int::Int(int&& num) : _num(num) {}
inline Int::Int(Int& F) : _num(F._num) {}
inline Int::Int(Int&& F) : _num(F._num) {}

inline Int& Int::operator=(Int& F)
{
	if (this != &F)
		_num = F._num;
	return *this;
}

inline Int& Int::operator=(Int&& F)
{
	if (this != &F)
		std::move(F);
	return *this;
}

inline Int& Int::operator=(int& num)
{
	if (_num != num)
		_num = num;
	return *this;
}

inline Int& Int::operator=(int&& num)
{
	if (_num != num)
		std::move(num);
	return *this;
}


inline Int::vec::vec() :_v(_mm256_setzero_si256()) {}
inline Int::vec::vec(vectypeint& v) : _v(v) {}
inline Int::vec::vec(vectypeint&& v) : _v(std::move(v)) {}


inline vectypeint Int::vec::get_data() { return _v; }
inline vectypeint* Int::vec::get_adress() { return &_v; }

inline void Int::vec::set_data(vectypeint v) { _v = v; }

inline Int::vec operator+(Int::vec& A, Int::vec& B) { return _mm256_add_epi32(A._v, B._v); }
inline Int::vec operator+(Int::vec& A, Int::vec&& B) { return _mm256_add_epi32(A._v, B._v); }
inline Int::vec operator+(Int::vec&& A, Int::vec& B) { return _mm256_add_epi32(A._v, B._v); }
inline Int::vec operator+(Int::vec&& A, Int::vec&& B) { return _mm256_add_epi32(A._v, B._v); }

inline Int::vec operator-(Int::vec& A, Int::vec& B) { return _mm256_sub_epi32(A._v, B._v); }
inline Int::vec operator-(Int::vec& A, Int::vec&& B) { return _mm256_sub_epi32(A._v, B._v); }
inline Int::vec operator-(Int::vec&& A, Int::vec& B) { return _mm256_sub_epi32(A._v, B._v); }
inline Int::vec operator-(Int::vec&& A, Int::vec&& B) { return _mm256_sub_epi32(A._v, B._v); }

inline Int::vec operator*(Int::vec& A, Int::vec& B) { return _mm256_sub_epi32(A._v, B._v); }
inline Int::vec operator*(Int::vec& A, Int::vec&& B) { return _mm256_sub_epi32(A._v, B._v); }
inline Int::vec operator*(Int::vec&& A, Int::vec& B) { return _mm256_sub_epi32(A._v, B._v); }
inline Int::vec operator*(Int::vec&& A, Int::vec&& B) { return _mm256_sub_epi32(A._v, B._v); }

inline Int::vec mul_add(Int::vec& A, Int::vec& B, Int::vec& C)
{
	return _mm256_fmadd_ps(A, B, C);
}


