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

	void del(Node<T>* node) {
		if (node != nullptr) {
			del(node->left);
			del(node->right);
			delete node;
		}
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

	void inorderDFS(Node<T>* node) {
		if (node == nullptr) {
			return;
		}

		inorderDFS(node->left);

		std::cout << node->data << " ";

		inorderDFS(node->right);
	}

	void postorderDFS(Node<T>* node) {
		if (node == nullptr) {
			return;
		}

		postorderDFS(node->left);

		postorderDFS(node->right);

		std::cout << node->data << " ";
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

	void insert(const T& value) {
		Node<T>* newNode = new Node<T>(value);
		if (root == nullptr) {
			root = newNode;
			return;
		}

		std::queue<Node<T>*> q;
		q.push(root);

		while (!q.empty()) {
			Node<T>* current = q.front();
			q.pop();

			if (current->left != nullptr) {
				q.push(current->left);
			}
			else {
				current->left = newNode;
				break;
			}

			if (current->right != nullptr) {
				q.push(current->right);
			}
			else {
				current->right = newNode;
				break;
			}
		}
	}

	Node<T>* find(const T& value) {
		
		if (root == nullptr) {
			std::cout << "the tree is empty" << std::endl;
			return nullptr;
		}

		std::queue<Node<T>*> q;
		q.push(root);

		while (!q.empty()) {
			Node<T>* current = q.front();
			q.pop();

			if (current->data == value) {
				return current;
			}

			if (current->left != nullptr) {
				q.push(current->left);
			}
			if (current->right != nullptr) {
				q.push(current->right);
			}
			
		}
		return nullptr;
	}

	void remove(const T& value) {
		Node<T>* deleted = find(value);
		Node<T>* parentDeleted = findParent(deleted);
		
		if ((deleted->left == nullptr) && (deleted->right == nullptr)) {
			if (parentDeleted->left == deleted) {
				parentDeleted->left = nullptr;
			}
			if (parentDeleted->right == deleted) {
				parentDeleted->right = nullptr;
			}
			delete deleted;
			return;
		}

		Node<T>* deep = findDeepestElement();
		Node<T>* parentDeep = findParent(deep);

		if (parentDeep->left == deep) {
			parentDeep->left = nullptr;
		}
		if (parentDeep->right == deep) {
			parentDeep->right = nullptr;
		}

		if (deleted != root) {
			if (parentDeleted->left == deleted) {
				parentDeleted->left = deep;
			}
			if (parentDeleted->right == deleted) {
				parentDeleted->right = deep;
			}
		}
		
		deep->left = deleted->left;
		deep->right = deleted->right;
		if (deleted == root) {
			root = deep;
		}
		delete deleted;
	}

	Node<T>* findParent(Node<T>* node) {
		if (root == nullptr) {
			return nullptr;
		}

		std::queue<Node<T>*> q;
		q.push(root);

		while (!q.empty()) {
			Node<T>* current = q.front();
			q.pop();

			if (current->left != nullptr) {
				if (current->left == node) {
					return current;
					break;
				}
				q.push(current->left);
			}
			if (current->right != nullptr) {
				if (current->right == node) {
					return current;
					break;
				}
				q.push(current->right);
			}
		}

		return nullptr;
	}

	Node<T>* findDeepestElement() {
		if (!root) {
			return nullptr;
		}

		Node<T>* deepestNode = nullptr;

		std::queue<Node<T>*> q;
		q.push(root);

		while (!q.empty()) {
			Node<T>* current = q.front();
			q.pop();

			deepestNode = current;

			if (current->left != nullptr) {
				q.push(current->left);
			}
			if (current->right != nullptr) {
				q.push(current->right);
			}
		}

		return deepestNode;
	}


	void printTree() {
		if (!root) {
			std::cout << "Tree is empty\n";
			return;
		}

		printTreeHelper(root, 0);
	}

	void printTreeHelper(Node<T>* node, int depth) {
		if (node == nullptr) {
			return;
		}

		printTreeHelper(node->right, depth + 1);

		std::cout << std::string(depth * 4, ' ') << node->data << "\n";

		printTreeHelper(node->left, depth + 1);
	}

	void treeHeight() {
		std::cout << "Height of tree:" << maxDepth(root) << "\n";
	}

	int maxDepth(Node<T>* node) {
		if (node == nullptr) {
			return 0;
		}

		int leftDepth = maxDepth(node->left);
		int rightDepth = maxDepth(node->right);
		int height = 1 + std::max(leftDepth, rightDepth);
		return height;
	}

	int getNodeCount() const {
		if (!root) {
			return 0;
		}

		int count = 0;
		std::queue<Node<T>*> q;
		q.push(root);

		while (!q.empty()) {
			Node<T>* current = q.front();
			q.pop();
			count++;

			if (current->left) {
				q.push(current->left);
			}
			if (current->right) {
				q.push(current->right);
			}
		}

		return count;
	}

	int getLevel(Node<T>* node) const {
		if (root == nullptr) {
			return -1;
		}

		std::queue<std::pair<Node<T>*, int>> q;
		q.push({ root, 0 });

		while (!q.empty()) {
			Node<T>* current = q.front().first;
			int level = q.front().second;
			q.pop();

			if (current == node) {
				return level;
			}

			if (current->left != nullptr) {
				q.push({ current->left, level + 1 });
			}

			if (current->right != nullptr) {
				q.push({ current->right, level + 1 });
			}
		}

		return -1;
	}

	void printLevelOfNode(const T& value) {
		if (!root) {
			std::cout << "Tree is empty\n";
			return;
		}

		std::queue<Node<T>> q;
		std::queue<int> levelQueue;
		q.push(root);
		levelQueue.push(0);

		while (!q.empty()) {
			Node<T> current = q.front();
			int level = levelQueue.front();
			q.pop();
			levelQueue.pop();

			if (current->data == value) {
				std::cout << "Level of node " << value << " is: " << level << std::endl;
				return;
			}

			if (current->left) {
				q.push(current->left);
				levelQueue.push(level + 1);
			}

			if (current->right) {
				q.push(current->right);
				levelQueue.push(level + 1);
			}
		}

		std::cout << "Node " << value << " not found in the tree\n";
	}
};
#endif // !BINARY_H