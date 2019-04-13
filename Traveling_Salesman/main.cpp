#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <assert.h>
#include <sstream>

using namespace std;

const int kMaxN = 10;
const double kInf = 1e9;
const double kEps = 1e-7;

struct City {
	std::string name;
	int x, y;
};

using Cities = std::vector<City>;

bool operator<(const City &a, const City &b) {
	return a.name < b.name;
}

// helper function to inpt the cities
Cities input() {
	Cities cities;
	unsigned N;
	std::cin >> N;
	for (unsigned i = 0; i < N; ++i) {
		City c;
		std::cin >> c.name >> c.x >> c.y;
		cities.push_back(c);
		if (i > 0) assert(cities[i - 1].name < c.name);
	}
	return cities;
}

// helper function to compute the square of an int
inline int sqr(int d) {
	return d * d;
}

// helper function to compute the distance between two cities
inline double dist(const Cities& cities, int i, int j) {
	return std::sqrt(sqr(cities[i].x - cities[j].x) + sqr(cities[i].y - cities[j].y));
}


int main() {
	Cities cities = input();
	int N = cities.size();
	
	// DP table
	vector<vector<double>> D(pow(2, N-1));
	vector<vector<Cities>> L(pow(2, N-1));
	for (int i = 0; i < pow(2, N - 1); i++)
	{
		D[i].resize(N - 1);
		L[i].resize(N - 1);
		for (int j = 0; j < N - 1; j++)
			L[i][j].push_back(cities[0]);
	}

	// Base cases 	// Calculation order
	for (int i = 0; i < N - 1; i++)
	{
		D[0][i] = 0;
	}

	// Computing entries
	/// size of x = 1
	for (int x = 1; x <= pow(2, N - 2); x*=2)
	{
		int i = log2(x); // x is subset of cities { 2, 3, ... , N }.
		D[x][i] = dist(cities, 0, i + 1);
		L[x][i].push_back(cities[i + 1]);
	}

	/// size of x != 1
	for (int x = 0; x < (1 << (N - 1)); x++)
	{
		for (int j = 2; j <= N - 1; j++)
		{
			int x_size = 0;
			for (int i = 0; i < N-1; i++)
			{
				if (x & (1 << i)) x_size += 1;
			}
			if (x_size == j)
			{
				for (int k = 0; k < N - 1; k++)
				{
					if (x & (1 << k))
					{
						double min_dist = 1000000;
						int min_ind = 0;
						for (int l = 0; l < N - 1; l++)
						{
							if (x & (1 << l) && k != l)
							{
								if (min_dist > D[x ^ (1 << k)][l] + dist(cities, l + 1, k + 1))
								{
									min_dist = D[x ^ (1 << k)][l] + dist(cities, l + 1, k + 1);
									min_ind = l;
								}
							}
						}
						D[x][k] = min_dist;
						L[x][k] = L[x ^ (1 << k)][min_ind];
						L[x][k].push_back(cities[k + 1]);
					}
				}
									
			}
		}
	}

	// How to extract the solution
	double min = 1000000;   // compute the shortest distance here
	int min_index = 0;
	for (int i = 0; i < N - 1; i++)
	{
		if (min > D[pow(2, N - 1) - 1][i])
		{
			min = D[pow(2, N - 1) - 1][i];
			min_index = i;
		}
		// In case of multiple optimal sols, choose the one ends with lexicographically higher name.
		else if (min == D[pow(2, N - 1) - 1][i])
		{
			if (L[pow(2, N - 1) - 1][min_index].back().name < L[pow(2, N - 1) - 1][i].back().name)
			{
				min_index = i;
			}
		}
	}

	std::cout << min << std::endl;
	// and output the path
	for (auto e : L[pow(2, N - 1) - 1][min_index])
	{
		std::cout << e.name << " ";
	}
	std::cout << std::endl;
}