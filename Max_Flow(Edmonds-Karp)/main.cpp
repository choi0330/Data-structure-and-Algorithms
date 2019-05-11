#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <set>

using namespace std;

// basic implementation of a directed graph data structure that is actually
// an adjacency list
template<typename C>
class DiGraph
{
private:
	size_t n_;
	std::vector<std::vector<C> > capacities_;
	std::vector<std::vector<C> > current_values_;


public:
	DiGraph(size_t n) : n_(n), capacities_(n, std::vector<C>(n, C())),
		current_values_(n, std::vector<C>(n, C()))
	{

	}

	void setEdge(size_t a, size_t b, C capacity)
	{
		capacities_[a][b] = capacity;
	}

	C getEdge(size_t a, size_t b) const
	{
		return capacities_[a][b];
	}

	void setValue(size_t a, size_t b, C value)
	{
		current_values_[a][b] = value;
	}

	C getValue(size_t a, size_t b) const
	{
		return current_values_[a][b];
	}

	size_t size() const
	{
		return n_;
	}
};

template<typename T>
void printGraph(const DiGraph<int>& g, T& stream)
{
	size_t n = g.size();

	for (size_t a = 0; a < n; ++a)
	{
		for (size_t b = 0; b < n; ++b)
		{
			if (g.getEdge(a, b) > 0)
			{
				stream << a << " " << b << ": " << g.getValue(a, b) << std::endl;
			}
		}
	}
}

template<typename C>
struct graph_information
{
	vector<C> distance;
	vector<size_t> path;
};

template<typename C>
graph_information<C> Dijkstra(DiGraph<C>& g, size_t node)
{
	size_t n = g.size();
	set<size_t> OPEN;
	vector<C> distance;
	vector<size_t> parent(n);
	deque<size_t> path;
	size_t source = 0;
	C INF = 100000;

	for (unsigned i = 0; i < n; i++)
	{
		parent.push_back(i);
	}

	OPEN.insert(source);

	for (unsigned i = 0; i < n; i++)
	{
		if (i == source) distance.push_back(0);
		else distance.push_back(INF);
	}

	while (OPEN.size() != 0)
	{
		// Dijkstra's way
		C min = distance[*OPEN.begin()];
		size_t min_ind = *OPEN.begin();
		for (auto e : OPEN)
		{
			if (distance[e] < min)
			{
				min = distance[e];
				min_ind = e;
			}
		}

		for (unsigned i = 0; i < n; i++)
		{
			if (g.getValue(min_ind, i) != 0)
			{
				if (distance[min_ind] + g.getValue(min_ind, i) < distance[i] && distance[min_ind] + g.getValue(min_ind, i) < distance[node])
				{
					distance[i] = distance[min_ind] + g.getValue(min_ind, i);
					if (i != node) OPEN.insert(i);
					parent[i] = min_ind;
				}
			}
		}

		OPEN.erase(OPEN.find(min_ind));
	}

	size_t index = node;

	while (index != source)
	{
		path.push_front(index);
		index = parent[index];
	}
	path.push_front(source);

	vector<size_t> real_path;
	for (unsigned i = 0; i < path.size(); i++)
	{
		real_path.push_back(path[i]);
	}


	graph_information<C> a;
	a.distance = distance;
	a.path = real_path;

	return a;
}

template<typename C>
bool getPath(DiGraph<C>& g, std::vector<size_t>& path)
{
	size_t n = g.size();
	size_t sink = n - 1;
	C INF = 100000;

	graph_information<C> result = Dijkstra<C>(g, sink);

	path.clear();
	vector<C> distance = result.distance;
	if (distance[sink] == INF) return false;
	else
	{
		path = result.path;
		return true;
	}
}

template<typename C>
void maxFlow(DiGraph<C>& g)
{
	std::vector<size_t> path;

	while (getPath(g, path))
	{
		// TODO: change the flow using the augmenting path according to the
		// Edmonds-Karp algorithm
		C min_edge = g.getValue(path[0], path[1]);
		for (unsigned i = 1; i < path.size() - 1; i++)
		{
			C current_edge = g.getValue(path[i], path[i + 1]);
			if (current_edge < min_edge)
			{
				min_edge = g.getValue(path[i], path[i + 1]);
			}
		}
		for (unsigned i = 0; i < path.size() - 1; i++)
		{
			g.setValue(path[i], path[i + 1], g.getValue(path[i], path[i + 1]) - min_edge);
			g.setValue(path[i + 1], path[i], g.getValue(path[i + 1], path[i]) + min_edge);
		}
	}

	return;
}

int main()
{
	size_t n = 0, m = 0;
	std::cin >> n >> m;

	DiGraph<int> g(n);

	for (size_t i = 0; i < m; ++i)
	{
		size_t a, b;
		int capacity;
		std::cin >> a >> b >> capacity;
		if (a >= n || b >= n)
		{
			std::cerr << "Edge indices out of bound." << std::endl;
			exit(EXIT_FAILURE);
		}
		g.setEdge(a, b, capacity);
		g.setValue(a, b, capacity);
	}

	// computing flow

	maxFlow(g);

	// you may use the following for debugging
	//printGraph(g, std::cout);

	// we compute the flow reaching the sink n-1
	int out_flow = 0;
	for (unsigned i = 0; i < n - 1; ++i)
	{
		//TODO: calculate the out_flow from DiGraph g
		out_flow += g.getValue(n-1, i);
	}
	std::cout << out_flow << std::endl;

	return 0;
}

