#include "HPEML.h"

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
	size_t row = 8, col = 8;
	Float F1(5), F2(6);
	Matrix<Float> A(row, col, F1), B(row, col, F2), C(row, col, F2), D(row, col, F1);
	//Matrix<Float> arr[4] = { A, B, C, D };
	//for (size_t i = 0; i < 4; ++i)
	//	cout << arr[i] << endl;
	Matrix<Float> mat=A;
	cout << mat;

	return 0;
}