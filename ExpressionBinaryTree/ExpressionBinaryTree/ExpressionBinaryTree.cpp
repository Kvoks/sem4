#include "ExpressionBinaryTree.h"
#include <string>
#include <iostream>
#include <exception>
#include <stdexcept>

ArithmeticTree::ArithmeticTree(std::string str)
{
	head = new Node(str);
}

int ArithmeticTree::calculate()
{
	if (!head)
	{
		throw std::logic_error("Tree is empty");
	}
	return head->calculate(head);
}

ArithmeticTree::~ArithmeticTree()
{
	if (head)
	{
		head->free_tree(head);
	}
}
