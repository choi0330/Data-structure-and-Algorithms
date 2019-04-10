#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>

using namespace std;

template<typename It1, typename It2>
It1 findOccurrence(const It1 from, const It1 to, const It2 begin, const It2 end)
{
	const unsigned M = 32768;
	const unsigned C = 1021;

	unsigned hash_b = 0;
	unsigned hash_a = 0;

	// your code here
	if (end - begin > to - from)
		return to;

	unsigned k = end - begin;
	
	// Hash b
	unsigned temp_c_k_b = 1;
	for (int j = k - 1; j >= 0; j--)
	{
		hash_b += *(begin + j)*(temp_c_k_b);
		hash_b %= M;
		if (j == 0) break;
		temp_c_k_b *= C;
		temp_c_k_b %= M;
	}
	hash_b %= M;
	
	// Hash a
	unsigned temp_c_k_a = 1;
	for (int j = k - 1; j >= 0; j--)
	{
		hash_a = hash_a + *(from + j)*(temp_c_k_a);
		hash_a %= M;
		if (j == 0) break;
		temp_c_k_a *= C;
		temp_c_k_a %= M;
	}
	hash_a %= M;

	unsigned n = to - from;
	unsigned c_i = temp_c_k_a;
	unsigned c_k = 1;

	for (unsigned i = 0; i <= n - k; i++)
	{
		if (hash_a == hash_b)
		{
			if (std::equal(from + i, from + i + k, begin, end))
			{
				return from + i;
			}

		}
		
		unsigned a_i = *(from + i)*(c_i);
		a_i %= M;
		unsigned a_i_plus_k = *(from + i + k)*(c_k);
		a_i_plus_k %= M;
		hash_a = (hash_a - a_i)*C + a_i_plus_k;
		hash_a %= M;	
	}

	return to;
}

int main()
{
	std::string command;
	std::getline(std::cin, command);

	std::string input;
	std::string substring;

	if (command == "input")
	{
		std::getline(std::cin, input);
		std::getline(std::cin, substring);
	}
	else
	{
		std::string filename;
		std::cin >> filename;
		filename = "./" + filename;
		std::ifstream file(filename);
		std::getline(file, input);
		std::getline(file, substring);
	}

	auto pos = findOccurrence(input.begin(), input.end(),
		substring.begin(), substring.end());
	if (pos == input.end())
		std::cout << "NOT FOUND" << std::endl;
	else
		std::cout << std::distance(input.begin(), pos) << std::endl;

	return 0;
}
