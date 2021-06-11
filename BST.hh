#ifndef __BST_HH__
#define __BST_HH__

#include <iostream>
#include <stdio.h>
#include <assert.h>

template <typename T>
class Node {
public:
	T data;
	Node<T>* parent;
	Node<T>* left;
	Node<T>* right;

	Node() = delete;

	Node(const T& d) : data{d}, parent{nullptr}, left{nullptr}, right{nullptr} {} 

	virtual ~Node() {
		std::cout << "Node " << data << " deleted\n";
	}
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
		size--;
	}

	Node<T>* find_smaller_node(Node<T>* n) const {
		assert(n);

		Node<T>* n1 = n;

		if (!n->left) {
//			std::cout << n1->data << std::endl;

			while (n1 && (n1->data >= n->data)) {
//				std::cout << n1->data << std::endl;
				n1 = n1->parent;
			}
		} else {
			n1 = n->left;
//			std::cout << n1->data <<std::endl;
		
			while (n1->right) {
//				std::cout << n1->data << std::endl;
				n1 = n1->right;
			}
		}		
		return n1;
	}
		
	Node<T>* find_larger_node(Node<T>* n) const {
		assert(n);

		Node<T>* n1 = n;

		if (!n->right) {
//			std::cout << n1->data << std::endl;

			while (n1 && (n1->data <= n->data)) {
//				std::cout << n1->data << std::endl;
				n1 = n1->parent;
			}
		} else {
			n1 = n->right;
//			std::cout << n1->data <<std::endl;
		
			while (n1->left) {
//				std::cout << n1->data << std::endl;
				n1 = n1->left;
			}
		}		
		return n1;
	}

	bool delete_node(Node<T>* n) {
		if (!n) {
			return false;
		}
		
		Node<T>* t = n;

		if (!n->left && !n->right) {
			t = n->parent;
			if (!t) {
				delete n;
				root = nullptr;
				size = 0;
				return true;
			}

			if (t->left == n)
				t->left = nullptr;
			else 
				t->right = nullptr;

			n->parent = NULL;
			delete n;
			
			size--;
			return true;
		}

		if (!n->left ^ !n->right) { 
			t = n->right ? n->right : n->left;
			t->parent = n->parent;
			if (!n->parent) {
				root = t;
				delete n;
				size--;
				return true;
			}				

			if (n == n->parent->left) 
				 n->parent->left = t;
			else 
				 n->parent->right = t;

			delete n;
			size--;

			return true;
		}

		t = find_larger_node(n);

		T temp = n->data;
		n->data = t->data;
		t->data = temp;

		return delete_node(t);
	}		

public:
	BST() : size{0}, root{nullptr} {}

	//returns NULL if not found
	Node<T>* find(const T& d) const {
		Node<T>* n = root;
		
		while (n && n->data != d) {
			if (n->data < d) 
				n = n->right;
			else 
				n = n->left;
		}

		return n;
	}

	const Node<T>* find_smaller_node(const T& d) const {
		Node<T>* n = find(d);
	
		if (!n)	{
			return nullptr;
		}
		
		return find_smaller_node(n);
	}

	const Node<T>* find_larger_node(const T& d) const {
		Node<T>* n = find(d);
	
		if (!n)	{
			return nullptr;
		}
		
		return find_larger_node(n);
	}

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
		std::cout << "[" << size << "]: ";
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

	bool delete_node(const T& d) {
		Node<T>* n = find(d);

		if (!n) 
			return false;

		return delete_node(n);
	}

	virtual ~BST() {
		delete_tree(root);
	}
};

#endif
