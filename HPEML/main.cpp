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
	size_t row = 5, col = 7;
	Float F1(1), F2(1);
	Matrix<Float> A(row, col, F1), B(col, row, F2);
	//Matrix<Float> arr[4] = { A, B, C, D };
	//for (size_t i = 0; i < 4; ++i)
	//	cout << arr[i] << endl;
	A.padBlockSize();
	B.padBlockSize();
	Matrix<Float> C;
	C.naiveMult(A, B);
	C.removePadding(row, row);
	cout << C;

	return 0;
}