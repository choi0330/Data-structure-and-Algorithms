// One possible solution: partition the left matrix into no_threads horizontal blocks:
#include <chrono>
#include <iostream>
#include <random>

#include <cassert>
#include "matrix.h"

void randomize(Matrix& m) {
	std::random_device rd;  //Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> uniform_dist(0, 10);
	for (size_t r = 0; r < m.Rows(); ++r) {
		for (size_t c = 0; c < m.Cols(); ++c) {
			m(r, c) = uniform_dist(gen);
		}
	}
}

// for submitting your solution, this code needs be unaltered
void test() {
	std::cout << "size (#rows=#cols) ? ";
	size_t sz = 0;
	std::cin >> sz;
	size_t no_threads = 0;
	std::cout << "#threads ? ";
	std::cin >> no_threads;
	Matrix L(sz, sz);
	Matrix R(sz, sz);
	randomize(L);
	randomize(R);

	auto start = std::chrono::high_resolution_clock::now();
	Matrix result = multiply(L, R, no_threads);
	auto finish = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = finish - start;
	std::cout << "Elapsed time: " << elapsed.count() << " s\n";

	if (sz <= 16) {
		std::cout << L;
		std::cout << R;
		std::cout << result;
	}
	assert(result == L * R); // do not remove this!
}

// use this code when submitting or testing
int main() {
	test();
}