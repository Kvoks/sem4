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
		if (cur->right == nullptr && cur->left == nullptr) {
			std::cout << "element does not exist" << std::endl;
			return nullptr;
		}
	}

	void replace(Node<T>* replaceable, T value) {
		if (replaceable == nullptr || this->root == nullptr) {
			//insert(value);
			std::cout << "the element to be replaced does not exist" << std::endl;
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
		replace_dfs(replaceable, value, this->root);
	}

	void replace_dfs(Node<T>* replaceable, T value, Node<T>* cur) {
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
			replace_dfs(replaceable, value, cur->left);
		}
		else {
			replace_dfs(replaceable, value, cur->right);
			return;
		}
	}

	void remove(T value) {
		Node<T>* del = find(value);
		if (del == nullptr) {
			std::cout << "element does not exist" << std::endl;
			return;
		}
		
		Node<T>* cur = this->root;

		while (cur->left!= del || cur->right!= del) {//цилк для сохранения предка
			if (cur->data < del->data) {
				cur = cur->right;
			}
			else {
				cur = cur->left;
			}
		}

		if (del->left == nullptr && del->right == nullptr) {
			if (cur->left == del) {
				cur->left = nullptr;
			}
			else {
				cur->right == nullptr;
			}
			delete del;
			return;
		}

		if (del->left == nullptr && del->right != nullptr) {
			if (cur->left == del) {
				cur->left = del->right;
			}
			else {
				cur->right == del->right;
			}
			del->right = nullptr;
			delete del;
			return;
		}

		if (del->left != nullptr && del->right == nullptr) {
			if (cur->left == del) {
				cur->left = del->left;
			}
			else {
				cur->right == del->left;
			}
			del->left = nullptr;
			delete del;
			return;
		}

		cur = del->right;

		while (cur->left->left != nullptr) {
			cur = cur->left;
		}

		T v = cur->left->data;

		if (cur->left->right != nullptr) {
			cur->left = cur->left->right;
		}
		else {
			cur->left = nullptr;
		}

		del->data = v;
		return;
	}
	
};
#endif // !SEARCH_H