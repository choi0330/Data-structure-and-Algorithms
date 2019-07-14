#pragma once
#include<vector>
#include <thread>
#include <vector>

class Matrix {
	std::vector<int> data;
	size_t rows;
	size_t cols;
public:
	Matrix(size_t r, size_t c) :data(r*c), rows(r), cols(c) {
	}

	size_t Rows() const {
		return rows;
	}

	size_t Cols() const {
		return cols;
	}

	void randomize() {
		std::random_device rd;  //Will be used to obtain a seed for the random number engine
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> uniform_dist(0, 10);
		for (size_t pos = 0; pos < rows*cols; ++pos) {
			data[pos] = uniform_dist(gen);
		}
	}

	int& operator()(size_t r, size_t c) {
		assert(r < rows && c < cols);
		return data[r*rows + c];
	}

	int operator()(size_t r, size_t c) const {
		assert(r < rows && c < cols);
		return data[r*rows + c];
	}

	bool operator==(const Matrix x) const {
		if (rows != x.rows || cols != x.cols) {
			return false;
		}
		return data == x.data;
	}
};

std::ostream& operator<<(std::ostream& o, const Matrix& m) {
	for (size_t r = 0; r < m.Rows(); ++r) {
		for (size_t c = 0; c < m.Cols(); ++c) {
			o << m(r, c) << " ";
		}
		o << std::endl;
	}
	o << std::endl;
	return o;
}

// block-multiply of blocks of two matrices
void MMBlock(Matrix& result, const Matrix& left, size_t rowLow, size_t rowHigh, const Matrix& right, size_t colLow, size_t colHigh, size_t innerLow, size_t innerHigh) {
	assert(left.Cols() == right.Rows());
	assert(rowLow <= rowHigh && rowHigh <= left.Rows());
	assert(colLow <= colHigh && colHigh <= right.Cols());
	assert(innerLow <= innerHigh && innerHigh <= right.Rows());
	for (size_t r = rowLow; r < rowHigh; ++r) {
		for (size_t c = colLow; c < colHigh; ++c) {
			int sum = result(r, c);
			for (size_t x = innerLow; x < innerHigh; ++x) {
				sum += left(r, x)*right(x, c);
			}
			result(r, c) = sum;
		}
	}
}

// multiply two matrices (single-threaded)
// please do not change this code
Matrix operator*(const Matrix& left, const Matrix& right) {
	Matrix result{ left.Rows(), right.Cols() };
	assert(left.Cols() == right.Rows());
	MMBlock(result, left, 0, left.Rows(), right, 0, right.Cols(), 0, left.Cols());
	return result;
}

Matrix multiply(const Matrix& left, const Matrix& right, size_t num_threads) {

	Matrix result{ left.Rows(), right.Cols() };

	// do the concurrent computation here
	// num_threads = 0 --> create no thread and do MM here
	
	if (num_threads == 0) MMBlock(result, left, 0, left.Rows(),	right, 0, right.Cols(),	0, left.Cols());
	// num_threads > 0 --> create num_threads threads and do MM in the spawned threads
	else
	{
		std::vector<std::thread> threads(num_threads);
		std::vector<unsigned> start_row(num_threads);
		std::vector<unsigned> end_row(num_threads);
		std::vector<unsigned> start_col(num_threads, 0);
		std::vector<unsigned> end_col(num_threads, left.Cols());

		int incre = left.Rows() / num_threads;
		start_row[0] = 0;
		end_row[0] = incre;
		if (num_threads > 1)
		{
			for (unsigned i = 1; i < num_threads - 1; i++)
			{
				start_row[i] = end_row[i - 1];
				end_row[i] = start_row[i] + incre;
			}
			start_row[num_threads - 1] = end_row[num_threads - 2];
			end_row[num_threads - 1] = left.Rows();
		}

		for (unsigned i = 0; i < num_threads; i++) 
			threads[i] = std::thread(MMBlock, std::ref(result), std::ref(left), start_row[i], end_row[i], std::ref(right), 0, right.Cols(), start_col[i], end_col[i]);

		for (auto & thread : threads) thread.join();
	}
	return result;
}
