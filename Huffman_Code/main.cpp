#include <iostream>
#include <vector>
#include <cassert>
#include <random>
#include <map>
#include <queue>
#include <memory>
#include <fstream>
#include <sstream>

using namespace std;

class Node {
public:
	char character;
	int freq;
	std::shared_ptr<Node> left;
	std::shared_ptr<Node> right;

public:
	Node() {};
	Node(char a, int b) : character{a}, freq{b}
	{};
	Node(Node a, Node b) : character{ NULL }, freq { a.freq + b.freq }, left{ &a }, right{ &b }
	{};

};

int depth(shared_ptr<Node> head, char a, int dep)
{
	if (!head)
		return 0;

	if (head->character != a)
	{
		dep = max(depth(head->right, a, dep+1), depth(head->left, a, dep + 1));
	}
	else if (head->character == a)
		return dep;

	return dep;
}

// Printing codes
string Codes(shared_ptr<Node> head, char a, string s)
{

	if (!head)
		return "";

	if (head->character != a)
	{
		if(Codes(head->left, a, s + "0").length() > Codes(head->right, a, s + "1").length())
			s = Codes(head->left, a, s + "0");
		else 
			s = Codes(head->right, a, s + "1");

	}
	else if (head->character == a)
	{
		return s;
	}
	return s;
}

void encode(std::istream& in) {
	// read in characters and get frequencies
	std::map<char, int> freq_map;

	char x;
	int n = 0;
	while (in.get(x)) {
		// update frequencies
		auto search = freq_map.find(x);
		if (search != freq_map.end())
		{
			search->second += 1;
		}
		else
		{
			freq_map.insert(make_pair(x, 1));
		}
		++n;
	}
	std::cout << "n = " << n << " characters" << std::endl;

	// build a min heap consisting of all leaf nodes
	auto comp_freq = [&](shared_ptr<Node> x, shared_ptr<Node> y) {return x->freq > y->freq; };
	priority_queue<shared_ptr<Node>, std::vector<shared_ptr<Node>>, decltype(comp_freq)> min_heap(comp_freq);

	for (auto ind = freq_map.begin(); ind != freq_map.end(); ind++)
	{
		min_heap.push(make_shared<Node>(ind->first, ind->second));
	}


	// build code tree
	shared_ptr<Node> head;

	while (min_heap.size() != 1)
	{
		shared_ptr<Node> left, right;
		left = min_heap.top();
		min_heap.pop();
		right = min_heap.top();
		min_heap.pop();

		head = make_shared<Node>('$', left->freq + right->freq);
		head->left = left;
		head->right = right;

		min_heap.push(head);
	}


	// output length of the code, i.e. the summed number of bits times the frequencies of characters
	int len = 0; // replace this by a call to a (recursive) function delivering the overal length
	for (auto ind = freq_map.begin(); ind != freq_map.end(); ind++)
	{
		len += depth(head, ind->first, 0)*(ind->second);
	}
	std::cout << "length = " << len << " bits" << std::endl;

	// make a table(map) & print codes (for fun)
	std::map<char, string> code_map;
	for (auto ind = freq_map.begin(); ind != freq_map.end(); ind++)
	{
		code_map.insert(make_pair(ind->first, Codes(head, ind->first, "")));
	}

	for (auto ind = code_map.begin(); ind != code_map.end(); ind++)
	{
		cout << ind->first << ": " << ind->second << endl;
	}
}

void encodeString(std::string str) {
	std::stringstream s;
	s << str;
	encode(s);
}

void encodeFile(std::string filename) {
	filename = "./" + filename;
	std::ifstream input(filename);
	encode(input);
}

// main function, use this unaltered function for your final submission
int main() {
	std::string command;
	std::cin >> command;
	if (command == "file") { // read in a file
		std::string filename;
		std::cin >> filename;
		encodeFile(filename);
	}
	else { // read in a string
		char och;
		std::cin >> och;
		assert(och == '"' || och == '\'');
		char ch;
		std::string str;
		while (std::cin.get(ch) && (ch != och)) {
			str += ch;
		}
		encodeString(str);
	}
}



/*
string "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbbccccccccccccddddddddddddddddeeeeeeeeefffff"
string "this is a text that needs to be encoded. I am looking forward to how this works."
file long.txt
file abc.txt
file longer.txt
string "aaaaaaaaaaaaaaaaaaaaaab"
*/
