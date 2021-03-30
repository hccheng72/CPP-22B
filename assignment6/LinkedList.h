#pragma once
#include"Node.h"
#include<iostream>
#include<string>
#include <cstdlib>
using namespace std;

template <class T>
class LinkedList {
private:
	Node<T> *head;
	Node<T> *tail;
public:
	LinkedList();
	~LinkedList();
	void printList() const;
	void append(const T data);
	void prepend(const T data);
	void removeFront();
	void insert(const T data);
	bool remove(const T data);
	bool find(const T data);
	bool isEmpty() const;
	T getFirst() const;
	T getLast() const;
};

/*default constructor.
it receives and return nothing.*/
template <class T>
LinkedList<T>::LinkedList() {
	head = tail = nullptr;
}

/*destructor. 
it receives and return nothing.*/
template <class T>
LinkedList<T>::~LinkedList() {
	Node<T> *temp;
	Node<T> *iter = head;
	while (iter) {
		temp = iter->next;
		delete iter;
		iter = temp;
	}
	head = tail = nullptr;
}

/*Displays all elements in linked list.
it receives and return nothing.*/
template <class T>
void LinkedList<T>::printList() const {
	if (head) {
		Node<T> *iter = head;
		while (iter != nullptr) {
			cout << iter->value << endl;
			iter = iter->next;
		}
		cout << endl;
	}
	else
		cout << "Empety list\n";
}

/*Adds a node to the end of the list.
it receives T data and returns nothing.*/
template <class T>
void LinkedList<T>::append(const T data) {
	Node<T> *temp = new Node<T>;
	temp->value = data;

	if (!head) {
		head = tail = temp;
	}
	else {
		tail->next = temp;
		tail = temp;
	}
}

/*Adds a node to the front of the list.
it receives T data and returns nothing.*/
template <class T>
void LinkedList<T>::prepend(const T data) {
	Node<T> *temp = new Node<T>;
	temp->value = data;
	if (!head) {
		head = tail = temp;
	}
	else {
		temp->next = head;
		head = temp;
	}
}

/*Removes the front node.
it receives T data and returns nothing.*/
template <class T>
void LinkedList<T>::removeFront() {
	if (!head)
		return;
	else {
		Node<T> *temp = head;
		if (tail == head)
			tail = nullptr;
		head = temp->next;
		delete temp;
	}
}

/*Accepts a value and will insert the value into the 
linked list in the correct order. it returns nothing.*/
template <class T>
void LinkedList<T>::insert(const T data) {
	Node<T> *temp = new Node<T>;
	temp->value = data;
	Node<T> *nodePtr = head;
	Node<T> *preNodePtr = nullptr;

	if (!head)
		head = tail = temp;
	else {
		while (nodePtr != nullptr && nodePtr->value < data) {
			preNodePtr = nodePtr;
			nodePtr = nodePtr->next;
		}
		if (preNodePtr == nullptr) {
			head = temp;
			temp->next = nodePtr;
		}
		else {
			preNodePtr->next = temp;
			temp->next = nodePtr;
			if (preNodePtr == tail)
				tail = temp;
		}
	}
}

/*Accepts a value and will remove the node with that value from the list.
it returns a boolean result.*/
template <class T>
bool LinkedList<T>::remove(const T data) {
	Node<T> *nodePtr = head;
	Node<T> *preNodePtr = nullptr;
	if (!head)
		return false;
	else if (head->value == data) {
		nodePtr = head->next;
		delete head;
		head = nodePtr;
		return true;
	}
	else {
		while (nodePtr != nullptr && nodePtr->value != data) {
			preNodePtr = nodePtr;
			nodePtr = nodePtr->next;
		}
		if (nodePtr) {
			preNodePtr->next = nodePtr->next;
			if (tail == nodePtr)
				tail = preNodePtr;
			delete nodePtr;
			return true;
		}
		else
			return false;
	}
}

/*Accepts a value and will search for that value in the linked list.
it returns a boolean result.*/
template <class T>
bool LinkedList<T>::find(const T data) {
	Node<T> *iter = head;
	while (iter) {
		if (iter->value == data)
			return true;
		iter = iter->next;
	}
	return false;
}

/*Returns true if list is empty and false otherwise.
it receives nothing and returns a boolean result.*/
template <class T>
bool LinkedList<T>::isEmpty() const {
	if (!head)
		return true;
	else
		return false;
}

/*Returns the value stored in the first node of the list.
it receives nothing.*/
template <class T>
T LinkedList<T>::getFirst() const {
	if (head)
		return head->value;
	else {
		cout << "ERROR: empety list.\n";
		exit(EXIT_FAILURE);
	}
}

/*Returns the value stored in the last node of the list.
it receives nothing.*/
template <class T>
T LinkedList<T>::getLast() const {
	if (tail)
		return tail->value;
	else {
		cout << "ERROR: empety list.\n";
		exit(EXIT_FAILURE);
	}
}