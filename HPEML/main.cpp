#include "HPEML.h"
#include "t_timer.h"
#include "Initialization.h"

//#include <ctime>

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


std::pair<int, double>  Initialization::times[5];

int main()
{
	try
	{
		//cout << "start" << endl;
		//size_t row1 = 8091, col = 8101, row2 = 8091;
		//Float F1(1), F2(1);
		//Float::vec V1(F1), V2(F2);
		////	Matrix<Float> A(row1, col, F1), B(col, row2, F1);
		//Matrix<Float> A(row1, col, F1), B(8012, row2, F1);
		////Matrix<Float> C = A.trans(true);
		//double t = 0;
		//t_timer tt;
		//for (size_t k = 0; k < 10; k++)
		//{
		//	tt.start();		//start timer
		//	A *= B;
		//	tt.stop();	//stop timer
		//	t += tt.get_time();
		//}
		//double time = t / 10;
		//cout << time << endl;
		//cout << A << endl << B;
		//clock_t t = clock();
		//for (size_t i = 0; i < 10; ++i)
		//	A *= B;
		//t = clock() - t;
		//t /= 10;
		//cout << (float)t / CLOCKS_PER_SEC;
		//cout << "Init Start" << endl;
		//Initialization::Init();
		//cout << "Init Done" << endl;
		//cout << "readData Start" << endl;
		//Initialization::readData();
		//cout << "readData Done" << endl;

		initializer_list< initializer_list<int>> l = { {1, 2, 3}, {4, 5, 6} };
		cout << l.begin()->begin();

		return 0;
	}
	catch (const char* caught)
	{
		std::cout << "Got " << caught << std::endl;
	}
}