#include "Header.h"

inline Double::Double() :_num(0) {}
inline Double::Double(double& num) : _num(num) {}
inline Double::Double(double&& num) : _num(num) {}
inline Double::Double(Double& F) : _num(F._num) {}
inline Double::Double(Double&& F) : _num(std::move(F._num)) {}

inline Double& Double::operator=(Double& F)
{
	if (this != &F)
		_num = F._num;
	return *this;
}

inline Double& Double::operator=(Double&& F)
{
	if (this != &F)
		_num = std::move(F._num);
	return *this;
}

inline Double& Double::operator=(double& num)
{
	if (_num != num)
		_num = num;
	return *this;
}

inline Double& Double::operator=(double&& num)
{
	if (_num != num)
		_num = std::move(num);
	return *this;
}

inline double Double::get_data() { return _num; }
inline double* Double::get_adress() { return &_num; }
inline Double::vec::vec() :_v(_mm256_setzero_pd()) {}
inline Double::vec::vec(vectypedouble& v) : _v(v) {}
inline Double::vec::vec(vectypedouble&& v) : _v(std::move(v)) {}
inline Double::vec::vec(vec& V) : _v(V._v) {}
inline Double::vec::vec(vec&& V) : _v(std::move(V._v)) {}

//how to know the legnth of p
inline Double::vec::vec(double* p)
{
}

inline Double::vec& Double::vec::operator=(Double::vec& V)
{
	if (_v != V._v)
		_v = _mm256_load_pd(V.get_adress);
	return *this;
}

inline Double::vec& Double::vec::operator=(Double::vec&& V)
{
	if (_v != V._v)
		_v = _mm256_load_pd(V.get_adress);
	return *this;
}

inline  bool operator==(vectypedouble& a, vectypedouble& b)
{
	vectypedouble pcmp = _mm256_cmp_pd(a, b, _CMP_EQ_OS);
	unsigned bitmask = _mm256_movemask_pd(pcmp);
	return (bitmask == 0xffffffffU);
}

inline  bool operator!= (vectypedouble& a, vectypedouble& b) { return !(a == b); }


inline vectypedouble Double::vec::get_data() { return _v; }
inline vectypedouble* Double::vec::get_adress() { return &_v; }

inline void Double::vec::set_data(vectypedouble v) { _v = v; }

inline Double::vec operator+(Double::vec& A, Double::vec& B) { return _mm256_add_pd(A._v, B._v); }
inline Double::vec operator+(Double::vec& A, Double::vec&& B) { return _mm256_add_pd(A._v, B._v); }
inline Double::vec operator+(Double::vec&& A, Double::vec& B) { return _mm256_add_pd(A._v, B._v); }
inline Double::vec operator+(Double::vec&& A, Double::vec&& B) { return _mm256_add_pd(A._v, B._v); }

inline Double::vec operator-(Double::vec& A, Double::vec& B) { return _mm256_sub_pd(A._v, B._v); }
inline Double::vec operator-(Double::vec& A, Double::vec&& B) { return _mm256_sub_pd(A._v, B._v); }
inline Double::vec operator-(Double::vec&& A, Double::vec& B) { return _mm256_sub_pd(A._v, B._v); }
inline Double::vec operator-(Double::vec&& A, Double::vec&& B) { return _mm256_sub_pd(A._v, B._v); }

inline Double::vec operator*(Double::vec& A, Double::vec& B) { return _mm256_mul_pd(A._v, B._v); }
inline Double::vec operator*(Double::vec& A, Double::vec&& B) { return _mm256_mul_pd(A._v, B._v); }
inline Double::vec operator*(Double::vec&& A, Double::vec& B) { return _mm256_mul_pd(A._v, B._v); }
inline Double::vec operator*(Double::vec&& A, Double::vec&& B) { return _mm256_mul_pd(A._v, B._v); }

inline Double::vec operator/(Double::vec& A, Double::vec& B) { return _mm256_div_pd(A._v, B._v); }
inline Double::vec operator/(Double::vec& A, Double::vec&& B) { return _mm256_div_pd(A._v, B._v); }
inline Double::vec operator/(Double::vec&& A, Double::vec& B) { return _mm256_div_pd(A._v, B._v); }
inline Double::vec operator/(Double::vec&& A, Double::vec&& B) { return _mm256_div_pd(A._v, B._v); }




inline Double::vec mul_add(Double::vec& A, Double::vec& B, Double::vec& C) { return _mm256_fmadd_pd((A._v), (B._v), (C._v)); }
inline Double::vec mul_sub(Double::vec& A, Double::vec& B, Double::vec& C) { return _mm256_fmsub_pd((A._v), (B._v), (C._v)); }