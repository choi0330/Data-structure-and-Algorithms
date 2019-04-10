#pragma once
#include <vector>

class SkipList { 
public:
	// A node represents the whole column of element occurences on levels [1..level].
	class Node {
	public:
		int value;

		// pointers to successor nodes
		std::vector<Node*> forward;

		Node(int v, std::size_t level)
			: value(v), forward(level, nullptr) {}

		std::size_t level() const {
			return forward.size();
		}
	};

public:
	SkipList() : max_level_(16) {
		head = new Node(0, max_level_);
		std::fill(head->forward.begin(), head->forward.end(), nullptr);
	}

	~SkipList();

	// Iterates all elements: they are all represented at the lowest level.
	class Iterator {
	private:
		Node* current_;

	public:
		Iterator()
			: current_(nullptr) {}

		Iterator(typename SkipList::Node* node)
			: current_(node) {}

		Iterator& operator=(Iterator& other) {
			current_ = other.current_;
			return *this;
		}

		Iterator& operator++() {
			current_ = current_->forward[0];
			return *this;
		}

		Iterator operator++(int) {
			Iterator r(*this);
			current_ = current_->forward[0];
			return r;
		}

		bool operator!=(const Iterator& other) {
			return current_ != other.current_;
		}

		int& operator->() {
			return current_->value;
		}

		int& operator*() {
			return current_->value;
		}
	};

	// Insert a new node containing the provided value at the corresponding position
	// in the list. Note that thus a value can occur multiple times in the list.
	void insert(int value);

	// Deletes all the elements containing value, if they exist.
	void erase(int value);
	
	/*std::size_t size();
	void swap(std::size_t i, std::size_t j);
	std::vector<int> copy(SkipList& v);
	void sink(SkipList& v, std::size_t i, std::size_t m);
	void heapSort(SkipList& v);*/
	
	Iterator begin() const {
		return Iterator(head->forward[0]);
	}

	Iterator end() const {
		return Iterator();
	}
	

public:
	// data members
	const std::size_t max_level_;
	Node* head; // pointer to first node
};
