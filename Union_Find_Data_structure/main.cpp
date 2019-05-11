#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

class UnionFind {

public:
	UnionFind(size_t size) 
	{
		for (size_t i = 1; i <= size; i++)
			p.push_back(i);
	};

	size_t find(size_t index)
	{
		if (p[index-1] == index)
			return index;
		else
			find(p[index-1]);
	}

	void unite(size_t a, size_t b)
	{
		size_t p_a = find(a);
		size_t p_b = find(b);

		size_t g_a = 0 , g_b = 0;

		if (p_a == p_b) return;
		else
		{
			for (size_t i = 0; i < p.size(); i++)
			{
				if (p[i] == p_a)
					g_a++;
				else if (p[i] == p_b)
					g_b++;
			}
			if (g_a >= g_b)
			{
				p[b - 1] = p_a;
				return;
			}
			else
			{
				p[a - 1] = p_b;
				return;
			}
		}
	}
private:
	vector<size_t> p;
};


int main()
{
	size_t n, i, j;
	std::cin >> n >> i >> j;
	UnionFind uf(n);
	// Read i unite operations
	for (size_t x = 0; x < i; x++)
	{
		size_t a, b;
		std::cin >> a >> b;
		uf.unite(a, b);
	}

	// Read and process j queries
	for (size_t x = 0; x < j; x++)
	{
		size_t a, b;
		std::cin >> a >> b;

		if (uf.find(a) == uf.find(b))
		{
			std::cout << "true ";
		}
		else
		{
			std::cout << "false ";
		}
	}
	std::cout << std::endl;

	return 0;
}
