#include <iostream>
#include <cmath>
#include <algorithm>
// Description
// allocations for 8 , 16, 32 , n elements: 4, 5, 6, [log_2(n)]_low + 1 times since a is set as 2
// number of allocations and copies are same in this code ( copy is used when allocating a bigger array temporarily)
// lower bound : a = 1, upper bound : a = 1073741823/sizeof(type); possible biggest size of array. it depends on the type of variable. 

template <typename T>
class Vector
{
	// member types
	using value_type = T;
	using iterator = T*;
	using const_iterator = const T*;
	using reference = T&;
	using const_reference = const T&;

public:
	// constructors
	Vector() :
		sz{ 0 }, capa{ 0 }, buffer{ nullptr }
	{}

	Vector(std::size_t size) :
		sz{ size }, capa{ 2*size }, buffer{ new value_type[2*size] }
	{}

	Vector(const Vector& vector) :
		Vector(vector.sz)
	{
		std::copy(vector.buffer, vector.buffer + vector.sz, buffer);
	}

	Vector(Vector&& vector) :
		Vector()
	{
		swap(vector);
	}

	// deconstructor
	~Vector()
	{
		delete[] buffer;
	}

	// assignment
	Vector& operator = (const Vector& vector)
	{
		Vector copy{ vector };
		swap(copy);
		return *this;
	}

	Vector& operator = (Vector&& vector)
	{
		swap(vector);
		return *this;
	}

	std::size_t size() const
	{
		return sz;
	}

	std::size_t capacity() const
	{
		return capa;
	}

	bool empty()
	{
		if (capa == 0)
			return true;
		else return false;
	}

	int& back()
	{
		return buffer[sz-1];
	}

	void clear()
	{
		delete[] buffer;
		sz = 0;
		capa = 0;
	}

	void push_back(T ele)
	{
		if (capa - sz >= 1)
		{
			buffer[sz] = ele;
			sz++;
		}
		else
		{
			if (sz != 0)
			{
				Vector tmp(sz);
				for (unsigned i = 0; i < sz; i++)
				{
					tmp[i] = buffer[i];
				}
				tmp[sz] = ele;
				swap(tmp);
				sz++;
			}
			else
			{
				Vector tmp(1);
				tmp[0] = ele;
				swap(tmp);
			}
		}
	}

	void pop_back()
	{
		sz--;
	}

	// element access
	reference operator [] (std::size_t index)
	{
		return buffer[index];
	}

	const_reference operator [] (std::size_t index) const
	{
		return buffer[index];
	}

	iterator begin()
	{
		return buffer;
	}

	iterator end()
	{
		T* last = buffer + sz;
		return last;
	}

	// modifiers
	void swap(Vector& vector)
	{
		std::swap(buffer, vector.buffer);
		std::swap(sz, vector.sz);
		std::swap(capa, vector.capa);
	}

	private:
		T* buffer;
		std::size_t sz;
		std::size_t capa;
};

void sink(Vector<int>& v, std::size_t i, std::size_t m)
{
	std::size_t index = i;
	while (2 * index <= m)
	{
		std::size_t j = 2 * index;
		if (j < m && v[j-1] < v[j])
			j++;
		if (v[index-1] < v[j-1])
		{
			std::swap(v[index-1], v[j-1]);
			index = j;
		}
		else index = m;
	}
}

void heapSort(Vector<int>& v)
{
	std::size_t n = v.size();
	for (std::size_t i = n / 2; i >= 1; i--)
		sink(v, i, n);
	for (std::size_t i = n; i >= 2; i--)
	{
		std::swap(v[0], v[i-1]);
		sink(v, 1, i - 1);
	}
	for (auto e : v)
	{
		std::cout << e << " ";
	}
	std::cout << std::endl;
}

// leave this main function unchanged for the autograder
int main()
{
	////test //pointer arithmetic
	//int* arr = new int[10];
	//int* first = &arr[5];
	//int* second = &arr[7];

	//std::cout << second - first << std::endl;

	//test // My vector
	//read
	//Vector myvec;

	//myvec.push_back(1);
	//for (auto e : myvec)
	//	std::cout << e << " ";
	//std::cout << std::endl;
	//myvec.push_back(2);
	//for (auto e : myvec)
	//	std::cout << e << " ";
	//std::cout << std::endl;
	//
	//myvec.pop_back();
	//for (auto e : myvec)
	//	std::cout << e << " ";
	//std::cout << std::endl;


	Vector<int> myvec;

	// read in vector until 0 appears (exclusive)
	int e;
	std::cin >> e;
	while (e != 0)
	{
		myvec.push_back(e);
		std::cin >> e;
	};

	// sort vector
	heapSort(myvec);

	// output vector
	for (auto x : myvec) {
		std::cout << x << " ";
	}

	return 0;
}
