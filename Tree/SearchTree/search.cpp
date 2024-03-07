#include<iostream>
#include"../BinaryTree/binary.h"
#include"search.h"

int main() {
	SearchTree<int> b;
	b.insert(3);
	b.insert(2);
	b.insert(10);
	b.insert(7);
	b.find(10);
	return 0;
}