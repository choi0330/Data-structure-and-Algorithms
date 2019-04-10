#include "skiplist.h"
#include <random>
#include <chrono>
#include <iostream>

using namespace std;
// you can use stderr for debugging
// (it does not interfere with the grading)
// example: cerr << "inserting number " << value << endl;

SkipList::~SkipList() {
	Node* current = head;
	Node * temp = head;

	for (auto e : *this)
	{
		current = temp;
		temp = temp->forward[0];
		free(current);
	}
	delete temp;
}

void SkipList::insert(int value) {

	auto start = chrono::steady_clock::now();

	vector<Node*> update(max_level_);
	Node* current = head;
	Node * temp = head;

	int rand_lev = 1;
	while (((double)rand() / (RAND_MAX)) < 0.5 && rand_lev < max_level_)
		rand_lev++;


	for (int i = max_level_ - 1; i >= 0; i--)
	{
		while (current->forward[i] != nullptr)
		{
			if (value > current->forward[i]->value)
			{
				current = current->forward[i];
			}
			else break;
		}
		update[i] = current;
	}
	temp = new Node(value, rand_lev);

	for (int j = 0; j <= rand_lev - 1; j++)
	{
		temp->forward[j] = update[j]->forward[j];
		update[j]->forward[j] = temp;
	}

	auto end = chrono::steady_clock::now();
	auto diff = end - start;
	cout << chrono::duration <double, nano>(diff).count() << " ns" << endl;

}

void SkipList::erase(int value) {
	// find all the keys with 'value' : erase and sort again//
	vector<Node*> update(max_level_);
	Node* current = head;

	for (int i = max_level_ - 1; i >= 0; i--)
	{
		while (current->forward[i] != nullptr)
		{
			if (value > current->forward[i]->value)
			{
				current = current->forward[i];
			}
			else break;
		}
		update[i] = current;
	}
	current = current->forward[0];
	if (current != nullptr)
	{
		while(current->value == value)
		{
			for (unsigned i = 0; i <= current->level() - 1; i++)
			{
				if (update[i]->forward[i] != current) break;
				update[i]->forward[i] = current->forward[i];
			}
			delete current;
			current = update[0]->forward[0];
			if (current == nullptr) break;
		}
	}
}



















// cannot be used //
//Bubble sorting
//
//	//1. size
//std::size_t n = 0;
//Node* current = head;
//while (1)
//{
//	if (current->forward[0] == nullptr)
//		break;
//	current = current->forward[0];
//	n++;
//}
//
//if (n == 0) return;
//
////2. vector
//std::vector<int> arr(n);
//Node* current_2 = head;
//for (unsigned i = 0; i < n; i++)
//{
//	current_2 = current_2->forward[0];
//	arr[i] = current_2->value;
//}
//
////3. sorting (vector and list)
//for (std::size_t i = 0; i < n - 1; i++)
//{
//	for (std::size_t j = 0; j < n - 1; j++)
//	{
//		if (arr[j] > arr[j + 1])
//		{
//			std::swap(arr[j], arr[j + 1]);
//			Node* current1 = head;
//			Node* current2 = current1->forward[0];
//			for (std::size_t size = j + 1; size >= 1; size--)
//			{
//				current1 = current1->forward[0];
//				current2 = current1->forward[0];
//			}
//			std::swap(current1->value, current2->value);
//		}
//	}
//}



//std::size_t size()
//{
//	std::size_t n = 0;
//	Node* current = head;
//	while (1)
//	{
//		current = current->forward[0];
//		n++;
//		if (current->forward[0] == nullptr)
//			break;
//	}
//	return n;
//}
//
//void swap(std::size_t i, std::size_t j) {
//	Node* current1 = head;
//	for (std::size_t size = i; size >= 1; size--)
//	{
//		current1 = current1->forward[0];
//	}
//	Node* current2 = head;
//	for (std::size_t size = j; size >= 1; size--)
//	{
//		current2 = current2->forward[0];
//	}
//	int temp = current2->value;
//	current2->value = current1->value;
//	current1->value = temp;
//}
//
//std::vector<int> copy(SkipList& v) {
//
//	std::size_t n = v.size();
//	std::vector<int> arr(n);
//	Node* current_2 = v.head;
//	for (unsigned i = 0; i < n; i++)
//	{
//		current_2 = current_2->forward[0];
//		arr[i] = current_2->value;
//	}
//
//	return arr;
//}
//
//void sink(SkipList& v, std::size_t i, std::size_t m)
//{
//	std::size_t n = v.size();
//	std::vector<int> arr = v.copy(v);
//
//	std::size_t index = i;
//
//	while (2 * index <= m)
//	{
//		std::size_t j = 2 * index;
//		if (j < m && arr[j - 1] < arr[j])
//			j++;
//		if (arr[index - 1] < arr[j - 1])
//		{
//			std::swap(arr[index - 1], arr[j - 1]);
//			v.swap(index, j);
//			index = j;
//		}
//		else index = m;
//	}
//}
//
//void heapSort(SkipList& v)
//{
//	std::size_t n = v.size();
//	for (std::size_t i = n / 2; i >= 1; i--)
//		sink(v, i, n);
//	for (std::size_t i = n; i >= 2; i--)
//	{
//		v.swap(1, i);
//		sink(v, 1, i - 1);
//	}
//}