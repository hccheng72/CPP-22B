#pragma once
#include <iostream>
#include<string>
using namespace std;

template <class T>
class Node {
public:
	T value;
	Node *next = nullptr;
};