#ifndef HPEML
#define HPEML // stands for: High Performance Extendable Math Library

#define VECSIZE 8
#define I_BLOCKSIZE 32
#define J_BLOCKSIZE 32
#define K_BLOCKSIZE 32
#define UNROLL_1 4 // UNROLL_1 * VECSIZE <= min{I_BLOCKSIZE, J_BLOCKSIZE, K_BLOCKSIZE}
#define UNROLL_2 2 //UNROLL_2 * VECSIZE <= min{I_BLOCKSIZE, J_BLOCKSIZE, K_BLOCKSIZE}

#include<iostream>
#include<vector>
#include "Float.h"
using namespace std;


/* class Memory_Block - START */
template <typename scalar, typename T> // CRTP (Curiously Recurring Template Pattern)
class Memory_Block // Base type of Matrix
{
protected:
	scalar* _mat;
	size_t _row;
	size_t _col;

public:
	// constructors
	Memory_Block() : _row(0), _col(0), _mat(nullptr) {}
	Memory_Block(size_t row, size_t col) : _row(row), _col(col), _mat(new scalar[row * col]) {}
	Memory_Block(size_t row, size_t col, scalar val) : _row(row), _col(col), _mat(new scalar[row * col])
	{
		size_t i, sizeOfMatrix = row * col, vecsize = VECSIZE;
		if (sizeOfMatrix >= vecsize)
		{
			for (i = 0; i < sizeOfMatrix - vecsize; i += vecsize)
				_mat[i] = scalar::vec(val);

			for (; i < sizeOfMatrix; ++i)
				_mat[i] = val;
		}

		else
		{
			for (i = 0; i < sizeOfMatrix; ++i)
				_mat[i] = val;
		}
	}

	Memory_Block(size_t row, size_t col, scalar* mat) : _row(row), _col(col), _mat(new scalar[row * col])
	{
		size_t i, sizeOfMatrix = row * col, vecsize = VECSIZE;
		if (sizeOfMatrix >= vecsize)
		{
			for (i = 0; i < sizeOfMatrix - vecsize; i += vecsize)
				_mat[i] = scalar::vec(mat[i]);

			for (; i < sizeOfMatrix; ++i)
				_mat[i] = mat[i];
		}

		else
		{
			for (i = 0; i < sizeOfMatrix; ++i)
				_mat[i] = mat[i];
		}
	}

	Memory_Block(size_t row, size_t col, string type); // rand or one matrix ...
	Memory_Block(initializer_list<initializer_list<scalar>> list_lists);
	Memory_Block(vector<vector<scalar>>& vec_vecs);
	Memory_Block(vector<vector<scalar>>&& vec_vecs);
	Memory_Block(const Memory_Block& M); // lvalue copy constructor
	Memory_Block(Memory_Block& M); // lvalue copy constructor
	Memory_Block(Memory_Block&& M); // rvalue copy constructor

	// accessors
	inline scalar& operator () (size_t i, size_t j) { return _mat[i * _col + j]; } // access to element (i, j)
	inline scalar* operator [] (size_t i) { return _mat + i * _col; } // access to row i

	// extractors
	T operator () (size_t upperRow, size_t lowerRow, size_t leftCol, size_t rightCol)  // sub-matrix: (upperRow : lowerRow(inclusive), leftCol : rightCol(inclusive))
	{
		size_t vecsize = VECSIZE, i, j, k;
		size_t row = lowerRow - upperRow + 1, col = rightCol - leftCol + 1;
		scalar* matrix = new scalar[row * col];

		if (rightCol >= vecsize)
		{
			for (i = upperRow, k = 0; i <= lowerRow; ++i)
			{
				for (j = leftCol; j < rightCol - vecsize; j += vecsize, k += vecsize)
					matrix[k] = scalar::vec(this->operator()(i, j)); // the operator () implemented above

				for (; j <= rightCol; ++j, ++k)
					matrix[k] = this->operator()(i, j);
			}
		}

		else
		{
			for (i = upperRow, k = 0; i <= lowerRow; ++i)
				for (j = leftCol; j <= rightCol; ++j, ++k)
					matrix[k] = this->operator()(i, j);
		}

		T subMatrix(row, col, matrix); // allocate sub matrix
		delete[] matrix;
		return subMatrix;
	}

	T sub(vector<size_t> row_list, vector<size_t> col_list);

	// sub-matrix: row_list - is a list of row nambers, col_list - is a list of column nambers
	// if (row_list.size() == 0) then - all rows
	// if (col_list.size() == 0) then - all columns

	// geters and seters
	inline scalar* data() { return _mat; }
	inline size_t rows() { return _row; }
	inline size_t cols() { return _col; }

	// assignment
	inline Memory_Block& operator = (const Memory_Block& M);
	inline Memory_Block& operator = (Memory_Block& M);
	inline Memory_Block& operator = (Memory_Block&& M);
	inline Memory_Block& operator = (vector<vector<scalar>>& vec_vecs);
	inline Memory_Block& operator = (vector<vector<scalar>>&& vec_vecs);

	// input\output operators
	friend ostream& operator << (ostream& out, Memory_Block& m)
	{
		size_t row = m.rows(), col = m.cols();
		for (size_t i = 0; i < row; ++i)
		{
			for (size_t j = 0; j < col; ++j)
				out << m(i, j) << " ";
			out << endl;
		}
		return out;
	}

	friend ostream& operator << (ostream& out, Memory_Block&& m)
	{
		size_t row = m.rows(), col = m.cols();
		for (size_t i = 0; i < row; ++i)
		{
			for (size_t j = 0; j < col; ++j)
				out << m(i, j) << " ";
			out << endl;
		}
		return out;
	}
	friend Memory_Block& operator << (Memory_Block& M, T x);
	friend Memory_Block& operator , (Memory_Block& M, T x);

	// destructor
	//~Memory_Block();
};
/* class Memory_Block - END */


/* class Matrix - START */
template <typename scalar>
class Matrix : public Memory_Block<scalar, Matrix<scalar>> // Type of Matrix
{
public:
	// constructors
	using Memory_Block<scalar, Matrix<scalar>>::Memory_Block;

	Matrix(const Matrix& M);
	Matrix(Matrix& M);
	Matrix(Matrix&& M);

	/* Assignment Operators - START */
	inline Matrix& operator = (const Matrix& M)
	{
		if (this != &M)
		{
			this->_row = M.rows();
			this->_col = M.cols();
			size_t sizeOfMatrix = this->_row * this->_col;
			scalar* matrix = M.data();
			for (size_t i = 0; i < sizeOfMatrix; ++i)
				this->_mat[i] = matrix[i];
		}

		return *this;
	}

	inline Matrix& operator = (Matrix& M)
	{
		if (this != &M)
		{
			this->_row = M.rows();
			this->_col = M.cols();
			size_t sizeOfMatrix = this->_row * this->_col;
			scalar* matrix = M.data();
			for (size_t i = 0; i < sizeOfMatrix; ++i)
				this->_mat[i] = matrix[i];
		}

		return *this;
	}

	inline Matrix& operator = (Matrix&& M)
	{
		if (this != &M)
		{
			this->_row = M.rows();
			this->_col = M.cols();
			size_t sizeOfMatrix = this->_row * this->_col;
			scalar* matrix = M.data();
			for (size_t i = 0; i < sizeOfMatrix; ++i)
				this->_mat[i] = matrix[i];
		}

		return *this;
	}

	inline Matrix& operator = (vector<vector<scalar>>& vec_vecs);
	inline Matrix& operator = (vector<vector<scalar>>&& vec_vecs);

	/* Assignment Operators - END */

	// operator += with matrices
	friend Matrix& operator += (Matrix& A, Matrix& B);
	friend Matrix& operator += (Matrix& A, Matrix&& B);
	friend Matrix& operator += (Matrix&& A, Matrix& B);
	friend Matrix& operator += (Matrix&& A, Matrix&& B);

	// operator -= with matrices
	friend Matrix& operator -= (Matrix& A, Matrix& B);
	friend Matrix& operator -= (Matrix& A, Matrix&& B);
	friend Matrix& operator -= (Matrix&& A, Matrix& B);
	friend Matrix& operator -= (Matrix&& A, Matrix&& B);

	// operator *= with scalar
	friend Matrix& operator *= (Matrix& M, scalar c);
	friend Matrix& operator *= (Matrix&& M, scalar c);

	// operator += with scalar
	friend Matrix& operator += (Matrix& M, scalar c);
	friend Matrix& operator += (Matrix&& M, scalar c);

	// operator -= with scalar
	friend Matrix& operator -= (Matrix& M, scalar c);
	friend Matrix& operator -= (Matrix&& M, scalar c);

	// operator /= with scalar
	friend Matrix& operator /= (Matrix& M, scalar c);
	friend Matrix& operator /= (Matrix&& M, scalar c);

	/* Sum Operator with Matrices - START */
	friend Matrix operator + (Matrix& A, Matrix& B)
	{
		size_t row = A.rows(), col = A.cols();
		if (row != B.rows() || col != B.cols())
			throw "Can't Sum! Wrong Dimensions!";


		size_t i, sizeOfMatrix = row * col, vecsize = VECSIZE;
		scalar* dataOfA = A.data(), * dataOfB = B.data(), * result = new scalar[row * col];
		if (sizeOfMatrix >= vecsize)
		{
			for (i = 0; i < sizeOfMatrix - vecsize; i += vecsize)
				result[i] = scalar::vec(dataOfA + i) + scalar::vec(dataOfB + i);

			for (; i < sizeOfMatrix; ++i)
				result[i] = dataOfA[i] + dataOfB[i];
		}

		else
		{
			for (i = 0; i < sizeOfMatrix; ++i)
				result[i] = dataOfA[i] + dataOfB[i];
		}

		Matrix<scalar> matrix(row, col, result);
		delete[] result;
		return matrix;
	}

	friend Matrix operator + (Matrix& A, Matrix&& B)
	{
		size_t row = A.rows(), col = A.cols();
		if (row != B.rows() || col != B.cols())
			throw "Can't Sum! Wrong Dimensions!";


		size_t i, sizeOfMatrix = row * col, vecsize = VECSIZE;
		scalar* dataOfA = A.data(), * dataOfB = B.data(), * result = new scalar[row * col];
		if (sizeOfMatrix >= vecsize)
		{
			for (i = 0; i < sizeOfMatrix - vecsize; i += vecsize)
				result[i] = scalar::vec(dataOfA + i) + scalar::vec(dataOfB + i);

			for (; i < sizeOfMatrix; ++i)
				result[i] = dataOfA[i] + dataOfB[i];
		}

		else
		{
			for (i = 0; i < sizeOfMatrix; ++i)
				result[i] = dataOfA[i] + dataOfB[i];
		}

		Matrix<scalar> matrix(row, col, result);
		delete[] result;
		return matrix;
	}

	friend Matrix operator + (Matrix&& A, Matrix& B)
	{
		size_t row = A.rows(), col = A.cols();
		if (row != B.rows() || col != B.cols())
			throw "Can't Sum! Wrong Dimensions!";


		size_t i, sizeOfMatrix = row * col, vecsize = VECSIZE;
		scalar* dataOfA = A.data(), * dataOfB = B.data(), * result = new scalar[row * col];
		if (sizeOfMatrix >= vecsize)
		{
			for (i = 0; i < sizeOfMatrix - vecsize; i += vecsize)
				result[i] = scalar::vec(dataOfA + i) + scalar::vec(dataOfB + i);

			for (; i < sizeOfMatrix; ++i)
				result[i] = dataOfA[i] + dataOfB[i];
		}

		else
		{
			for (i = 0; i < sizeOfMatrix; ++i)
				result[i] = dataOfA[i] + dataOfB[i];
		}

		Matrix<scalar> matrix(row, col, result);
		delete[] result;
		return matrix;
	}

	friend Matrix operator + (Matrix&& A, Matrix&& B)
	{
		size_t row = A.rows(), col = A.cols();
		if (row != B.rows() || col != B.cols())
			throw "Can't Sum! Wrong Dimensions!";


		size_t i, sizeOfMatrix = row * col, vecsize = VECSIZE;
		scalar* dataOfA = A.data(), * dataOfB = B.data(), * result = new scalar[row * col];
		if (sizeOfMatrix >= vecsize)
		{
			for (i = 0; i < sizeOfMatrix - vecsize; i += vecsize)
				result[i] = scalar::vec(dataOfA + i) + scalar::vec(dataOfB + i);

			for (; i < sizeOfMatrix; ++i)
				result[i] = dataOfA[i] + dataOfB[i];
		}

		else
		{
			for (i = 0; i < sizeOfMatrix; ++i)
				result[i] = dataOfA[i] + dataOfB[i];
		}

		Matrix<scalar> matrix(row, col, result);
		delete[] result;
		return matrix;
	}
	/* Sum Operator with Matrices - END */

	/* Sub Operator with Matrices - START */
	friend Matrix operator - (Matrix& A, Matrix& B)
	{
		size_t row = A.rows(), col = A.cols();
		if (row != B.rows() || col != B.cols())
			throw "Can't Sub! Wrong Dimensions!";

		size_t i, sizeOfMatrix = row * col, vecsize = VECSIZE;
		scalar* dataOfA = A.data(), * dataOfB = B.data(), * result = new scalar[row * col];

		if (sizeOfMatrix >= vecsize)
		{
			for (i = 0; i < sizeOfMatrix - vecsize; i += vecsize)
				result[i] = scalar::vec(dataOfA + i) - scalar::vec(dataOfB + i);

			for (; i < sizeOfMatrix; ++i)
				result[i] = dataOfA[i] - dataOfB[i];
		}

		else
		{
			for (i = 0; i < sizeOfMatrix; ++i)
				result[i] = dataOfA[i] - dataOfB[i];
		}

		Matrix<scalar> matrix(row, col, result);
		delete[] result;
		return matrix;
	}

	friend Matrix operator - (Matrix& A, Matrix&& B)
	{
		size_t row = A.rows(), col = A.cols();
		if (row != B.rows() || col != B.cols())
			throw "Can't Sub! Wrong Dimensions!";

		size_t i, sizeOfMatrix = row * col, vecsize = VECSIZE;
		scalar* dataOfA = A.data(), * dataOfB = B.data(), * result = new scalar[row * col];

		if (sizeOfMatrix >= vecsize)
		{
			for (i = 0; i < sizeOfMatrix - vecsize; i += vecsize)
				result[i] = scalar::vec(dataOfA + i) - scalar::vec(dataOfB + i);

			for (; i < sizeOfMatrix; ++i)
				result[i] = dataOfA[i] - dataOfB[i];
		}

		else
		{
			for (i = 0; i < sizeOfMatrix; ++i)
				result[i] = dataOfA[i] - dataOfB[i];
		}

		Matrix<scalar> matrix(row, col, result);
		delete[] result;
		return matrix;
	}

	friend Matrix operator - (Matrix&& A, Matrix& B)
	{
		size_t row = A.rows(), col = A.cols();
		if (row != B.rows() || col != B.cols())
			throw "Can't Sub! Wrong Dimensions!";

		size_t i, sizeOfMatrix = row * col, vecsize = VECSIZE;
		scalar* dataOfA = A.data(), * dataOfB = B.data(), * result = new scalar[row * col];

		if (sizeOfMatrix >= vecsize)
		{
			for (i = 0; i < sizeOfMatrix - vecsize; i += vecsize)
				result[i] = scalar::vec(dataOfA + i) - scalar::vec(dataOfB + i);

			for (; i < sizeOfMatrix; ++i)
				result[i] = dataOfA[i] - dataOfB[i];
		}

		else
		{
			for (i = 0; i < sizeOfMatrix; ++i)
				result[i] = dataOfA[i] - dataOfB[i];
		}

		Matrix<scalar> matrix(row, col, result);
		delete[] result;
		return matrix;
	}

	friend Matrix operator - (Matrix&& A, Matrix&& B)
	{
		size_t row = A.rows(), col = A.cols();
		if (row != B.rows() || col != B.cols())
			throw "Can't Sub! Wrong Dimensions!";

		size_t i, sizeOfMatrix = row * col, vecsize = VECSIZE;
		scalar* dataOfA = A.data(), * dataOfB = B.data(), * result = new scalar[row * col];

		if (sizeOfMatrix >= vecsize)
		{
			for (i = 0; i < sizeOfMatrix - vecsize; i += vecsize)
				result[i] = scalar::vec(dataOfA + i) - scalar::vec(dataOfB + i);

			for (; i < sizeOfMatrix; ++i)
				result[i] = dataOfA[i] - dataOfB[i];
		}

		else
		{
			for (i = 0; i < sizeOfMatrix; ++i)
				result[i] = dataOfA[i] - dataOfB[i];
		}

		Matrix<scalar> matrix(row, col, result);
		delete[] result;
		return matrix;
	}
	/* Sub Operator with Matrices - END */

	// operator * with matrices
	friend Matrix operator * (Matrix& A, Matrix& B);
	friend Matrix operator * (Matrix& A, Matrix&& B);
	friend Matrix operator * (Matrix&& A, Matrix& B);
	friend Matrix operator * (Matrix&& A, Matrix&& B);

	friend Matrix operator + (Matrix& A, scalar c); //4 times
	friend Matrix operator - (Matrix& A, scalar c); //4 times
	friend Matrix operator * (Matrix& A, scalar c); //4 times
	friend Matrix operator / (Matrix& A, scalar c); //2 times

	/* Arithmetic Operators - END */

	// product with transpose
	friend Matrix product(Matrix&& A, char mode_a, Matrix&& B, char mode_b); // 4 times

	// Element-wise product
	friend Matrix dot_product(Matrix&& a, Matrix&& b); //4 times

	Matrix trans(bool inplace);
	Matrix conj(bool inplace);
	Matrix diag();
};
/* class Matrix - END */


/* class Vector - START */
template <typename scalar>
class Vector : public Matrix<scalar>
{
	// constructors
	Vector(); // empty constructor
	Vector(size_t len); // Vector of size len
	Vector(size_t len, scalar val); // Vector filled by val
	Vector(size_t row, size_t col, std::string type); //rand Vector ...
	Vector(std::initializer_list<scalar> list);
	Vector(std::vector<scalar>& vec);
	Vector(std::vector<scalar>&& vec_vecs);
	Vector(const Vector& V); // lvalue copy constructor
	Vector(Vector& V); // lvalue copy constructor
	Vector(Vector&& V); // rvalue copy constructor
};
/* class Vector - END */

#endif // !HPEML