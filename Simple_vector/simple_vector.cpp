#include <algorithm>
#include <iostream>

class Vector
{
public:
	// member types
	using value_type = int;
	using iterator = int*;
	using const_iterator = const int*;
	using reference = int&;
	using const_reference = const int&;

	// constructors
	Vector() : sz{ 0 }, elem{ nullptr }
	{}

	Vector(std::size_t size) : sz{ size }, elem{ new int[size] }
	{}

	Vector(const Vector& vector) : Vector(vector.sz)
	{
		std::copy(vector.elem, vector.elem + vector.sz, elem);
	}

	// deconstructor
	~Vector()
	{
		delete[] elem;
	}

	// assignment
	Vector& operator = (const Vector& vector)
	{
		Vector cpy(vector);
		swap(cpy);
		return *this;
	}

	std::size_t size() const
	{
		return sz;
	}

	// element access
	reference operator [] (std::size_t index)
	{
		return elem[index];
	}

	const_reference operator [] (std::size_t index) const
	{
		return elem[index];
	}

	// modifiers
	void swap(Vector& vector)
	{
		std::swap(sz, vector.sz);
		std::swap(elem, vector.elem);
	}

private:
	int* elem;
	std::size_t sz;
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