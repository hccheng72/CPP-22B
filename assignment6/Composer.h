#pragma once
#include <iostream>
#include<string>
using namespace std;

class Composer {
private:
	string name;
	int year;
public:
	Composer(string s = " ", int n = 0) : name(s), year(n) {};
	friend ostream &operator<<(ostream &out, const Composer &obj);
	bool operator<(const Composer &right);
	bool operator==(const Composer &right);
	bool operator!=(const Composer &right);
};

