#ifndef __BST_HH__
#define __BST_HH__

#include <iostream>

template <typename T>
class Node {
public:
	T data;
	Node* parent;
	Node* left;
	Node* right;

	Node() = delete;

	Node(const T& d) : data{d}, parent{nullptr}, left{nullptr}, right{nullptr} {} 
};

template <typename T>
class BST {
	Node<T>* root;
	int size;

private:
	void delete_tree(Node<T>* n) {
		if (!n) {
			return;
		}

		delete_tree(n->left);
		delete_tree(n->right);
		std::cout << "delete " << n->data << std::endl;
		delete n;
	}

	Node<T>* find_smaller_node(const Node<T>* n) const {

	}

	Node<T>* find_smaller_node(const T& d) const {

	}

	//find_larger_node() {/*todo*/}

public:
	BST() : size{0}, root{nullptr} {}

	int get_size() const {
		return size;
	}

	void dump_subtree_data(const Node<T>* n) const {
		if (!n) {
			return;
		}

		dump_subtree_data(n->left);
		std::cout << n->data << " ";
		dump_subtree_data(n->right);

		return;
	}

	void dump_all_data() const {
		dump_subtree_data(root);
		return;
	}

	bool insert(const T& d) {
		Node<T>* n = new Node<T>(d);

		if (root == nullptr) {
			root = n;
			size = 1;
			return true;
		}

		Node<T>* n1 = root;
		Node<T>* n2 = NULL;

		while (n1) {
			n2 = n1;

			if (d < n1->data) {
				n1 = n1->left;
			} else if (d > n1->data) {
				n1 = n1->right;
			} else if (d == n1->data) {
				delete n;
				return false;
			}
		}
		
		if (d < n2->data) {
			n2->left = n;
		} else if (d > n2->data) {
			n2->right = n;
		}

		n->parent = n2;
		size++;	 

		return true;
	}

	virtual ~BST() {
		delete_tree(root);
	}
};

#endif
