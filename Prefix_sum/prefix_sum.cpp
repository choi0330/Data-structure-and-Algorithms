#include <iostream>
#include <vector>

using namespace std;

class PrefixSum
{
private:
	std::vector<std::vector<int> > mat;

public:
	PrefixSum(const std::vector<std::vector<int> >& a)
	{
		mat = a;
	}

	// pre: 0 <= x0 <= x1 < n and 0 <= y0 <= y1 < m
	int sum(unsigned x0, unsigned x1, unsigned y0, unsigned y1)
	{
		int sum = 0;
		for (unsigned i = x0; i <= x1; i++)
			for (unsigned j = y0; j <= y1; j++)
				sum += mat[i][j];

		return sum;
	}
};


int main()
{
	unsigned n, m, x0, x1, y0, y1;

	std::cin >> n;
	std::cin >> m;

	std::vector<std::vector<int> > a(n, std::vector<int>(m));

	for (unsigned i = 0; i < n; ++i)
		for (unsigned j = 0; j < m; ++j)
			std::cin >> a[i][j];

	std::cin >> x0;
	std::cin >> x1;
	std::cin >> y0;
	std::cin >> y1;

	PrefixSum prefixSum(a);

	std::cout << prefixSum.sum(x0, x1, y0, y1) << std::endl;
	return 0;
}