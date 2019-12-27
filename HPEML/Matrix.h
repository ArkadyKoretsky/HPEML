#ifndef Matrix_Class
#define Matrix_Class

#include "Memory_Block.h"
using namespace std;

template <typename scalar>
class Matrix : public Memory_Block<scalar, Matrix<scalar>> // Type of Matrix
{
public:
	/* Constructors - START */
	using Memory_Block<scalar, Matrix<scalar>>::Memory_Block;

	Matrix(const Matrix& M);
	Matrix(Matrix& M);
	Matrix(Matrix&& M);
	/* Constructors - END */


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

#endif // !Matrix_Class