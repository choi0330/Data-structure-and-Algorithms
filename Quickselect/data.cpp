#include "data.h"
#include <iostream>
#include <vector>
#include <random>
#include <fstream>
#include <string>


/* for class Integer
Integer::Integer(int t): value(t){}
	(etc)
*/

std::vector<int> getData() {
	// input
	size_t n = 0;

	std::string name; // name of the data input method, should be "input" or "random" or "file"
	std::cin >> name;

	std::vector<int> a;

	// std::random_device rd;  //can be used to obtain a seed for the random number engine
	std::mt19937 gen(7); //Standard mersenne_twister_engine seeded with 7
	std::uniform_int_distribution<> dis(0, 1000);

	if (name == "random") {
		std::cin >> n;
		for (size_t i = 0; i < n; ++i) {
			a.push_back(dis(gen));
		}
	}
	else if (name == "file") {
		//todo
		std::string filename;
		std::cin >> filename;
		filename = "./" + filename;
		std::ifstream file(filename);
		file >> n;
		for (size_t i = 0; i < n; ++i) {
			int value;
			file >> value;
			a.push_back(value);
		}
	}
	else if (name == "tricky")
	{
		std::cin >> n;
		for (size_t i = n; i > 0; --i)
			a.push_back(i);
	}
	else if (name == "equal")
	{
		std::cin >> n;
		for (size_t i = 0; i < n; ++i)
			a.push_back(123);
	}
	else // should be "input"
	{
		std::cin >> n;
		for (size_t i = 0; i < n; ++i)
		{
			int value;
			std::cin >> value;
			a.push_back(value);
		}
	}
	return a;
}

