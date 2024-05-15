#include<iostream>
#include"binary.h"

int main() {
	BinaryTree<int> b;
	b.insert(3);
	b.insert(5);
	b.insert(10);
	b.insert(7);
	b.find(10);
	b.printTree();
	b.remove(3);
	b.printTree();
	return 0;
}