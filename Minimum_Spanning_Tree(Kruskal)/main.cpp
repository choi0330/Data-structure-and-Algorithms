#include <iostream>
#include <vector>
#include <algorithm>

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
		if (p[index - 1] == index)
			return index;
		else
			find(p[index - 1]);
	}

	void unite(size_t a, size_t b)
	{
		size_t p_a = find(a);
		size_t p_b = find(b);

		size_t g_a = 0, g_b = 0;

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

class edge {
public:
	

	edge(size_t u, size_t v, unsigned c) : from{ u }, to{ v }, cost{ c }
	{};

	unsigned value() const
	{
		return cost;
	}

	size_t node_from()
	{
		return from;
	}

	size_t node_to()
	{
		return to;
	}

private:
	size_t from;
	size_t to;
	unsigned cost;
};

bool operator<(edge const& a, edge const& b)
{
	return a.value() < b.value();
}

int main()
{
	std::size_t n, m;
	std::cin >> n >> m;
	// TODO: Initialize graph
	UnionFind uf(n);
	vector<edge> e;
	vector<edge> cycle_free;

	for (std::size_t i = 0; i < m; i++)
	{
		// Read edges
		std::size_t u, v;
		int c;
		std::cin >> u >> v >> c;
		edge temp_e(u, v, c);
		e.push_back(temp_e);
		// TODO: add edge from u to v with weight c to the graph.
		
	}

	int cost = 0;
	// Perform Kruskals algorithm and calculate the cost
	sort(e.begin(), e.end());
	for (unsigned i = 0; i < m; i++)
	{
		if (uf.find(e[i].node_from()) == uf.find(e[i].node_to())) continue;
		else {
			uf.unite(e[i].node_from(), e[i].node_to());
			cycle_free.push_back(e[i]);
		}
		if (cycle_free.size() == n - 1) break;
	}
	for (auto e : cycle_free)
	{
		cost += e.value();
	}

	std::cout << cost << std::endl;

	return 0;
}
