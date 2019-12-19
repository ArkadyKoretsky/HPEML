#include "Header.h"

inline Int64::Int64() : _num(0) {}
inline Int64::Int64(int& num) : _num(num) {}
inline Int64::Int64(int&& num) : _num(num) {}
inline Int64::Int64(Int64& F) : _num(F._num) {}
inline Int64::Int64(Int64&& F) : _num(std::move(F._num)) {}

inline Int64& Int64::operator=(Int64& F)
{
	if (this != &F)
		_num = F._num;
	return *this;
}

inline Int64& Int64::operator=(Int64&& F)
{
	if (this != &F)
		_num = std::move(F._num);
	return *this;
}

inline Int64& Int64::operator=(int& num)
{
	if (_num != num)
		_num = num;
	return *this;
}

inline Int64& Int64::operator=(int&& num)
{
	if (_num != num)
		_num = std::move(num);
	return *this;
}

inline int Int64::get_data() { return _num; }
inline int* Int64::get_adress() { return &_num; }

inline Int64::vec::vec() :_v(_mm256_setzero_si256()) {}
inline Int64::vec::vec(vectypeint& v) : _v(v) {}
inline Int64::vec::vec(vectypeint&& v) : _v(std::move(v)) {}
inline Int64::vec::vec(vec& V) : _v(V._v) {}
inline Int64::vec::vec(vec&& V) : _v(std::move(V._v)) {}

//how to know the legnth of p
inline Int64::vec::vec(int* p)
{
}

inline Int64::vec& Int64::vec::operator=(Int64::vec& V)
{
	if (_v != V._v)
		_v = _mm256_load_si256(V.get_adress);
	return *this;
}

inline Int64::vec& Int64::vec::operator=(Int64::vec&& V)
{
	if (_v != V._v)
		_v = _mm256_load_si256(V.get_adress);
	return *this;
}

inline  bool operator==(vectypeint& a, vectypeint& b)
{
	vectypeint pcmp = _mm256_cmpeq_epi64(a, b);  // epi8 is fine too
	unsigned bitmask = _mm256_movemask_epi8(pcmp);
	return (bitmask == 0xffffffffU);
}

inline  bool operator!= (vectypeint& a, vectypeint& b) { return !(a == b); }


inline vectypeint Int64::vec::get_data() { return _v; }
inline vectypeint* Int64::vec::get_adress() { return &_v; }

inline void Int64::vec::set_data(vectypeint v) { _v = v; }

inline Int64::vec operator+(Int64::vec& A, Int64::vec& B) { return _mm256_add_epi64(A._v, B._v); }
inline Int64::vec operator+(Int64::vec& A, Int64::vec&& B) { return _mm256_add_epi64(A._v, B._v); }
inline Int64::vec operator+(Int64::vec&& A, Int64::vec& B) { return _mm256_add_epi64(A._v, B._v); }
inline Int64::vec operator+(Int64::vec&& A, Int64::vec&& B) { return _mm256_add_epi64(A._v, B._v); }

inline Int64::vec operator-(Int64::vec& A, Int64::vec& B) { return _mm256_sub_epi64(A._v, B._v); }
inline Int64::vec operator-(Int64::vec& A, Int64::vec&& B) { return _mm256_sub_epi64(A._v, B._v); }
inline Int64::vec operator-(Int64::vec&& A, Int64::vec& B) { return _mm256_sub_epi64(A._v, B._v); }
inline Int64::vec operator-(Int64::vec&& A, Int64::vec&& B) { return _mm256_sub_epi64(A._v, B._v); }

inline Int64::vec operator*(Int64::vec& A, Int64::vec& B) { return _mm256_mullo_epi64(A._v, B._v); }
inline Int64::vec operator*(Int64::vec& A, Int64::vec&& B) { return _mm256_mullo_epi64(A._v, B._v); }
inline Int64::vec operator*(Int64::vec&& A, Int64::vec& B) { return _mm256_mullo_epi64(A._v, B._v); }
inline Int64::vec operator*(Int64::vec&& A, Int64::vec&& B) { return _mm256_mullo_epi64(A._v, B._v); }



inline Int64::vec mul_add(Int64::vec& A, Int64::vec& B, Int64::vec& C) { return _mm256_castpd_si256(_mm256_fmadd_pd(_mm256_castsi256_pd(A._v), _mm256_castsi256_pd(B._v), _mm256_castsi256_pd(C._v))); }
inline Int64::vec mul_sub(Int64::vec& A, Int64::vec& B, Int64::vec& C) { return _mm256_castpd_si256(_mm256_fmsub_pd(_mm256_castsi256_pd(A._v), _mm256_castsi256_pd(B._v), _mm256_castsi256_pd(C._v))); }