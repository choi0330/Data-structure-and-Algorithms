#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;

unsigned Levenshtein(const std::string& x, const std::string& y) {
	// implement me
	int m = x.length() + 1;
	int n = y.length() + 1;
	
	vector<vector<int>> table(m);
	
	for (int i = 0; i < m; i++) table[i].resize(n);
	for (int i = 0; i < n; i++) table[0][i] = i;
	for (int i = 1; i < m; i++) table[i][0] = i;

	for(int i = 1; i < m; i++)
		for (int j = 1; j < n; j++)
		{
			int del = 0;
			if (x[i-1] == y[j-1]) del = 1;
			else if ((x[i] == 'c' || x[i] == 'd') && (y[j] == 'c' || y[j] == 'd')) del = 1;
			else del = 0;

			table[i][j] = std::min({ table[i - 1][j] + 1, table[i][j - 1] + 1, table[i - 1][j - 1] + 1 - del });
		}

	return (unsigned)table[m-1][n-1];
}


// use an unaltered version of main() for submissions and testing
int main() {
	std::string name;
	std::cin >> name;
	std::ifstream dict("./dictionary.txt");
	unsigned int min = name.size() + 1;
	std::string best;
	std::string n;
	while (dict >> n) {
		unsigned dist = Levenshtein(name, n);
		if (dist < min) {
			min = dist;
			best = n;
		}
	}
	std::cout << "best match:" << best;
	std::cout << " (" << min << ")";
}