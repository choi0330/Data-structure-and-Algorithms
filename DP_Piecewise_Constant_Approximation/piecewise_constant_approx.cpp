#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip> // for setprecision
#include <cassert>
#include <algorithm>
#include <random>
#include "images.h"

// helper function for showVectors
// please do not change
int scale(double x, int max) {
	return (int)(max * (x + 0.1) / 1.2);
}
// show the vectors (data and reconstruction) in graphical form
// please do not change
void showVectors(const std::vector<double>& data, const std::vector<double>& result) {
	Image img(256, 128);
	double minr = *std::min_element(std::begin(result), std::end(result));
	double maxr = *std::max_element(std::begin(result), std::end(result));
	double mind = *std::min_element(std::begin(data), std::end(data));
	double maxd = *std::max_element(std::begin(data), std::end(data));
	double min = std::min(minr, mind);
	double max = std::max(maxr, maxd);
	unsigned length = result.size();
	int dotsize = 3;
	if (length > 256)
		dotsize = 0;
	else if (length > 64)
		dotsize = 1;
	else if (length > 16)
		dotsize = 2;
	int xp = scale(0 / (double)(length - 1), 256);
	int yp = scale(1 - (result[0] - min) / (max - min), 128);
	img.Ellipse(Red, xp, yp, dotsize, dotsize);
	for (unsigned int i = 0; i < length; ++i) {
		int x = scale(i / (double)(length - 1), 256);
		int y = scale(1 - (result[i] - min) / (max - min), 128);
		if (yp == y) {
			img.Line(Red, xp, yp, x, y);
		}
		else {
			img.Ellipse(Red, xp, yp, dotsize, dotsize);
			img.Ellipse(Red, x, y, dotsize, dotsize);
		}
		yp = y;
		xp = x;
		y = scale(1 - (data[i] - min) / (max - min), 128);
		img.Line(Yellow, x - dotsize, y - dotsize, x + dotsize, y + dotsize);
		img.Line(Yellow, x - dotsize, y + dotsize, x + dotsize, y - dotsize);
	}
	img.Ellipse(Red, xp, yp, dotsize, dotsize);
}


// output a vector
template <typename datatype>
void out(std::vector<datatype> v) {
	for (auto x = v.begin(); x != v.end(); ++x) {
		std::cout << *x;
		if (x + 1 != v.end()) std::cout << " ";
	}
	std::cout << "\n";
}

// helper function to compute a prefix sum array
// no need to change this
template <typename function>
std::vector<double> sum_vector(unsigned int sz, function f) {
	std::vector<double> vec(sz + 1);
	double sum = 0;
	for (unsigned int i = 0; i < sz; ++i) {
		vec[i] = sum;
		sum += f(i);
	}
	vec[sz] = sum;
	return vec;
}

// helper function to retreive from prefix sum array
// pre: 0 <= from < to <= sum.size()
// we consider interval [from,to)
// no need to change this
double getsum(const std::vector<double>& sum, unsigned int from, unsigned int to) {
	return sum[to] - sum[from];
}

// helper function to fill vector interval
// pre: 0 <= from < to <= vec.size()
// we consider interval [from,to)
// no need to change this
void fill(std::vector<double>& vec, double value, unsigned int from, unsigned int to) {
	std::fill(vec.begin() + from, vec.begin() + to, value);
}

// the Statistics class is a container that can be used to quickly retreive
// the mean value and the sum of squared error values on intervals
// parts remain to be implemented
class Statistics {
	unsigned int n;
	std::vector<double> sum;
	std::vector<double> ssq;
public:
	Statistics(const std::vector<double>& data) : n{ (unsigned int)data.size() }
	{
		sum = sum_vector(n, [&](int i) {return data[i]; });
		ssq = sum_vector(n, [&](int i) {return data[i] * data[i]; });
	};


	// pre: 0 <= from < to <= n;
	// post: return mean of data[from,to)
	double mean(unsigned int from, unsigned int to) const {
		// ! implement this !
		double avg = getsum(sum, from, to) / (to - from);
		return avg;
	}

	// pre: 0 <= from <to <= n;
	// post: return err of constant approximation in interval [from,to)
	double err(unsigned int from, unsigned int to) const {
		// ! implement this !
		double avg = mean(from, to);
		double error = getsum(ssq, from, to) - 2 * avg*getsum(sum, from, to) + avg * avg*(to - from);
		return error;
	}

	int size() const {
		return n;
	}
};



// the minimization 
// implement it
double MinimizeH(double gamma, const Statistics& s, std::vector<double>& result) {
	int n = s.size();

	// define the DP tables
	std::vector<std::vector<double>> table(n+1);
	std::vector<double> table2;
	
	// fill the DP tables
	table[0].push_back(0);
	table2.push_back(0);

	for (int i = 1; i <= n; i++)
	{
		double min = 100000;
		int new_split;
		for (int j = 0; j < i; j++)
		{
			
			if (min > table2[j] + gamma + s.err(j, i))
			{
				min = table2[j] + gamma + s.err(j, i);
				new_split = j;
			}
			
		}
		table[i] = table[new_split];
		table[i].push_back(i);
		table2.push_back(min);
	}

	//// read out result from the tables and fill result vector accordingly
	for (auto index = table[n].begin(); index != table[n].end() - 1; index++)
	{
		fill(result, s.mean(*index, *(index + 1)), *index, *(index + 1));
	}

	//// return the minimal value of H(gamma, data)
	return table2[n];
}

// main function, use this unaltered function for your final submission
int main() {
	std::cout << std::setprecision(3); // don't remove, relevant for output grading
	std::srand(std::clock()); // use system clock, required for image output don't remove

	// input format:
	// Input = gamma:double Data
	// Data = "data" {data:real} "end" | "random" length:int.

	// input gamma
	double gamma;
	std::cin >> gamma;

	// input data
	std::vector<double> data;
	std::string type;
	std::cin >> type;

	if (type == "random") {
		std::mt19937 gen(7);
		std::uniform_real_distribution<> dis;
		unsigned length;
		std::cin >> length;
		double stepvalue = 0.5;
		for (unsigned i = 0; i < length; ++i) {
			if (dis(gen) < 10.0 / length) {
				stepvalue = dis(gen);
			}
			data.push_back(stepvalue + 0.1*dis(gen));
		}
	}
	else if (type == "sin") {
		unsigned length;
		std::cin >> length;
		for (unsigned i = 0; i < length; ++i) {
			data.push_back(std::sin(i*std::atan(1) * 8 / length));
		}
	}
	else {
		// input data vector
		double value;
		while (std::cin >> value) {
			data.push_back(value);
		}
	}
	std::vector<double> result = data;

	// preparation for fast mean / err computation
	Statistics stat(data);
	// minimize (and output result)
	std::cout << MinimizeH(gamma, stat, result) << std::endl;

	// for debugging purposes
	// out(result);
	// graphical output
	showVectors(data, result);
}