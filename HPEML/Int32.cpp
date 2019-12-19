#include "Header.h"

inline Int32::Int32() : _num(0) {}
inline Int32::Int32(int& num) : _num(num) {}
inline Int32::Int32(int&& num) : _num(num) {}
inline Int32::Int32(Int32& F) : _num(F._num) {}
inline Int32::Int32(Int32&& F) : _num(std::move(F._num)) {}

inline Int32& Int32::operator=(Int32& F)
{
	if (this != &F)
		_num = F._num;
	return *this;
}

inline Int32& Int32::operator=(Int32&& F)
{
	if (this != &F)
		_num = std::move(F._num);
	return *this;
}

inline Int32& Int32::operator=(int& num)
{
	if (_num != num)
		_num = num;
	return *this;
}

inline Int32& Int32::operator=(int&& num)
{
	if (_num != num)
		_num = std::move(num);
	return *this;
}

inline int Int32::get_data() { return _num; }
inline int* Int32::get_adress() { return &_num; }

inline Int32::vec::vec() :_v(_mm256_setzero_si256()) {}
inline Int32::vec::vec(vectypeint& v) : _v(v) {}
inline Int32::vec::vec(vectypeint&& v) : _v(std::move(v)) {}
inline Int32::vec::vec(vec& V) : _v(V._v) {}
inline Int32::vec::vec(vec&& V) : _v(std::move(V._v)) {}

//how to know the legnth of p
inline Int32::vec::vec(int* p)
{
}

inline Int32::vec& Int32::vec::operator=(Int32::vec& V)
{
	if (_v != V._v)
		_v = _mm256_load_si256(V.get_adress);
	return *this;
}

inline Int32::vec& Int32::vec::operator=(Int32::vec&& V)
{
	if (_v != V._v)
		_v = _mm256_load_si256(V.get_adress);
	return *this;
}

inline  bool operator==(vectypeint& a, vectypeint& b)
{
	vectypeint pcmp = _mm256_cmpeq_epi32(a, b);  // epi8 is fine too
	unsigned bitmask = _mm256_movemask_epi8(pcmp);
	return (bitmask == 0xffffffffU);
}

inline  bool operator!= (vectypeint& a, vectypeint& b) { return !(a == b); }


inline vectypeint Int32::vec::get_data() { return _v; }
inline vectypeint* Int32::vec::get_adress() { return &_v; }

inline void Int32::vec::set_data(vectypeint v) { _v = v; }

inline Int32::vec operator+(Int32::vec& A, Int32::vec& B) { return _mm256_add_epi32(A._v, B._v); }
inline Int32::vec operator+(Int32::vec& A, Int32::vec&& B) { return _mm256_add_epi32(A._v, B._v); }
inline Int32::vec operator+(Int32::vec&& A, Int32::vec& B) { return _mm256_add_epi32(A._v, B._v); }
inline Int32::vec operator+(Int32::vec&& A, Int32::vec&& B) { return _mm256_add_epi32(A._v, B._v); }

inline Int32::vec operator-(Int32::vec& A, Int32::vec& B) { return _mm256_sub_epi32(A._v, B._v); }
inline Int32::vec operator-(Int32::vec& A, Int32::vec&& B) { return _mm256_sub_epi32(A._v, B._v); }
inline Int32::vec operator-(Int32::vec&& A, Int32::vec& B) { return _mm256_sub_epi32(A._v, B._v); }
inline Int32::vec operator-(Int32::vec&& A, Int32::vec&& B) { return _mm256_sub_epi32(A._v, B._v); }

inline Int32::vec operator*(Int32::vec& A, Int32::vec& B) { return _mm256_mullo_epi32(A._v, B._v); }
inline Int32::vec operator*(Int32::vec& A, Int32::vec&& B) { return _mm256_mullo_epi32(A._v, B._v); }
inline Int32::vec operator*(Int32::vec&& A, Int32::vec& B) { return _mm256_mullo_epi32(A._v, B._v); }
inline Int32::vec operator*(Int32::vec&& A, Int32::vec&& B) { return _mm256_mullo_epi32(A._v, B._v); }



inline Int32::vec mul_add(Int32::vec& A, Int32::vec& B, Int32::vec& C) { return _mm256_castps_si256(_mm256_fmadd_ps(_mm256_castsi256_ps(A._v), _mm256_castsi256_ps(B._v), _mm256_castsi256_ps(C._v))); }
inline Int32::vec mul_sub(Int32::vec& A, Int32::vec& B, Int32::vec& C) { return _mm256_castps_si256(_mm256_fmsub_ps(_mm256_castsi256_ps(A._v), _mm256_castsi256_ps(B._v), _mm256_castsi256_ps(C._v))); }


Int32::vec