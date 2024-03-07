#ifndef SEARCH_H
#define SEARCH_H

#include<iostream>
#include"../BinaryTree/binary.h"

template <typename T>
class SearchTree : public BinaryTree<T> {
public:
	SearchTree(Node<T>* root_ = nullptr) {
		this->root = root_;
	}

	void insert(T value) {
		if (this->root == nullptr) {
			this->root = new Node<T>(value);
		}
		else {
			insert_dfs(value, this->root);
		}
	}

	void insert_dfs(T value, Node<T>* cur) {
		if (cur == nullptr) {
			return;
		}
		if (cur->left == nullptr && value <= cur->data) {
			Node<T>* newNode = new Node<T>(value);
			cur->left = newNode;
			return;
		}
		if (cur->right == nullptr && value > cur->data) {
			Node<T>* newNode = new Node<T>(value);
			cur->right = newNode;
			return;
		}
		if (value <= cur->data) {
			insert_dfs(value, cur->left);
		}
		else {
			insert_dfs(value, cur->right);
		}
	}

	Node<T>* find(T value) {
		return find_dfs(value, this->root);
	}

	Node<T>* find_dfs(T value, Node<T>* cur) {
		if (cur->data == value) {
			return cur;
		}
		if (cur->left != nullptr && value <= cur->data) {
			find_dfs(value, cur->left);
		}
		if (cur->right != nullptr && value > cur->data) {
			find_dfs(value, cur->right);
		}
		return cur;
	}

};
#endif // !SEARCH_H