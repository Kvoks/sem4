#include<iostream>

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
};

//Node* create(int value, Node* l = nullptr, Node* r = nullptr){};
template <typename T>
class BinaryTree {
	Node<T> *root;	// корень
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

	void insert(T value) {
		if (root == nullptr) {
			root = new Node<T>(value);
		}
		insert_dfs(value, root);
	}

	void insert_dfs(T value,Node<T>* cur){
		if (cur->left == nullptr) {
			Node<T>* newNode = new Node<T>(value);
			cur->left = newNode;
			return;
		}
		if (cur->right == nullptr) {
			Node<T>* newNode = new Node<T>(value);
			cur->right = newNode;
			return;
		}
		insert_dfs(value, cur->left);
		insert_dfs(value, cur->right);
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
		if (node->left != nullptr) {
			del(node->left);
		}
		if (node->right != nullptr) {
			del(node->right);
		}
		delete node;
	}
	
	void remove(Node<T>* node) {
		//каким образом он должен заменить, в плане что и на что
	}
};
