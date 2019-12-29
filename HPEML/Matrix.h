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
	Matrix(Matrix&& M) : Memory_Block<scalar, Matrix<scalar>>::Memory_Block(M) {}
	Matrix(Matrix M[4]) : Memory_Block<scalar, Matrix<scalar>>::Memory_Block(M) {} // collect 4 blocks into 1 big matrix


	// assignment operators
	inline Matrix& operator = (const Matrix& M) { return Memory_Block<scalar, Matrix<scalar>>::operator = (M); }
	inline Matrix& operator = (Matrix& M) { return Memory_Block<scalar, Matrix<scalar>>::operator = (M); }
	inline Matrix& operator = (Matrix&& M) { return Memory_Block<scalar, Matrix<scalar>>::operator = (M); }
	inline Matrix& operator = (vector<vector<scalar>>& vec_vecs);
	inline Matrix& operator = (vector<vector<scalar>>&& vec_vecs);


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

	// product with transpose
	friend Matrix product(Matrix&& A, char mode_a, Matrix&& B, char mode_b); // 4 times

	// Element-wise product
	friend Matrix dot_product(Matrix&& a, Matrix&& b); //4 times

	Matrix trans(bool inplace);
	Matrix conj(bool inplace);
	Matrix diag();

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

	void removePadding(size_t row, size_t col) // resize the matrix into rowXcol
	{
		if (row == this->_row && col == this->_col) // no need to unpadd
			return;

		size_t i, j, vecsize = VECSIZE, originalRow = this->_row, originalCol = this->_col;
		scalar* matrix = new scalar[row * col], * originalMatrix = this->_mat;

		if (col >= vecsize)
		{
			for (i = 0; i < row; ++i)
				for (j = 0; j < col - vecsize; j += vecsize)
					matrix[i * col + j] = scalar::vec(originalMatrix + i * originalCol + j);

			for (; j < col; ++j)
				matrix[i * col + j] = originalMatrix[i * originalCol + j];
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
	Matrix naiveMult(Matrix& A, Matrix& B)
	{
		size_t rowA = A.rows(), colA_rowB = A.cols(), colB = B.cols();
		scalar* result = new scalar[rowA * colB];
		size_t iBlock = min(I_BLOCKSIZE, (int)rowA);
		size_t jBlock = min(J_BLOCKSIZE, (int)colA_rowB);
		size_t kBlock = min(K_BLOCKSIZE, (int)colB);

		scalar* tempB = new scalar[colA_rowB * colB], * originalB = B.data(), * originalA = A.data();
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
										sum[y][x] = typename scalar::vec();
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
										sum[y][x] = typename scalar::vec::mul_add(vecA[x], vecB[y], sum[y][x]);
								}
								index += unroll_2 * vecsize;
							}

							for (size_t x = 0; x < unroll_1; x++)
								for (size_t y = 0; y < unroll_2; y++)
									result[(i + x) * colB + j + y * vecsize] = sum[y][x];
						}

		delete[] tempB;
		return Matrix(rowA, colB, result);
	}

	Matrix naiveMult(Matrix& A, Matrix&& B)
	{
		size_t rowA = A.rows(), colA_rowB = A.cols(), colB = B.cols();
		scalar* result = new scalar[rowA * colB];
		size_t iBlock = min(I_BLOCKSIZE, (int)rowA);
		size_t jBlock = min(J_BLOCKSIZE, (int)colA_rowB);
		size_t kBlock = min(K_BLOCKSIZE, (int)colB);

		scalar* tempB = new scalar[colA_rowB * colB], * originalB = B.data(), * originalA = A.data();
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
										sum[y][x] = typename scalar::vec();
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
										sum[y][x] = typename scalar::vec.mul_add(vecA[x], vecB[y], sum[y][x]);
								}
								index += unroll_2 * vecsize;
							}

							for (size_t x = 0; x < unroll_1; x++)
								for (size_t y = 0; y < unroll_2; y++)
									result[(i + x) * colB + j + y * vecsize] = sum[y][x];
						}

		delete[] tempB;
		return Matrix(rowA, colB, result);
	}

	Matrix naiveMult(Matrix&& A, Matrix& B)
	{
		size_t rowA = A.rows(), colA_rowB = A.cols(), colB = B.cols();
		scalar* result = new scalar[rowA * colB];
		size_t iBlock = min(I_BLOCKSIZE, (int)rowA);
		size_t jBlock = min(J_BLOCKSIZE, (int)colA_rowB);
		size_t kBlock = min(K_BLOCKSIZE, (int)colB);

		scalar* tempB = new scalar[colA_rowB * colB], * originalB = B.data(), * originalA = A.data();
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
										sum[y][x] = typename scalar::vec();
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
										sum[y][x] = typename scalar::vec.mul_add(vecA[x], vecB[y], sum[y][x]);
								}
								index += unroll_2 * vecsize;
							}

							for (size_t x = 0; x < unroll_1; x++)
								for (size_t y = 0; y < unroll_2; y++)
									result[(i + x) * colB + j + y * vecsize] = sum[y][x];
						}

		delete[] tempB;
		return Matrix(rowA, colB, result);
	}

	Matrix naiveMult(Matrix&& A, Matrix&& B)
	{
		size_t rowA = A.rows(), colA_rowB = A.cols(), colB = B.cols();
		scalar* result = new scalar[rowA * colB];
		size_t iBlock = min(I_BLOCKSIZE, (int)rowA);
		size_t jBlock = min(J_BLOCKSIZE, (int)colA_rowB);
		size_t kBlock = min(K_BLOCKSIZE, (int)colB);

		scalar* tempB = new scalar[colA_rowB * colB], * originalB = B.data(), * originalA = A.data();
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
										sum[y][x] = typename scalar::vec();
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
										sum[y][x] = typename scalar::vec.mul_add(vecA[x], vecB[y], sum[y][x]);
								}
								index += unroll_2 * vecsize;
							}

							for (size_t x = 0; x < unroll_1; x++)
								for (size_t y = 0; y < unroll_2; y++)
									result[(i + x) * colB + j + y * vecsize] = sum[y][x];
						}

		delete[] tempB;
		return Matrix(rowA, colB, result);
	}
	/* Naive Multiplication - END */
};

#endif // !Matrix_Class