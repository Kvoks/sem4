#ifndef ExpressionBinaryTree_H
#define ExpressionBinaryTree_H

#include "../Node/Node.h"
#include <iostream>
class ArithmeticTree
{
private:
	Node* head = nullptr;
public:
	ArithmeticTree(std::string str);
	~ArithmeticTree();
	int calculate();
};

#endif