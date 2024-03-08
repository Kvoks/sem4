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

	void remove(Node<T>* replaceable, T value) {
		if (replaceable == nullptr || this->root == nullptr) {
			insert(value);
			return;
		}
		if (replaceable == this->root) {
			if (replaceable->left->data <= value && replaceable->right->data > value) {
				replaceable->data = value;
				return;
			}
			std::cout << "replacement is not possible" << std::endl;
			return;
		}
		remove_dfs(replaceable, value, this->root);
	}

	void remove_dfs(Node<T>* replaceable, T value, Node<T>* cur) {
		if (cur == nullptr) {
			std::cout << "replacement is not possible" << std::endl;
			return;
		}
	
		if (cur->left == replaceable) {
			if (cur->data <= value && replaceable->left->data <= value && replaceable->right->data > value) {
				replaceable->data = value;
			}
			return;
		}

		if (cur->right == replaceable) {
			if (cur->data > value && replaceable->left->data <= value && replaceable->right->data > value) {
				replaceable->data = value;
			}
			return;
		}

		if (value <= cur->data) {
			remove_dfs(replaceable, value, cur->left);
		}
		else {
			remove_dfs(replaceable, value, cur->right);
			return;
		}
	}
};
#endif // !SEARCH_H