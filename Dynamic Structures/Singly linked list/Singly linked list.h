#include<iostream>

template<typename T>
class Node {
public:
	T data;
	Node* next;
	Node(T data = T(), Node* next = nullptr) {
		this->data = data;
		this->next = next;
	}
	Node(const Node& p) {
		data = p.data;
		next = p.next;
	}
	~Node() {}
};

template<typename T>
class Singly_linked_list {
	Node<T>* head;
	int size;
public:
	Singly_linked_list() {
		size = 0;
		head = nullptr;
	}
	Singly_linked_list(int size, Node<T>* head) {
		this->size = size;
		this->head = head;
	}
	Singly_linked_list(const Singly_linked_list& p) {
		head = p.head;
		size = p.size;
	}
	~Singly_linked_list() {
		clear();
	}

	void pop_front() {
		Node<T>* current = this->head;
		this->head = current->next;
		current->next = nullptr;
		delete current;
		size--;
	}

	void pop_back() {
		Node<T>* current = this->head;
		while (current->next != nullptr) {
			current = current->next;
		}
		delete current;
		size--;
	}

	void push_back(T data) {
		if (head == nullptr) {
			head = new Node<T>(data);
		}
		else {
			Node<T>* current = this->head;
			while (current->next != nullptr) {
				current = current->next;
			}
			current->next = new Node<T>(data);
		}
		size++;
	}

	void push_front(T data) {
		this->head = new Node<T>(data, head);
		size++;
	}

	void insert(T data, int ind) {
		if (ind == 0) {
			push_front(data);
		}
		Node<T>* current = this->head;
		for (int i = 0; i < ind - 1; i++) {
			current = current->next;
		}
		Node<T>* newNode = new Node<T>(data, current->next);
		current->next = newNode;
	}

	void removeNode(int ind) {
		if (ind == 0) {
			pop_front();
		}
		if (ind == size - 1) {
			pop_back();
		}
		Node<T>* current = this->head;
		for (int i = 0; i < ind - 1; i++) {
			current = current->next;
		}
		Node<T>* delNode = current->next;
		current->next = delNode->next;
		delete delNode;
		size--;
	}

	void clear() {
		while (size) {
			pop_front();
		}
	}

	int getSize() { return size; }

	T& operator[](const int ind) {
		if (ind >= this->size) {
			std::cout<<"nevern"<<std::endl;
		}
		else {
			int count = 0;
			Node<T>* current = this->head;
			while (count != ind) {
				current = current->next;
				count++;
			}
			return current->data;
		}
	}
};