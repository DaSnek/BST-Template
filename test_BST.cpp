#include <stdio.h>
#include <iostream>
#include <vector>

#include "BST.hh"

int main() {
	BST<int> bst;

	int v;

	while (std::cin >> v) {
		bst.insert(v);

		std::cout << "BST: ";
		bst.dump_all_data();
		std::cout << std::endl;

		std::cout << "BST size: " << bst.get_size();
		std::cout << std::endl;
	}
}
