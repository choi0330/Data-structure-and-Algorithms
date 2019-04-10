#include <iostream>
#include <functional>
#include <random>
#include <cctype>
#include <string>
#include <climits> // for CHAR_BITS


//#include "sortedlist.h"
#include "skiplist.h"

// rotate left for simple checksum computation
unsigned int rol(unsigned int x, unsigned int bits) {
	return x << bits | x >> (sizeof(unsigned int)*CHAR_BIT - bits);
}

// output the values of the container in a autograder-friendly form 
// output the first 8 elements, then output elements 8, 16, 32, etc.
void writeOutput(const SkipList &c) {
	size_t k = 0;
	size_t l = 0;
	unsigned int checksum = 0;
	for (auto x : c) {  // this needs iterators to be implemented!
		unsigned int value = std::hash<unsigned int>()(x);
		checksum = rol(checksum, 7) ^ value;
		if (k == l) {
			std::cout << x << " ";
			if (l < 8) {
				++l;
			}
			else {
				l *= 2;
			}
		}
		++k;
	}
	if (k == 0) {
		std::cout << "empty";
	}
	if (k > 8) {
		std::cout << ", n = " << k;
		std::cout << ", checksum = " << checksum;
	}
	std::cout << std::endl;
}

// return if the stream might contain an integer as next symbol
// does not consume the integer
bool hasInt(std::istream& in) {
	while (in.good() && std::isspace(in.peek()))
		in.get();
	return in.good() && (std::isdigit(in.peek()) || in.peek() == '-');
}

// consume and return next identifier from stream in
std::string getCommand(std::istream& in) {
	std::string command;
	in >> command;
	return command;
}

// class to generate pseudo random numbers
class Random {
	std::mt19937 gen;
	std::uniform_int_distribution<> dis;

public:
	Random(unsigned int seed) : dis(1, 65000) {
		gen.seed(seed);
	}

	int get() {
		return dis(gen);
	}
};

// The following main function implements a little command interface
// The format of the test input is 
// { add values {<value:int>} | add random <size:int> | 
//   remove values {<value:int>} | remove random <skip:int> <size:int> |
//   print | end }.
int main() {

	// random number with probability
	//std::random_device rd;
	//std::mt19937 gen(rd());
	//double weights[17];
	//double val = 1;
	//for (int i = 1; i < 17; i++)
	//{
	//	weights[i] = val;
	//	val = 0.5*val;
	//	std::cout << weights[i] << " ";
	//}
	//weights[0] = 0;
	//std::cout << std::endl;
	//std::discrete_distribution<> d(std::begin(weights), std::end(weights));
	//for (int i = 0; i < 10000; i++)
	//{
	//	int rand_level = d(gen);
	//	std::cout << rand_level << " ";
	//}


	SkipList list;
	////list.insert(1);
	////list.insert(2);
	////list.insert(2);
	////list.insert(3);
	////list.insert(4);
	////list.erase(1);
	////list.erase(2);
	////list.erase(3);
	////list.erase(4);
	////writeOutput(list);
	////sorted_list list;
	while (std::cin.good()) {
		std::string command = getCommand(std::cin);
		if (command == "end") {
			break;
		}
		if (command == "add") {
			std::string sub = getCommand(std::cin);
			if (sub == "values") {
				while (hasInt(std::cin)) {
					int value;
					std::cin >> value;
					list.insert(value);
				}
			}
			else if (sub == "random") {
				unsigned int seed;
				std::cin >> seed;
				Random random(seed);
				std::size_t size;
				std::cin >> size;
				while (size-- != 0) {
					list.insert(random.get());
				}
			}
		}
		else if (command == "remove") {
			std::string sub = getCommand(std::cin);
			if (sub == "values") {
				while (hasInt(std::cin)) {
					int value;
					std::cin >> value;
					list.erase(value);
				}
			}
			else if (sub == "random") {
				unsigned int seed;
				std::cin >> seed;
				Random random(seed);
				std::size_t size;
				std::cin >> size;
				while (size-- != 0) {
					list.erase(random.get());
				}
			}
		}
		else if (command == "print") {
			writeOutput(list);
		}
		else {
			std::cout << "unknown command: '" << command << "'" << std::endl;
		}
	}
	return 0;
}