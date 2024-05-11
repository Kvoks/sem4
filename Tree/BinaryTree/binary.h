#ifndef BINARY_H
#define BINARY_H

#include<iostream>
#include<queue>

template <typename T>
class Node {
public:
	T data;
	Node* left, *right;

	Node(T data = T(), Node* left = nullptr, Node* right = nullptr) {
		this->data = data;
		this->left = left;
		this->right = right;
	}
	Node(const Node<T>& r) {
		data = r.data;
		left = r.left;
		right = r.right;
	}
	~Node(){}

	bool operator==(const Node<T>* r) {
		return !((this->left == r->left) || (this->right == r->right) || (this->data == r->data));
	}
};

//Node* create(int value, Node* l = nullptr, Node* r = nullptr){};
template <typename T>
class BinaryTree {
protected:
	Node<T>* root;	// корень
	int flag = 0;
public:
	BinaryTree(Node<T>* root = nullptr) {
		this->root = root;
	}

	~BinaryTree() {
		del(root);
	}

	void DFS(void(*operation)(Node<T>*)) {
		DFS_preorder(root, operation);
	}

	void DFS_preorder(Node<T>* current, void(*operation)(Node<T>*)) {
		if (current != NULL) {
			operation(current);
			DFS_preorder(current->left, operation);
			DFS_preorder(current->right, operation);
		}
	}

	void BFS(void(*operation)(Node<T>*)) {
		std::queue<Node<T>*> q;
		q.push(root);
		Node<T>* node, * position = nullptr;
		while (!q.empty()) {
			node = q.front();
			q.pop();
			operation(node);
			if (node->left != nullptr)
				q.push(node->left);
			if (node->right != nullptr)
				q.push(node->right);
		}
	}

	void insert(T value) {
		this->flag = 0;
		if (root == nullptr) {
			root = new Node<T>(value);
		}
		else {
			insert_dfs(value, root);
		}
	}

	void insert_dfs(T value,Node<T>* cur){
		if (this->flag == 1) { 
			return; 
		}
		else{
			if (cur->left == nullptr && this->flag == 0) {
				Node<T>* newNode = new Node<T>(value);
				cur->left = newNode;
				this->flag = 1;
				return;
			}
			else {
				if (cur->right == nullptr && this->flag == 0) {
					Node<T>* newNode = new Node<T>(value);
					cur->right = newNode;
					this->flag = 1;
					return;
				}
				else{
					insert_dfs(value, cur->left);
					insert_dfs(value, cur->right);
				}
			}
		}

	}
	Node<T>* find(T value){

		return find_dfs(value, root);
	}

	Node<T>* find_dfs(T value, Node<T>* cur) {
		if (cur->data == value) {
			return cur;
		}
		if (cur->left != nullptr) {
			find_dfs(value, cur->left);
		}
		if (cur->right != nullptr) {
			find_dfs(value, cur->right);
		}
		return cur;
	}
	void del(Node<T>* node){
		if (node == nullptr) {
			return;
		}
		if (node->left != nullptr) {
			del(node->left);
		}
		if (node->right != nullptr) {
			del(node->right);
		}
		node->left = nullptr;
		node->right = nullptr;
		delete node;
	}
	
	void replace(Node<T>* replaceable, T value) {
		if (root == nullptr || replaceable == nullptr) {
			insert(value);
			return;
		}
		if (root == replaceable) {
			root->data = value;
		}
		replace_dfs(replaceable, value, root);
	}

	void replace_dfs(Node<T>* replaceable, T value, Node<T>* cur) {
		if (cur == nullptr) {
			std::cout << "replacement is not possible" << std::endl;
			return;
		}
		if (cur->left == replaceable) {
			cur->left->data = value;
			return;
		}
		if (cur->right == replaceable) {
			cur->right->data = value;
			return;
		}
		replace_dfs(replaceable, value, cur->left);
		replace_dfs(replaceable, value, cur->right);
	}

};
#endif // !BINARY_H