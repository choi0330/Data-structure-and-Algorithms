#include "data.h"
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

class Selector
{
	using Iterator = std::vector<int>::iterator;
public:
	std::vector<int> v;


public:
	Selector(const std::vector<int>& a) : v(a)
	{}

	size_t size()
	{
		return v.size();
	}

	//int randompivot(Iterator& l, Iterator& r)
	//{
	//	if (l == r)
	//		return *l;
	//	else
	//	{
	//		Iterator randomiter = l + rand() % std::distance(l, r);
	//		return *randomiter;
	//	}
	//}

	//unsigned partition(Iterator& l, Iterator& r, int p)
	//{
	//	Iterator l_temp = l;
	//	while (l <= r)
	//	{
	//		while (*l < p)
	//		{
	//			l++;
	//		}
	//		while (*r > p)
	//		{
	//			r--;
	//		}
	//		std::iter_swap(l, r);
	//		if (*l == *r)
	//			l++;
	//	}
	//	l--;

	//	unsigned d = std::distance(l_temp, l);
	//	return d;
	//}

	//int quickselect(Iterator& l, Iterator& r, size_t k)
	//{
	//	if (l == r) return *l;
	//	unsigned length = std::distance(l, r);
	//	std::cout << "length: " << length << std::endl;
	//	int x = randompivot(l, r);
	//	std::cout << "Random pivot: " << x << std::endl;
	//	std::cout << "Before: ";
	//	//print_v();
	//	unsigned m = partition(l, r, x);
	//	std::cout << "m : " << m << std::endl;
	//	std::cout << "After: ";
	//	/*print_v();*/
	//	Iterator begin = l - m;
	//	Iterator end = begin + length;
	//	if (*begin == *end) return quickselect(l, l, 0);
	//	if (k < m) {
	//		Iterator m_it = begin + (m - 1);
	//		return quickselect(begin, m_it, k);
	//	}
	//	else if (k > m) {
	//		Iterator m_it = begin + (m + 1);
	//		return quickselect(m_it, end, k-m-1);
	//	}
	//	else {
	//		Iterator m_it = begin + m;
	//		return *m_it;
	//	}
	//}

	//int selectRandomized(size_t k)
	//{
	//	Iterator l = v.begin();
	//	Iterator r = v.end() - 1;
	//	return quickselect(l, r, k);
	//}

	//solution
	Iterator partition(Iterator left, Iterator right, int p)
	{
		auto l = left;
		auto r = right -1;
		bool do_left = true;
		while (l <= r)
		{
			while (*l < p)
			{
				l++;
			}
			while (*r > p)
			{
				r--;
			}
			std::iter_swap(l, r);
			if (*l == *r)
				l++;
		}
		l--;

		return l;
	}

	int selectRandomized(size_t k)
	{
		Iterator l = v.begin();
		Iterator r = v.end();

		std::mt19937 gen(123);
		std::size_t n = r - l;
		if (k >= n)
			return 0;
		while (n > 1)
		{
			std::uniform_int_distribution<size_t> dis(0, n - 1);
			Iterator pivot = l + dis(gen);
			Iterator pos = partition(l, r, *pivot);
			std::size_t offset = pos - l;
			if (offset < k)
			{
				l = pos + 1;
				k -= offset + 1;
			}
			else if (offset > k)
				r = pos;
			else return *pos;
			n = r - l;
		}
		return *l;
	}

	void print_v()
	{
		for (const auto e : v)
		{
			std::cout << e << " ";
		}
		std::cout << std::endl;
	}

};

int main()
{	//test
	/*std::vector<int> v = { 10, 5, 3, 2, 2, 4, 7 };
	Selector s(v);*/
	//std::vector<int>::iterator l = s.v.begin();
	//std::vector<int>::iterator r = s.v.end()-1;
	/*std::vector<int>::iterator l_temp = s.v.begin();
	std::vector<int>::iterator r_temp = s.v.end() - 1;*/
	
	/*int x = 5;
	std::cout << x << std::endl;
	s.print_v();
	unsigned q = s.partition(l,r,x);
	std::cout << *l << std::endl;
	std::cout << q << std::endl;
	s.print_v();*/

	//std::cout << s.quickselect(l, r, 4) << std::endl;
	//s.print_v();
	
	//std::cout << s.selectRandomized(3) << std::endl;
	//s.print_v();
	int size;
	std::cin >> size;
	std::vector<int> v(size);
	for (auto e = v.begin(); e!= v.end(); e++)
	{
		std::cin >> *e;
	}
	Selector s(v);
	size_t k;
	std::cin >> k;

	if (k >= s.size())
	{
		std::cerr << "index too large" << std::endl;
		return EXIT_FAILURE;
	}

	std::cout << s.selectRandomized(k) << std::endl;

	return 0;
}

/*

  input examples:

  file testdata.txt 4
  random 50 8
  input 5 3 2 1 5 4 2

*/