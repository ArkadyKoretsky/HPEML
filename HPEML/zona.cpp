//#include <iostream>
//#include <immintrin.h>
#include "Float.h"

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
	Float F1(5), F2(10);
	Float::vec V1(F1), V2(F2);
	Float::vec V3 = V1 + V2;
	cout << F1 + F2;
	//Matrix<Float> A(row, col, Float(1)), B(row, col, Float()), C(row, col);

	//C = A + B;

	//cout << C;

	return 0;

}