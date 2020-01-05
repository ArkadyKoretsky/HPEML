#include "HPEML.h"
#include <ctime>

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
	size_t row1 = 14, col = 10, row2 = 11;
	Float F1(8), F2(2);
	Float::vec V1(F1), V2(F2);
	Matrix<Float> A(row1, col, F1), B(col, row2, F2);
	Matrix<Float> C = A.trans(true);
	cout << A << endl << C;
	//clock_t t = clock();
	//for (size_t i = 0; i < 10; ++i)
	//	A *= B;
	//t = clock() - t;
	//t /= 10;
	//cout << (float)t / CLOCKS_PER_SEC;

	return 0;
}