#include <algorithm>
#include <iostream>
#include <cctype>

// Copy your implementation of the class template Vector
// and your template functions read, write and sort from task 1
// and add the following class members to the String class:
template <typename T>
class Vector
{
public:
	// member types
	using value_type = T;
	using iterator = T * ;
	using const_iterator = const T*;
	using reference = T & ;
	using const_reference = const T&;

	// constructors
	Vector() :
		first{ nullptr }, last{ nullptr }, limit{ nullptr }
	{
	}

	Vector(std::size_t size) :
		Vector(size, 2 * size)
	{
	}

	Vector(const Vector& vector) :
		Vector(vector.last - vector.first)
	{
		std::copy(vector.first, vector.last, first);
	}

	Vector(Vector&& vector) :
		Vector()
	{
		swap(vector);
	}

	// deconstructor
	~Vector()
	{
		delete[] first;
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

	// iterators
	iterator begin()
	{
		return first;
	}

	iterator end()
	{
		return last;
	}

	const_iterator begin() const
	{
		return first;
	}

	const_iterator end() const
	{
		return last;
	}

	std::size_t size() const
	{
		return last - first;
	}

	// element access
	reference operator [] (std::size_t index)
	{
		return first[index];
	}

	const_reference operator [] (std::size_t index) const
	{
		return first[index];
	}

	// modifiers
	void swap(Vector& vector)
	{
		std::swap(first, vector.first);
		std::swap(last, vector.last);
		std::swap(limit, vector.limit);
	}

	void push_back(const value_type& value)
	{
		if (last == limit)
		{
			std::size_t size = last - first;
			Vector vector{ size, size * 2 + 1 };
			std::move(first, last, vector.first);
			swap(vector);
		}

		*last = value;
		++last;
	}

	void pop_back()
	{
		T* temp = last - 1;
		delete last;
		last = temp;

		if (limit - last > last - first)
		{
			std::size_t size = last - first;
			Vector vector(size);
			std::move(first, last, vector.first);
			swap(vector);
		}

	}

	void clear()
	{
		last = first;
	}

private:
	Vector(std::size_t size, std::size_t capacity) :
		first{ new value_type[capacity] }, last{ first + size }, limit{ first + capacity }
	{
	}

	iterator first;
	iterator last;
	iterator limit;
};

template <typename T> Vector<T> read()
{
	Vector<T> vector;
	for (T value; std::cin >> value;) vector.push_back(value);
	return vector;
}


template <typename T> void sort(T* begin, T* end)
{
	for (T* iter = begin; iter != end; ++iter)
	{
		auto min = iter;

		for (T* iter2 = iter; iter2 != end; ++iter2)
		{
			if (*iter2 < *min)
			{
				min = iter2;
			}
		}
		std::swap(*iter, *min);
	}
}

template <typename T> void write(const T* begin, const T* end)
{
	for (const T* iter = begin; iter != end; ++iter)
		std::cout << *iter << ' ';
}

class String
{
public:
	// constructors
	String() : first(new char), last(nullptr)
	{}

	// iterators
	char* begin()
	{
		return first;
	}

	char* end()
	{
		return last;
	}

	const char* begin() const
	{
		return first;
	}

	const char* end() const
	{
		return last;
	}

	// modifiers
	void clear()
	{
		first = new char;
		last = first;
	}

	String& operator += (char character)
	{
		*last = character;
		last++;
		return *this;
	}

private:
	char* first;
	char* last;
};

bool operator < (const String& a, const String& b)
{
	return std::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end());
}

std::ostream& operator << (std::ostream& os, const String& string)
{
	for (auto& e : string)
		os << e;
	return os;
}

std::istream& operator >> (std::istream& is, String& string)
{
	string.clear();
	while (is.good() && std::isspace(is.peek())) is.ignore();
	while (is.good() && std::isgraph(is.peek())) string += is.get();
	if (string.begin() == string.end()) is.setstate(is.failbit);
	return is;
}

int main()
{
	auto vector = read<String>();
	sort(vector.begin(), vector.end());
	write(vector.begin(), vector.end());
}