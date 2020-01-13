#include "HPEML.h"
#include <ctime>
#include "t_timer.h"

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
	size_t row1 = 4091, col = 4079, row2 = 4091;
	Matrix<Float> A(row1, col, "rand"), B(col, row2, "rand");
	double timer = 0;
	t_timer t;
	for (size_t i = 0; i < 10; ++i)
	{
		t.start();
		A * B;
		t.stop();
		timer += t.get_time();
	}

	cout << timer / 10;

	return 0;
}