/*Date: 5/26/2019
This program will give functionality through the
use of various overloaded operators*/
#include<iostream>
#include"Array.h"
using namespace std;

int main() {
	Array arr1(5), arr2(10);
	for (int i = 0; i < arr1.getSize(); i++)
		arr1[i] = i;
	for (int i = 0; i < arr2.getSize(); i++)
		arr2[i] = i;
	cout << "arr1 contains: " << arr1;
	cout << "arr2 contains: " << arr2;
	Array arr3(arr1);
	cout << "arr3 contains: " << arr3 << endl;
	arr2 = arr2;
	cout << "arr2 contains: " << arr2;
	arr3 = arr2;
	cout << "arr3 contains: " << arr3 << endl;
	cout << boolalpha; //Display booleans as 'true' or 'false' instead of 1 or 0
	cout << "arr2 == arr3: " << (arr2 == arr3) << endl;
	cout << "arr1 == arr3: " << (arr1 == arr3) << endl;
	cout << "arr1 < arr3: " << (arr1 < arr3) << endl << endl;
	arr3[0] = 100;
	cout << "New arr3: " << arr3;
	cout << "arr2 == arr3: " << (arr2 == arr3) << endl;
	cout << "arr1 == arr3: " << (arr1 == arr3) << endl;
	cout << "arr1 < arr3: " << (arr1 < arr3) << endl << endl;
	arr1 += arr2;
	cout << "arr1 += arr2: " << arr1 << endl;
	cout << "!arr1: " << !arr1;
	cout << "*arr1: " << *arr1 << endl << endl;
	cout << "arr1++: " << arr1++;
	cout << "arr1 is: " << arr1 << endl;
	cout << "--arr1: " << --arr1;
	cout << "arr1 is: " << arr1 << endl;
	cout << "Total number of elements in all arrays: " << Array::getNumberOfElements() << endl << endl;
	return 0;
}

/* Sample Run:
arr1 contains: 0 1 2 3 4
arr2 contains: 0 1 2 3 4 5 6 7 8 9
arr3 contains: 0 1 2 3 4

arr2 contains: 0 1 2 3 4 5 6 7 8 9
arr3 contains: 0 1 2 3 4 5 6 7 8 9

arr2 == arr3: true
arr1 == arr3: true
arr1 < arr3: false

New arr3: 100 1 2 3 4 5 6 7 8 9
arr2 == arr3: false
arr1 == arr3: false
arr1 < arr3: true

arr1 += arr2: 0 1 2 3 4 0 1 2 3 4 5 6 7 8 9

!arr1: 3 2 1 9 4 7 2 0 4 6 8 0 3 5 1
*arr1: 0

arr1++: 3 2 1 9 4 7 2 0 4 6 8 0 3 5 1
arr1 is: 4 3 2 10 5 8 3 1 5 7 9 1 4 6 2

--arr1: 3 2 1 9 4 7 2 0 4 6 8 0 3 5 1
arr1 is: 3 2 1 9 4 7 2 0 4 6 8 0 3 5 1

Total number of elements in all arrays: 35
*/