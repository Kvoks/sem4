#include<iostream>
#include"Singly linked list.h"
using namespace std;

int main() {
	Singly_linked_list<int> lst;
	lst.push_back(5);
	lst.push_back(7);
	lst.push_back(101);
	cout << lst.getSize() << endl;
	for (int i = 0; i < lst.getSize(); i++)
	{
		cout << lst[i] << endl;
	}

	cout << endl << "pop_front " << endl << endl;

	lst.pop_front();

	for (int i = 0; i < lst.getSize(); i++)
	{
		cout << lst[i] << endl;
	}
	cout << lst.getSize() << endl;

	lst.clear();

	cout << lst.getSize() << endl;

	return 0;
}