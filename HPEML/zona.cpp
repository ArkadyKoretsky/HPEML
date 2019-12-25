#include <iostream>
#include <immintrin.h>

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
	test *A = new test[8], *B = new test[8];
	float numbers[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };

	for (size_t i = 0; i < 8; ++i)
		A[i].num = numbers[i];

	__m256  _register = _mm256_loadu_ps(A->address());

	B[0] = _register;

	for (size_t i = 0; i < 8; ++i)
		cout << B[i].num << " ";
	cout << endl;

	return 0;

}