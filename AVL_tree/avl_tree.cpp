#include <iostream>
#include <cassert>
#include <string>
#include <cctype>
#include <algorithm>

using namespace std;

template <typename T>
class AvlTree {
public:
	AvlTree() :root{ nullptr }
	{};

	class Node {
	public:
		Node(){};
		Node(T val) :value{ val }, left{ nullptr }, right{ nullptr }, height{ 1 }
		{};
		~Node() {};
	private:
		T value;
		Node* left;
		Node* right;
		int height;
		
	public:
		void print_node() {
			if (this != nullptr) 
			{
				cout << this->value << " ";
				this->left->print_node();
				this->right->print_node();
			}
		}

		int get_height(Node* node)
		{
			if (node == nullptr)
				return 0;
			return node->height;
		}

		int balance()
		{
			if (this == nullptr) return 0;
			return get_height(right) - get_height(left);
		}

		void update() {
			if (this == nullptr) return;
			height = max(get_height(left),get_height(right)) + 1;
			left->update();
			right->update();
		}

		Node* rotate_left(Node* x)
		{
			Node* new_pivot = x->right;
			Node* transfer = new_pivot->left;

			new_pivot->left = x;
			x->right = transfer;

			new_pivot->update();
			x->update();

			return new_pivot;
		}

		Node* rotate_right(Node* x)
		{
			Node* new_pivot = x->left;
			Node* transfer = new_pivot->right;

			new_pivot->right = x;
			x->left = transfer;

			new_pivot->update();
			x->update();

			return new_pivot;
		}

		T fin_min(Node* node)
		{
			T sym_suc;
			while (node != nullptr)
			{
				sym_suc = node->value;
				node = node->left;
			}
			return sym_suc;
		}

		Node* insert_key(T key, Node* x)
		{
			if (x == nullptr)
			{
				x = new Node(key);
				return x;
			}

			else if (x->value < key)
			{
				 x->right = x->right->insert_key(key,x->right);
				 if (x->balance() == 2) {
					 if (x->right->value < key)
						 x = rotate_left(x);
					 else
					 {
						 x->right = rotate_right(x->right);
						 x = rotate_left(x);
					 }
				 }
			}

			else if (key < x->value)
			{
				x->left = x->left->insert_key(key,x->left);
				if (x->balance() == -2) {
					if (key < left->value)
						x = rotate_right(x);
					else
					{
						x->left = rotate_left(x->left);
						x = rotate_right(x);
					}
				}
			}

			else
			{
				cout << "Same value inserted. Error" << endl;
				return x;
			}
			x->update();
			return x;					   
		}

		Node* remove_key(T key, Node* x)
		{
			if (x == nullptr)
			{
				cout << "Element not found" << endl;
				return x;
			}
			else if (key < x->value) x->left = x->left->remove_key(key, x->left);

			else if (x->value < key) x->right = x->right->remove_key(key, x->right);
			
			else if (x->left != nullptr && x->right != nullptr)
			{
				x->value = fin_min(x->right);
				x->right = remove_key(x->value, x->right);
			}

			else
			{
				Node* temp = x;
				if (x->left == nullptr) x = x->right;
				else if (x->right == nullptr) x = x->left;
				delete temp;
			}

			if (x == nullptr)
				return x;

			x->update();

			if (x->balance() == 2) {
				if (x->right->value < key)
					x = rotate_left(x);
				else
				{
					x->right = rotate_right(x->right);
					x = rotate_left(x);
				}
			}

			else if (x->balance() == -2) {
				if (key < left->value)
					x = rotate_right(x);
				else
				{
					x->left = rotate_left(x->left);
					x = rotate_right(x);
				}
			}

			x->update();
			return x;
		}
	};

	// insert key into the AVL tree
	void insert(T key) {
		root = root->insert_key(key,root);
		assert(root->balance() == -1 || root->balance() == 0 || root->balance() == 1);
	}

	// remove key from the AVL tree, OPTIONAL.
	void remove(T key) {
		root = root->remove_key(key, root);
		assert(root->balance() == -1 || root->balance() == 0 || root->balance() == 1);
	}

	// output the content of the tree in pre-order: node then node->left then node->right
	void print() {
		if (root != nullptr)
		{
			root->print_node();
		}
	}

private:
	Node* root;
};


// please do not modify this function
bool hasInt(std::istream& is) {
	return is.good() && is >> std::ws && is.good() && !std::isalpha(is.peek());
}

// main function -- driver of the tests, please do not modify
int main() {
	AvlTree<int> tree;
	for (std::string command; std::cin >> command && command != "end";) {
		if (command == "insert") {
			for (int num; hasInt(std::cin) && std::cin >> num;) {
				tree.insert(num);
			}
		}
		else if (command == "remove") { // removal is an optional part of the exercise -- it is not tested
			for (int num; hasInt(std::cin) && std::cin >> num;) {
				tree.remove(num);
			}
		}
		else if (command == "print") {
			std::cout << "[ ";
			tree.print(); // output of the tree in pre-order: node then left then right
			std::cout << " ]" << std::endl;
		}
		else {
			std::cerr << "command?" << std::endl;
		}
	}
	return 0;
}