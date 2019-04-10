#include <algorithm>
#include <iostream>

// Copy your vector implementation from the previous task
// and add the the following class members:
class Vector
{
	// member types
	using value_type = int;
	using iterator = int*;
	using const_iterator = const int*;
	using reference = int&;
	using const_reference = const int&;

public:
	// constructors
	Vector() :
		sz{ 0 }, capa{ 0 }, buffer{ nullptr }
	{}

	Vector(std::size_t size) :
		sz{ size }, capa{ 2 * size }, buffer{ new value_type[size] }
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
		delete[] reinterpret_cast<int*>(buffer);
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
		return buffer[sz - 1];
	}

	void clear()
	{
		delete[] buffer;
		sz = 0;
		capa = 0;
	}

	void push_back(int ele)
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
				tmp[sz] = ele;
				swap(tmp);
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
		int* last = buffer + sz;
		delete last;
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
		int* last = buffer + sz;
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
	int* buffer;
	std::size_t sz;
	std::size_t capa;
};

Vector read()
{
	std::size_t size;
	std::cin >> size;
	Vector vector{ size };
	for (std::size_t index = 0; index != size; ++index) std::cin >> vector[index];
	return vector;
}

void sort(Vector& vector)
{
	for (std::size_t index = 0; index != vector.size(); ++index)
	{
		auto minimum = index;
		for (auto comparand = minimum; comparand != vector.size(); ++comparand)
			if (vector[comparand] < vector[minimum]) minimum = comparand;
		if (minimum != index) std::swap(vector[minimum], vector[index]);
	}
}

void write(const Vector& vector)
{
	for (std::size_t index = 0; index != vector.size(); ++index)
		std::cout << vector[index] << ' ';
}

int main()
{
	auto vector = read();
	sort(vector);
	write(vector);
}