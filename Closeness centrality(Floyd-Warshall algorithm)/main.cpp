#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <cassert>
#include <sstream>
constexpr auto INF = 10000;
using namespace std;

template<typename Matrix>
void allPairsShortestPaths(unsigned n, Matrix& m)
{
	// TODO: add code for Floyd-Warshall algorithm here
	//vector<Matrix> d(n);
	Matrix d = m;

	for (unsigned i = 0; i < n; i++)
	{
		for (unsigned j = 0; j < n; j++)
		{
			if (i != j && d[i][j] == 0)
				d[i][j] = INF;
		}
	}
	// Find shortest path using matrix 'a' and write the corresponding length at the matrix 'm'.
	for (unsigned k = 0; k < n; k++)
	{
		for (unsigned i = 0; i < n; i++)
		{
			for (unsigned j = 0; j < n; j++)
			{
				if (d[i][k] + d[k][j] < d[i][j])
					d[i][j] = d[i][k] + d[k][j];
			}
		}
	}
	m = d;
}

int main()
{
	unsigned n = 0;
	ifstream input("./input.txt");
	char buffer[41];
	buffer[40] = '\0';

	for (unsigned i = 0; i < 21; ++i)
		input.ignore(numeric_limits<streamsize>::max(), '\n');

	input >> n;

	cout << "vertices: " << n << endl;

	vector<vector<unsigned> > adjacencies(n, vector<unsigned>(n, 0));
	vector<string> names(n);

	// transform input data into an adjacency list
	for (unsigned i = 0; i < n; ++i)
	{
		unsigned index, degree, dummy;
		input >> index >> degree >> dummy;
		assert(i + 1 == index);
		while (input.peek() == ' ')
			input.get();
		input.read(buffer, 40);
		names[i] = buffer;
		for (unsigned j = 0; j < degree; ++j)
		{
			unsigned neighbor;
			input >> neighbor;
			adjacencies[i][neighbor - 1] = 1;
			// we are dealing with an undirected graph ...
			adjacencies[neighbor - 1][i] = 1;
		}
	}
	
	allPairsShortestPaths(n, adjacencies);

	for (unsigned i = 0; i < n; ++i)
	{
		cout << names[i] << ": ";
		unsigned centrality = 0;

		// TODO: compute centrality of vertex i here
		for (unsigned j = 0; j < n; j++)
		{
			if (j != i && adjacencies[i][j] != INF) centrality += adjacencies[i][j];
		}
		cout << centrality << endl;
	}

	return 0;
}
