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
	size_t row1 = 4, col = 4, row2 = 11;
	Float F1(1), F2(1);
	Float::vec V1(F1), V2(F2);
	vector<size_t> row_list;
	row_list.push_back(1);
	row_list.push_back(2);
	Float matrix[16] = { Float(1), Float(2), Float(3), Float(4),
						 Float(5), Float(6), Float(7), Float(8),
						 Float(9), Float(10), Float(11), Float(12),
						 Float(13), Float(14), Float(15), Float(16)
	};
	Matrix<Float> A(row1, col, "one"), B(col, row2, F2);
	vector<Float> vec(5);
	for (size_t i = 0; i < 5; ++i)
		cout << vec.at(i) << " ";
	vector<vector<Float>> vecs(5);
	for (size_t i = 0; i < 5; ++i)
		vecs.push_back(vec);
	Matrix<Float> C(vecs);
	//Matrix<Float> C = A.conj(true);
	cout << C;

	for (size_t i = 0; i < 5; ++i)
	{
		for (size_t j = 0; j < 5; ++j)
			cout << vecs.at(i).at(j) << " ";
		cout << endl;
	}

	//clock_t t = clock();
	//for (size_t i = 0; i < 10; ++i)
	//A *= B;
	//cout << A;
	//t = clock() - t;
	//t /= 10;
	//cout << (float)t / CLOCKS_PER_SEC;

	return 0;
}