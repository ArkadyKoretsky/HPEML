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
	size_t row1 = 5, col = 7, row2 = 11;
	Float F1(1), F2(1);
	Float::vec V1(F1), V2(F2);
	Matrix<Float> A(row1, col, F1), B(col, row2, F2);
	cout << A * B;
	cout << endl;
	Float F3(3);
	Matrix<Float> C(row1, col, F3), D(row1, col, F3);
	cout << C.dot_product(C, D);

	return 0;
}