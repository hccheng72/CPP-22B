#include<iostream>
#include<string>
#include"Composer.h"
using namespace std;

/*it receives two objects and returns one object.
to display the Composer object.*/
ostream &operator<<(ostream &out, const Composer &obj) {
	out << obj.name << " - " << obj.year;
	return out;
}

/*it receives an object and returns boolean result.
to operate as "<".*/
bool Composer::operator<(const Composer &right) {
	if (year < right.year)
		return true;
	else
		return false;
}

/*it receives an object and returns boolean result.
to operate as "==".*/
bool Composer::operator==(const Composer &right) {
	if (name == right.name)
		return true;
	else
		return false;
}

/*it receives an object and returns boolean result.
to operate as "!=".*/
bool Composer::operator!=(const Composer &right) {
	if (*this == right)
		return false;
	else
		return true;
}