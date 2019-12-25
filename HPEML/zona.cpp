//#include <iostream>
//#include <immintrin.h>
#include "Header.h"

using namespace std;

class test
{
public:
	float num;

	test() : num(0) {}
	test(float _num) : num(_num) {}

	test& operator = (__m256 _register) { _mm256_storeu_ps(&num, _register); return *this; }
	//void method(__m256 _register)
	//{
	//	_mm256_storeu_ps(&num, _register);
	//}

	float* address() { return &num; }
};



int main()
{
	size_t row = 31, col = 35;
	Float F;
	cout << F.data();
	//Matrix<Float> A(row, col, Float(1)), B(row, col, Float()), C(row, col);

	//C = A + B;

	//cout << C;

	return 0;

}