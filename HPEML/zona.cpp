#include <iostream>
#include <immintrin.h>

using namespace std;

class test
{
public:
	float num;
	
	test(): num(0) {}
	test(float _num) : num(_num) {}

	test& operator = (__m256 _register) { _mm256_storeu_ps(&num, _register); return *this; }
	//void method(__m256 _register)
	//{
	//	_mm256_storeu_ps(&num, _register);
	//}
};



int main()
{
	float numbers[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };
	__m256  _register = _mm256_loadu_ps(numbers);
	test A[8];

	A[0] =_register;
	
	for (size_t i = 0; i < 8; ++i)
		cout << A[i].num << " ";
	cout << endl;

	return 0;
}