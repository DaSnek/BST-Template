#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>

#include "BST.hh"

#define N		100

int random_num() {
	static bool init = false;
	if (!init) {
		srand(time(NULL));
		init = true;
	}

	return rand();
}

int main() {
	BST<int> bst;
	std::vector<int> v;

	for (int i = 0; i < N; i++) {
		v.push_back(random_num());
	}

	for (int i : v) {
		bst.insert(i);	
	}

	std::cout << std::endl;
	bst.dump_all_data();
	std::cout << std::endl;

	std::random_shuffle(v.begin(), v.end());

	std::cout << "--------------------" << std::endl;
	for (int i : v) {
		std::cout << bst.find(i)->data << std::endl;
	}

	std::cout << "--------------------" << std::endl;
	for (int i : v) {
		const Node<int>* a = bst.find_smaller_node(i); 
		std::cout << (a ? a->data : 'x') << std::endl;
	}
	
	std::cout << "--------------------" << std::endl;
	for (int i : v) {
		const Node<int>* a = bst.find_larger_node(i); 
		std::cout << (a ? a->data : 'x') << std::endl;
	}

	std::cout << "--------------------" << std::endl;
	for (int i : v) {
		if (!bst.delete_node(i)) {
			std::cout << "*************Node " << i << "delete failed****************" << std::endl;
		}
		bst.dump_all_data();
		std::cout << std::endl;
	}
	std::cout << "here" << std::endl;
}
