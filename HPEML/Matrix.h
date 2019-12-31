#ifndef Matrix_Class
#define Matrix_Class

#include "Memory_Block.h"
using namespace std;

template <typename scalar>
class Matrix : public Memory_Block<scalar, Matrix<scalar>> // Type of Matrix
{
public:

	using Memory_Block<scalar, Matrix<scalar>>::Memory_Block;

	// constructors
	Matrix(const Matrix& M) : Memory_Block<scalar, Matrix<scalar>>::Memory_Block(M) {}
	Matrix(Matrix& M) : Memory_Block<scalar, Matrix<scalar>>::Memory_Block(M) {}
	Matrix(Matrix&& M) noexcept : Memory_Block<scalar, Matrix<scalar>>::Memory_Block(M) {}
	Matrix(Matrix M[4]) : Memory_Block<scalar, Matrix<scalar>>::Memory_Block(M) {} // collect 4 blocks into 1 big matrix


	/* Assignment Operators - START */
	inline Matrix& operator = (const Matrix& M)
	{
		if (this != &M)
		{
			this->_row = M.rows();
			this->_col = M.cols();
			size_t i, sizeOfMatrix = this->_row * this->_col, vecsize = VECSIZE;
			scalar* matrix = M.data();
			if (this->_mat == nullptr)
				this->_mat = new scalar[sizeOfMatrix];

			if (sizeOfMatrix >= vecsize)
			{
				for (i = 0; i < sizeOfMatrix - vecsize; i += vecsize)
					this->_mat[i] = scalar::vec(matrix + i);

				for (; i < sizeOfMatrix; ++i)
					this->_mat[i] = matrix[i];
			}

			else
			{
				for (i = 0; i < sizeOfMatrix; ++i)
					this->_mat[i] = matrix[i];
			}
		}

		return *this;
	}

	inline Matrix& operator = (Matrix& M)
	{
		if (this != &M)
		{
			this->_row = M.rows();
			this->_col = M.cols();
			size_t i, sizeOfMatrix = this->_row * this->_col, vecsize = VECSIZE;
			scalar* matrix = M.data();
			if (this->_mat == nullptr)
				this->_mat = new scalar[sizeOfMatrix];

			if (sizeOfMatrix >= vecsize)
			{
				for (i = 0; i < sizeOfMatrix - vecsize; i += vecsize)
					this->_mat[i] = scalar::vec(matrix + i);

				for (; i < sizeOfMatrix; ++i)
					this->_mat[i] = matrix[i];
			}

			else
			{
				for (i = 0; i < sizeOfMatrix; ++i)
					this->_mat[i] = matrix[i];
			}
		}

		return *this;
	}

	inline Matrix& operator = (Matrix&& M) noexcept
	{
		if (this != &M)
		{
			this->_row = M.rows();
			this->_col = M.cols();
			size_t i, sizeOfMatrix = this->_row * this->_col, vecsize = VECSIZE;
			scalar* matrix = M.data();
			if (this->_mat == nullptr)
				this->_mat = new scalar[sizeOfMatrix];

			if (sizeOfMatrix >= vecsize)
			{
				for (i = 0; i < sizeOfMatrix - vecsize; i += vecsize)
					this->_mat[i] = scalar::vec(matrix + i);

				for (; i < sizeOfMatrix; ++i)
					this->_mat[i] = matrix[i];
			}

			else
			{
				for (i = 0; i < sizeOfMatrix; ++i)
					this->_mat[i] = matrix[i];
			}
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


	/* Multiplication Operator with Matrices - START */
	friend Matrix operator * (Matrix& A, Matrix& B)
	{
		if (A.cols() != B.rows())
			throw "Wrong Dimensions! Can't Multiply!";

		size_t row = A.rows(), col = B.cols(), col_row = A.cols(); // for padding removal
		A.padRowOrColumn();
		B.padRowOrColumn();
		size_t rowA = A.rows(), colA_rowB = A.cols(), colB = B.cols(); // dimensions after padding

		Matrix<scalar> AA[4], BB[4];

		// split A matrix
		AA[0] = A.operator()(0, rowA / 2 - 1, 0, colA_rowB / 2 - 1);
		AA[1] = A.operator()(0, rowA / 2 - 1, colA_rowB / 2, colA_rowB - 1);
		AA[2] = A.operator()(rowA / 2, rowA - 1, 0, colA_rowB / 2 - 1);
		AA[3] = A.operator()(rowA / 2, rowA - 1, colA_rowB / 2, colA_rowB - 1);
		A.removePadding(row, col_row);

		// split B matrix
		BB[0] = B.operator()(0, colA_rowB / 2 - 1, 0, colB / 2 - 1);
		BB[1] = B.operator()(0, colA_rowB / 2 - 1, colB / 2, colB - 1);
		BB[2] = B.operator()(colA_rowB / 2, colA_rowB - 1, 0, colB / 2 - 1);
		BB[3] = B.operator()(colA_rowB / 2, colA_rowB - 1, colB / 2, colB - 1);
		B.removePadding(col_row, col);

		Matrix<scalar> S[8];

		// sums from A sub matrices
		S[0] = AA[2] + AA[3];
		S[1] = S[0] - AA[0];
		S[2] = AA[0] - AA[2];
		S[3] = AA[1] - S[1];

		// sums from B sub matrices
		S[4] = BB[1] - BB[0];
		S[5] = BB[3] - S[4];
		S[6] = BB[3] - BB[1];
		S[7] = S[5] - BB[2];

		Matrix<scalar> P[7];
		thread t[7];
		t[0] = thread([&P, &AA, &BB, &S]() {P[0].naiveMult(S[1], S[5]); });
		t[1] = thread([&P, &AA, &BB, &S]() {P[1].naiveMult(AA[0], BB[0]); });
		t[2] = thread([&P, &AA, &BB, &S]() {P[2].naiveMult(AA[1], BB[2]); });
		t[3] = thread([&P, &AA, &BB, &S]() {P[3].naiveMult(S[2], S[6]); });
		t[4] = thread([&P, &AA, &BB, &S]() {P[4].naiveMult(S[0], S[4]); });
		t[5] = thread([&P, &AA, &BB, &S]() {P[5].naiveMult(S[3], BB[3]); });
		t[6] = thread([&P, &AA, &BB, &S]() {P[6].naiveMult(AA[3], S[7]); });

		for (size_t i = 0; i < 7; ++i)
			t[i].join();

		Matrix<scalar> T[2];
		T[0] = P[0] + P[1];
		T[1] = T[0] + P[3];

		Matrix<scalar> CC[4];
		CC[0] = P[1] + P[2];
		CC[1] = T[0] + P[4] + P[5];
		CC[2] = T[1] - P[6];
		CC[3] = T[1] + P[4];

		// collect into result matrix
		Matrix<scalar> C(CC);
		C.removePadding(row, col);

		return C;
	}

	friend Matrix operator * (Matrix& A, Matrix&& B)
	{
		if (A.cols() != B.rows())
			throw "Wrong Dimensions! Can't Multiply!";

		size_t row = A.rows(), col = B.cols(), col_row = A.cols(); // for padding removal
		A.padRowOrColumn();
		B.padRowOrColumn();
		size_t rowA = A.rows(), colA_rowB = A.cols(), colB = B.cols(); // dimensions after padding

		Matrix<scalar> AA[4], BB[4];

		// split A matrix
		AA[0] = A.operator()(0, rowA / 2 - 1, 0, colA_rowB / 2 - 1);
		AA[1] = A.operator()(0, rowA / 2 - 1, colA_rowB / 2, colA_rowB - 1);
		AA[2] = A.operator()(rowA / 2, rowA - 1, 0, colA_rowB / 2 - 1);
		AA[3] = A.operator()(rowA / 2, rowA - 1, colA_rowB / 2, colA_rowB - 1);
		A.removePadding(row, col_row);

		// split B matrix
		BB[0] = B.operator()(0, colA_rowB / 2 - 1, 0, colB / 2 - 1);
		BB[1] = B.operator()(0, colA_rowB / 2 - 1, colB / 2, colB - 1);
		BB[2] = B.operator()(colA_rowB / 2, colA_rowB - 1, 0, colB / 2 - 1);
		BB[3] = B.operator()(colA_rowB / 2, colA_rowB - 1, colB / 2, colB - 1);
		B.removePadding(col_row, col);

		Matrix<scalar> S[8];

		// sums from A sub matrices
		S[0] = AA[2] + AA[3];
		S[1] = S[0] - AA[0];
		S[2] = AA[0] - AA[2];
		S[3] = AA[1] - S[1];

		// sums from B sub matrices
		S[4] = BB[1] - BB[0];
		S[5] = BB[3] - S[4];
		S[6] = BB[3] - BB[1];
		S[7] = S[5] - BB[2];

		Matrix<scalar> P[7];
		thread t[7];
		t[0] = thread([&P, &AA, &BB, &S]() {P[0].naiveMult(S[1], S[5]); });
		t[1] = thread([&P, &AA, &BB, &S]() {P[1].naiveMult(AA[0], BB[0]); });
		t[2] = thread([&P, &AA, &BB, &S]() {P[2].naiveMult(AA[1], BB[2]); });
		t[3] = thread([&P, &AA, &BB, &S]() {P[3].naiveMult(S[2], S[6]); });
		t[4] = thread([&P, &AA, &BB, &S]() {P[4].naiveMult(S[0], S[4]); });
		t[5] = thread([&P, &AA, &BB, &S]() {P[5].naiveMult(S[3], BB[3]); });
		t[6] = thread([&P, &AA, &BB, &S]() {P[6].naiveMult(AA[3], S[7]); });

		for (size_t i = 0; i < 7; ++i)
			t[i].join();

		Matrix<scalar> T[2];
		T[0] = P[0] + P[1];
		T[1] = T[0] + P[3];

		Matrix<scalar> CC[4];
		CC[0] = P[1] + P[2];
		CC[1] = T[0] + P[4] + P[5];
		CC[2] = T[1] - P[6];
		CC[3] = T[1] + P[4];

		// collect into result matrix
		Matrix<scalar> C(CC);
		C.removePadding(row, col);

		return C;
	}

	friend Matrix operator * (Matrix&& A, Matrix& B)
	{
		if (A.cols() != B.rows())
			throw "Wrong Dimensions! Can't Multiply!";

		size_t row = A.rows(), col = B.cols(), col_row = A.cols(); // for padding removal
		A.padRowOrColumn();
		B.padRowOrColumn();
		size_t rowA = A.rows(), colA_rowB = A.cols(), colB = B.cols(); // dimensions after padding

		Matrix<scalar> AA[4], BB[4];

		// split A matrix
		AA[0] = A.operator()(0, rowA / 2 - 1, 0, colA_rowB / 2 - 1);
		AA[1] = A.operator()(0, rowA / 2 - 1, colA_rowB / 2, colA_rowB - 1);
		AA[2] = A.operator()(rowA / 2, rowA - 1, 0, colA_rowB / 2 - 1);
		AA[3] = A.operator()(rowA / 2, rowA - 1, colA_rowB / 2, colA_rowB - 1);
		A.removePadding(row, col_row);

		// split B matrix
		BB[0] = B.operator()(0, colA_rowB / 2 - 1, 0, colB / 2 - 1);
		BB[1] = B.operator()(0, colA_rowB / 2 - 1, colB / 2, colB - 1);
		BB[2] = B.operator()(colA_rowB / 2, colA_rowB - 1, 0, colB / 2 - 1);
		BB[3] = B.operator()(colA_rowB / 2, colA_rowB - 1, colB / 2, colB - 1);
		B.removePadding(col_row, col);

		Matrix<scalar> S[8];

		// sums from A sub matrices
		S[0] = AA[2] + AA[3];
		S[1] = S[0] - AA[0];
		S[2] = AA[0] - AA[2];
		S[3] = AA[1] - S[1];

		// sums from B sub matrices
		S[4] = BB[1] - BB[0];
		S[5] = BB[3] - S[4];
		S[6] = BB[3] - BB[1];
		S[7] = S[5] - BB[2];

		Matrix<scalar> P[7];
		thread t[7];
		t[0] = thread([&P, &AA, &BB, &S]() {P[0].naiveMult(S[1], S[5]); });
		t[1] = thread([&P, &AA, &BB, &S]() {P[1].naiveMult(AA[0], BB[0]); });
		t[2] = thread([&P, &AA, &BB, &S]() {P[2].naiveMult(AA[1], BB[2]); });
		t[3] = thread([&P, &AA, &BB, &S]() {P[3].naiveMult(S[2], S[6]); });
		t[4] = thread([&P, &AA, &BB, &S]() {P[4].naiveMult(S[0], S[4]); });
		t[5] = thread([&P, &AA, &BB, &S]() {P[5].naiveMult(S[3], BB[3]); });
		t[6] = thread([&P, &AA, &BB, &S]() {P[6].naiveMult(AA[3], S[7]); });

		for (size_t i = 0; i < 7; ++i)
			t[i].join();

		Matrix<scalar> T[2];
		T[0] = P[0] + P[1];
		T[1] = T[0] + P[3];

		Matrix<scalar> CC[4];
		CC[0] = P[1] + P[2];
		CC[1] = T[0] + P[4] + P[5];
		CC[2] = T[1] - P[6];
		CC[3] = T[1] + P[4];

		// collect into result matrix
		Matrix<scalar> C(CC);
		C.removePadding(row, col);

		return C;
	}

	friend Matrix operator * (Matrix&& A, Matrix&& B)
	{
		if (A.cols() != B.rows())
			throw "Wrong Dimensions! Can't Multiply!";

		size_t row = A.rows(), col = B.cols(), col_row = A.cols(); // for padding removal
		A.padRowOrColumn();
		B.padRowOrColumn();
		size_t rowA = A.rows(), colA_rowB = A.cols(), colB = B.cols(); // dimensions after padding

		Matrix<scalar> AA[4], BB[4];

		// split A matrix
		AA[0] = A.operator()(0, rowA / 2 - 1, 0, colA_rowB / 2 - 1);
		AA[1] = A.operator()(0, rowA / 2 - 1, colA_rowB / 2, colA_rowB - 1);
		AA[2] = A.operator()(rowA / 2, rowA - 1, 0, colA_rowB / 2 - 1);
		AA[3] = A.operator()(rowA / 2, rowA - 1, colA_rowB / 2, colA_rowB - 1);
		A.removePadding(row, col_row);

		// split B matrix
		BB[0] = B.operator()(0, colA_rowB / 2 - 1, 0, colB / 2 - 1);
		BB[1] = B.operator()(0, colA_rowB / 2 - 1, colB / 2, colB - 1);
		BB[2] = B.operator()(colA_rowB / 2, colA_rowB - 1, 0, colB / 2 - 1);
		BB[3] = B.operator()(colA_rowB / 2, colA_rowB - 1, colB / 2, colB - 1);
		B.removePadding(col_row, col);

		Matrix<scalar> S[8];

		// sums from A sub matrices
		S[0] = AA[2] + AA[3];
		S[1] = S[0] - AA[0];
		S[2] = AA[0] - AA[2];
		S[3] = AA[1] - S[1];

		// sums from B sub matrices
		S[4] = BB[1] - BB[0];
		S[5] = BB[3] - S[4];
		S[6] = BB[3] - BB[1];
		S[7] = S[5] - BB[2];

		Matrix<scalar> P[7];
		thread t[7];
		t[0] = thread([&P, &AA, &BB, &S]() {P[0].naiveMult(S[1], S[5]); });
		t[1] = thread([&P, &AA, &BB, &S]() {P[1].naiveMult(AA[0], BB[0]); });
		t[2] = thread([&P, &AA, &BB, &S]() {P[2].naiveMult(AA[1], BB[2]); });
		t[3] = thread([&P, &AA, &BB, &S]() {P[3].naiveMult(S[2], S[6]); });
		t[4] = thread([&P, &AA, &BB, &S]() {P[4].naiveMult(S[0], S[4]); });
		t[5] = thread([&P, &AA, &BB, &S]() {P[5].naiveMult(S[3], BB[3]); });
		t[6] = thread([&P, &AA, &BB, &S]() {P[6].naiveMult(AA[3], S[7]); });

		for (size_t i = 0; i < 7; ++i)
			t[i].join();

		Matrix<scalar> T[2];
		T[0] = P[0] + P[1];
		T[1] = T[0] + P[3];

		Matrix<scalar> CC[4];
		CC[0] = P[1] + P[2];
		CC[1] = T[0] + P[4] + P[5];
		CC[2] = T[1] - P[6];
		CC[3] = T[1] + P[4];

		// collect into result matrix
		Matrix<scalar> C(CC);
		C.removePadding(row, col);

		return C;
	}
	/* Multiplication Operator with Matrices - END */


	friend Matrix operator + (Matrix& A, scalar c); //4 times
	friend Matrix operator - (Matrix& A, scalar c); //4 times
	friend Matrix operator * (Matrix& A, scalar c); //4 times
	friend Matrix operator / (Matrix& A, scalar c); //2 times

	// product with transpose
	friend Matrix product(Matrix&& A, char mode_a, Matrix&& B, char mode_b); // 4 times


	/* Element-Wise Product - START */
	Matrix dot_product(Matrix& A, Matrix& B)
	{
		size_t row = A.rows(), col = A.cols();
		if (row != B.rows() || col != B.cols())
			throw "Can't Multiply Element-Wise! Wrong Dimensions!";

		size_t i, sizeOfMatrix = row * col, vecsize = VECSIZE;
		scalar* dataOfA = A.data(), * dataOfB = B.data(), * result = new scalar[row * col];
		if (sizeOfMatrix >= vecsize)
		{
			for (i = 0; i < sizeOfMatrix - vecsize; i += vecsize)
				result[i] = scalar::vec(dataOfA + i) * scalar::vec(dataOfB + i);

			for (; i < sizeOfMatrix; ++i)
				result[i] = dataOfA[i] * dataOfB[i];
		}

		else
		{
			for (i = 0; i < sizeOfMatrix; ++i)
				result[i] = dataOfA[i] * dataOfB[i];
		}

		Matrix<scalar> matrix(row, col, result);
		delete[] result;
		return matrix;
	}

	Matrix dot_product(Matrix& A, Matrix&& B)
	{
		size_t row = A.rows(), col = A.cols();
		if (row != B.rows() || col != B.cols())
			throw "Can't Multiply Element-Wise! Wrong Dimensions!";

		size_t i, sizeOfMatrix = row * col, vecsize = VECSIZE;
		scalar* dataOfA = A.data(), * dataOfB = B.data(), * result = new scalar[row * col];
		if (sizeOfMatrix >= vecsize)
		{
			for (i = 0; i < sizeOfMatrix - vecsize; i += vecsize)
				result[i] = scalar::vec(dataOfA + i) * scalar::vec(dataOfB + i);

			for (; i < sizeOfMatrix; ++i)
				result[i] = dataOfA[i] * dataOfB[i];
		}

		else
		{
			for (i = 0; i < sizeOfMatrix; ++i)
				result[i] = dataOfA[i] * dataOfB[i];
		}

		Matrix<scalar> matrix(row, col, result);
		delete[] result;
		return matrix;
	}

	Matrix dot_product(Matrix&& A, Matrix& B)
	{
		size_t row = A.rows(), col = A.cols();
		if (row != B.rows() || col != B.cols())
			throw "Can't Multiply Element-Wise! Wrong Dimensions!";

		size_t i, sizeOfMatrix = row * col, vecsize = VECSIZE;
		scalar* dataOfA = A.data(), * dataOfB = B.data(), * result = new scalar[row * col];
		if (sizeOfMatrix >= vecsize)
		{
			for (i = 0; i < sizeOfMatrix - vecsize; i += vecsize)
				result[i] = scalar::vec(dataOfA + i) * scalar::vec(dataOfB + i);

			for (; i < sizeOfMatrix; ++i)
				result[i] = dataOfA[i] * dataOfB[i];
		}

		else
		{
			for (i = 0; i < sizeOfMatrix; ++i)
				result[i] = dataOfA[i] * dataOfB[i];
		}

		Matrix<scalar> matrix(row, col, result);
		delete[] result;
		return matrix;
	}

	Matrix dot_product(Matrix&& A, Matrix&& B)
	{
		size_t row = A.rows(), col = A.cols();
		if (row != B.rows() || col != B.cols())
			throw "Can't Multiply Element-Wise! Wrong Dimensions!";

		size_t i, sizeOfMatrix = row * col, vecsize = VECSIZE;
		scalar* dataOfA = A.data(), * dataOfB = B.data(), * result = new scalar[row * col];
		if (sizeOfMatrix >= vecsize)
		{
			for (i = 0; i < sizeOfMatrix - vecsize; i += vecsize)
				result[i] = scalar::vec(dataOfA + i) * scalar::vec(dataOfB + i);

			for (; i < sizeOfMatrix; ++i)
				result[i] = dataOfA[i] * dataOfB[i];
		}

		else
		{
			for (i = 0; i < sizeOfMatrix; ++i)
				result[i] = dataOfA[i] * dataOfB[i];
		}

		Matrix<scalar> matrix(row, col, result);
		delete[] result;
		return matrix;
	}
	/* Element-Wise Product - END */


	Matrix trans(bool inplace);
	Matrix conj(bool inplace);


	/* Diagonal of Matrix - START */
	Matrix diag() // the diagonal returned as column vector
	{
		size_t row = this->_row, col = this->_col;
		if (row != col)
			throw "Not Square Matrix!";

		scalar* diagonal = new scalar[row], * matrix = this->_mat;

		for (size_t i = 0, j = 0; i < row * col; i += col + 1, ++j)
			diagonal[j] = matrix[i];

		return Matrix<scalar>(row, 1, diagonal);
	}
	/* Diagonal of Matrix - END */


	/* Padding Functions - START */
	void padRowOrColumn() // pad single row\column with zeros if the dimensions are not even
	{
		size_t originalRow = this->_row, originalCol = this->_col;
		size_t row = originalRow % 2 == 0 ? originalRow : originalRow + 1;
		size_t col = originalCol % 2 == 0 ? originalCol : originalCol + 1;

		if (row == originalRow && col == originalCol) // no need for even padding
			return;

		size_t i, j, vecsize = VECSIZE, sizeOfMatrix = row * col;
		scalar* matrix = new scalar[sizeOfMatrix]; // activates the empty constructor scalar() which automatically sets the whole matrix to 0
		scalar* originalMatrix = this->_mat;

		// copy the original matrix
		if (originalCol >= vecsize)
		{
			for (i = 0; i < originalRow; ++i)
			{
				for (j = 0; j < originalCol - vecsize; j += vecsize)
					matrix[i * col + j] = scalar::vec(originalMatrix + i * originalCol + j);

				for (; j < originalCol; ++j)
					matrix[i * col + j] = originalMatrix[i * originalCol + j];
			}
		}
		else
		{
			for (i = 0; i < originalRow; ++i)
				for (j = 0; j < originalCol; ++j)
					matrix[i * col + j] = originalMatrix[i * originalCol + j];
		}

		this->_row = row;
		this->_col = col;
		delete[] this->_mat;
		this->_mat = matrix;
	}

	void padBlockSize()
	{
		size_t blockSize = I_BLOCKSIZE, vecsize = VECSIZE, i, j;
		size_t row = this->_row, originalRow = this->_row;
		size_t col = this->_col, originalCol = this->_col;

		if (row % blockSize != 0)
			row = (row / blockSize + 1) * blockSize;

		if (col % blockSize != 0)
			col = (col / blockSize + 1) * blockSize;

		if (row == originalRow && col == originalCol) // no need for blocsize padding
			return;

		size_t sizeOfMatrix = row * col;
		scalar* matrix = new scalar[sizeOfMatrix];
		scalar* originalMatrix = this->_mat; // activates the empty constructor scalar() which automatically sets the whole matrix to 0

		// copy the original matrix
		if (originalCol >= vecsize)
		{
			for (i = 0; i < originalRow; ++i)
			{
				for (j = 0; j < originalCol - vecsize; j += vecsize)
					matrix[i * col + j] = scalar::vec(originalMatrix + i * originalCol + j);

				for (; j < originalCol; ++j)
					matrix[i * col + j] = originalMatrix[i * originalCol + j];
			}
		}
		else
		{
			for (i = 0; i < originalRow; ++i)
				for (j = 0; j < originalCol; ++j)
					matrix[i * col + j] = originalMatrix[i * originalCol + j];
		}

		this->_row = row;
		this->_col = col;
		delete[] this->_mat;
		this->_mat = matrix;
	}

	void removePadding(size_t row, size_t col) // resize the matrix into row X col
	{
		if (row == this->_row && col == this->_col) // no need to unpadd
			return;

		size_t i, j, vecsize = VECSIZE, originalRow = this->_row, originalCol = this->_col;
		scalar* matrix = new scalar[row * col], * originalMatrix = this->_mat;

		if (col >= vecsize)
		{
			for (i = 0; i < row; ++i)
			{
				for (j = 0; j < col - vecsize; j += vecsize)
					matrix[i * col + j] = scalar::vec(originalMatrix + i * originalCol + j);

				for (; j < col; ++j)
					matrix[i * col + j] = originalMatrix[i * originalCol + j];
			}

		}
		else
		{
			for (i = 0; i < row; ++i)
				for (j = 0; j < col; ++j)
					matrix[i * col + j] = originalMatrix[i * originalCol + j];
		}

		this->_row = row;
		this->_col = col;
		delete[] this->_mat;
		this->_mat = matrix;
	}
	/* Padding Functions - END */


	/* Naive Multiplication - START */
	void naiveMult(Matrix& A, Matrix& B)
	{
		size_t original_rowA = A.rows(), original_colA_rowB = A.cols(), original_colB = B.cols(); // for padding removal

		// pad the matrices before multiplying
		A.padBlockSize();
		B.padBlockSize();
		size_t rowA = A.rows(), colA_rowB = A.cols(), colB = B.cols();
		size_t iBlock = min(I_BLOCKSIZE, (int)rowA);
		size_t jBlock = min(J_BLOCKSIZE, (int)colA_rowB);
		size_t kBlock = min(K_BLOCKSIZE, (int)colB);

		scalar* tempB = new scalar[colA_rowB * colB], * originalB = B.data(), * originalA = A.data(), * result = new scalar[rowA * colB];
		size_t index = 0, vecsize = VECSIZE;
		const size_t unroll_1 = UNROLL_1, unroll_2 = UNROLL_2;
		typename scalar::vec sum[unroll_2][unroll_1], vecA[unroll_1], vecB[unroll_2];

		// Storing matrix B in tempB (in other order)
		for (size_t jj = 0; jj < colB; jj += jBlock)
			for (size_t kk = 0; kk < colA_rowB; kk += kBlock)
				for (size_t j = jj; j < jj + jBlock; j += unroll_2 * vecsize)
					for (size_t k = kk; k < kk + kBlock; ++k)
					{
						for (size_t x = 0; x < unroll_2; ++x)
						{
							vecB[x] = originalB + k * colB + j + x * vecsize;
							tempB[index + x * vecsize] = vecB[x];
						}
						index += unroll_2 * vecsize;
					}

		// matrix multiplication
		for (size_t ii = 0; ii < rowA; ii += iBlock)
			for (size_t jj = 0; jj < colB; jj += jBlock)
				for (size_t kk = 0; kk < colA_rowB; kk += kBlock)
					for (size_t i = ii; i < ii + iBlock; i += unroll_1)
						for (size_t j = jj; j < jj + jBlock; j += unroll_2 * vecsize)
						{
							index = (j - jj) * kBlock + kk * jBlock + jj * colA_rowB;

							if (kk == 0)
								for (size_t x = 0; x < unroll_1; ++x)
									for (size_t y = 0; y < unroll_2; ++y)
										sum[y][x] = scalar::vec();
							else
								for (size_t x = 0; x < unroll_1; ++x)
									for (size_t y = 0; y < unroll_2; ++y)
										sum[y][x] = result + (i + x) * colB + j + y * vecsize;

							for (size_t k = kk; k < kk + kBlock; ++k)
							{
								for (size_t x = 0; x < unroll_2; ++x)
									vecB[x] = tempB + index + x * vecsize;

								for (size_t x = 0; x < unroll_1; ++x)
								{
									vecA[x] = originalA[(i + x) * colA_rowB + k];
									for (size_t y = 0; y < unroll_2; ++y)
										sum[y][x] = sum[y][x].mul_add(vecA[x], vecB[y], sum[y][x]);
								}
								index += unroll_2 * vecsize;
							}

							for (size_t x = 0; x < unroll_1; ++x)
								for (size_t y = 0; y < unroll_2; ++y)
									result[(i + x) * colB + j + y * vecsize] = sum[y][x];
						}

		delete[] tempB;
		A.removePadding(original_rowA, original_colA_rowB);
		B.removePadding(original_colA_rowB, original_colB);
		this->_mat = result;
		this->removePadding(original_rowA, original_colB);
	}

	void naiveMult(Matrix& A, Matrix&& B)
	{
		size_t original_rowA = A.rows(), original_colA_rowB = A.cols(), original_colB = B.cols(); // for padding removal

		// pad the matrices before multiplying
		A.padBlockSize();
		B.padBlockSize();
		size_t rowA = A.rows(), colA_rowB = A.cols(), colB = B.cols();
		size_t iBlock = min(I_BLOCKSIZE, (int)rowA);
		size_t jBlock = min(J_BLOCKSIZE, (int)colA_rowB);
		size_t kBlock = min(K_BLOCKSIZE, (int)colB);

		scalar* tempB = new scalar[colA_rowB * colB], * originalB = B.data(), * originalA = A.data(), * result = new scalar[rowA * colB];
		size_t index = 0, vecsize = VECSIZE;
		const size_t unroll_1 = UNROLL_1, unroll_2 = UNROLL_2;
		typename scalar::vec sum[unroll_2][unroll_1], vecA[unroll_1], vecB[unroll_2];

		// Storing matrix B in tempB (in other order)
		for (size_t jj = 0; jj < colB; jj += jBlock)
			for (size_t kk = 0; kk < colA_rowB; kk += kBlock)
				for (size_t j = jj; j < jj + jBlock; j += unroll_2 * vecsize)
					for (size_t k = kk; k < kk + kBlock; ++k)
					{
						for (size_t x = 0; x < unroll_2; ++x)
						{
							vecB[x] = originalB + k * colB + j + x * vecsize;
							tempB[index + x * vecsize] = vecB[x];
						}
						index += unroll_2 * vecsize;
					}

		// matrix multiplication
		for (size_t ii = 0; ii < rowA; ii += iBlock)
			for (size_t jj = 0; jj < colB; jj += jBlock)
				for (size_t kk = 0; kk < colA_rowB; kk += kBlock)
					for (size_t i = ii; i < ii + iBlock; i += unroll_1)
						for (size_t j = jj; j < jj + jBlock; j += unroll_2 * vecsize)
						{
							index = (j - jj) * kBlock + kk * jBlock + jj * colA_rowB;

							if (kk == 0)
								for (size_t x = 0; x < unroll_1; ++x)
									for (size_t y = 0; y < unroll_2; ++y)
										sum[y][x] = scalar::vec();
							else
								for (size_t x = 0; x < unroll_1; ++x)
									for (size_t y = 0; y < unroll_2; ++y)
										sum[y][x] = result + (i + x) * colB + j + y * vecsize;

							for (size_t k = kk; k < kk + kBlock; ++k)
							{
								for (size_t x = 0; x < unroll_2; ++x)
									vecB[x] = tempB + index + x * vecsize;

								for (size_t x = 0; x < unroll_1; ++x)
								{
									vecA[x] = originalA[(i + x) * colA_rowB + k];
									for (size_t y = 0; y < unroll_2; ++y)
										sum[y][x] = sum[y][x].mul_add(vecA[x], vecB[y], sum[y][x]);
								}
								index += unroll_2 * vecsize;
							}

							for (size_t x = 0; x < unroll_1; ++x)
								for (size_t y = 0; y < unroll_2; ++y)
									result[(i + x) * colB + j + y * vecsize] = sum[y][x];
						}

		delete[] tempB;
		A.removePadding(original_rowA, original_colA_rowB);
		B.removePadding(original_colA_rowB, original_colB);
		this->_mat = result;
		this->removePadding(original_rowA, original_colB);
	}

	void naiveMult(Matrix&& A, Matrix& B)
	{
		size_t original_rowA = A.rows(), original_colA_rowB = A.cols(), original_colB = B.cols(); // for padding removal

		// pad the matrices before multiplying
		A.padBlockSize();
		B.padBlockSize();
		size_t rowA = A.rows(), colA_rowB = A.cols(), colB = B.cols();
		size_t iBlock = min(I_BLOCKSIZE, (int)rowA);
		size_t jBlock = min(J_BLOCKSIZE, (int)colA_rowB);
		size_t kBlock = min(K_BLOCKSIZE, (int)colB);

		scalar* tempB = new scalar[colA_rowB * colB], * originalB = B.data(), * originalA = A.data(), * result = new scalar[rowA * colB];
		size_t index = 0, vecsize = VECSIZE;
		const size_t unroll_1 = UNROLL_1, unroll_2 = UNROLL_2;
		typename scalar::vec sum[unroll_2][unroll_1], vecA[unroll_1], vecB[unroll_2];

		// Storing matrix B in tempB (in other order)
		for (size_t jj = 0; jj < colB; jj += jBlock)
			for (size_t kk = 0; kk < colA_rowB; kk += kBlock)
				for (size_t j = jj; j < jj + jBlock; j += unroll_2 * vecsize)
					for (size_t k = kk; k < kk + kBlock; ++k)
					{
						for (size_t x = 0; x < unroll_2; ++x)
						{
							vecB[x] = originalB + k * colB + j + x * vecsize;
							tempB[index + x * vecsize] = vecB[x];
						}
						index += unroll_2 * vecsize;
					}

		// matrix multiplication
		for (size_t ii = 0; ii < rowA; ii += iBlock)
			for (size_t jj = 0; jj < colB; jj += jBlock)
				for (size_t kk = 0; kk < colA_rowB; kk += kBlock)
					for (size_t i = ii; i < ii + iBlock; i += unroll_1)
						for (size_t j = jj; j < jj + jBlock; j += unroll_2 * vecsize)
						{
							index = (j - jj) * kBlock + kk * jBlock + jj * colA_rowB;

							if (kk == 0)
								for (size_t x = 0; x < unroll_1; ++x)
									for (size_t y = 0; y < unroll_2; ++y)
										sum[y][x] = scalar::vec();
							else
								for (size_t x = 0; x < unroll_1; ++x)
									for (size_t y = 0; y < unroll_2; ++y)
										sum[y][x] = result + (i + x) * colB + j + y * vecsize;

							for (size_t k = kk; k < kk + kBlock; ++k)
							{
								for (size_t x = 0; x < unroll_2; ++x)
									vecB[x] = tempB + index + x * vecsize;

								for (size_t x = 0; x < unroll_1; ++x)
								{
									vecA[x] = originalA[(i + x) * colA_rowB + k];
									for (size_t y = 0; y < unroll_2; ++y)
										sum[y][x] = sum[y][x].mul_add(vecA[x], vecB[y], sum[y][x]);
								}
								index += unroll_2 * vecsize;
							}

							for (size_t x = 0; x < unroll_1; ++x)
								for (size_t y = 0; y < unroll_2; ++y)
									result[(i + x) * colB + j + y * vecsize] = sum[y][x];
						}

		delete[] tempB;
		A.removePadding(original_rowA, original_colA_rowB);
		B.removePadding(original_colA_rowB, original_colB);
		this->_mat = result;
		this->removePadding(original_rowA, original_colB);
	}

	void naiveMult(Matrix&& A, Matrix&& B)
	{
		size_t original_rowA = A.rows(), original_colA_rowB = A.cols(), original_colB = B.cols(); // for padding removal

		// pad the matrices before multiplying
		A.padBlockSize();
		B.padBlockSize();
		size_t rowA = A.rows(), colA_rowB = A.cols(), colB = B.cols();
		size_t iBlock = min(I_BLOCKSIZE, (int)rowA);
		size_t jBlock = min(J_BLOCKSIZE, (int)colA_rowB);
		size_t kBlock = min(K_BLOCKSIZE, (int)colB);

		scalar* tempB = new scalar[colA_rowB * colB], * originalB = B.data(), * originalA = A.data(), * result = new scalar[rowA * colB];
		size_t index = 0, vecsize = VECSIZE;
		const size_t unroll_1 = UNROLL_1, unroll_2 = UNROLL_2;
		typename scalar::vec sum[unroll_2][unroll_1], vecA[unroll_1], vecB[unroll_2];

		// Storing matrix B in tempB (in other order)
		for (size_t jj = 0; jj < colB; jj += jBlock)
			for (size_t kk = 0; kk < colA_rowB; kk += kBlock)
				for (size_t j = jj; j < jj + jBlock; j += unroll_2 * vecsize)
					for (size_t k = kk; k < kk + kBlock; ++k)
					{
						for (size_t x = 0; x < unroll_2; ++x)
						{
							vecB[x] = originalB + k * colB + j + x * vecsize;
							tempB[index + x * vecsize] = vecB[x];
						}
						index += unroll_2 * vecsize;
					}

		// matrix multiplication
		for (size_t ii = 0; ii < rowA; ii += iBlock)
			for (size_t jj = 0; jj < colB; jj += jBlock)
				for (size_t kk = 0; kk < colA_rowB; kk += kBlock)
					for (size_t i = ii; i < ii + iBlock; i += unroll_1)
						for (size_t j = jj; j < jj + jBlock; j += unroll_2 * vecsize)
						{
							index = (j - jj) * kBlock + kk * jBlock + jj * colA_rowB;

							if (kk == 0)
								for (size_t x = 0; x < unroll_1; ++x)
									for (size_t y = 0; y < unroll_2; ++y)
										sum[y][x] = scalar::vec();
							else
								for (size_t x = 0; x < unroll_1; ++x)
									for (size_t y = 0; y < unroll_2; ++y)
										sum[y][x] = result + (i + x) * colB + j + y * vecsize;

							for (size_t k = kk; k < kk + kBlock; ++k)
							{
								for (size_t x = 0; x < unroll_2; ++x)
									vecB[x] = tempB + index + x * vecsize;

								for (size_t x = 0; x < unroll_1; ++x)
								{
									vecA[x] = originalA[(i + x) * colA_rowB + k];
									for (size_t y = 0; y < unroll_2; ++y)
										sum[y][x] = sum[y][x].mul_add(vecA[x], vecB[y], sum[y][x]);
								}
								index += unroll_2 * vecsize;
							}

							for (size_t x = 0; x < unroll_1; ++x)
								for (size_t y = 0; y < unroll_2; ++y)
									result[(i + x) * colB + j + y * vecsize] = sum[y][x];
						}

		delete[] tempB;
		A.removePadding(original_rowA, original_colA_rowB);
		B.removePadding(original_colA_rowB, original_colB);
		this->_mat = result;
		this->removePadding(original_rowA, original_colB);
	}
	/* Naive Multiplication - END */
};

#endif // !Matrix_Class