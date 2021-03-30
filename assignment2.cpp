/*This program could determine the letter grade for students at a school
after keying students and thieir test scores.
Date: 4/26/2019*/

#include <iostream>
#include <string>
using namespace std;

int inputData(string*&, double**&);
char* calcGrade(double**, int);
void displayData(string*, double**, char*, int);
void cleanHeap(string*, double**, char*, int);

int main() {
	int numStudent;
	string *namePtr = nullptr;
	double **scoresPtr = nullptr;
	char *letterPtr = nullptr;

	numStudent = inputData(namePtr, scoresPtr);
	letterPtr = calcGrade(scoresPtr, numStudent);
	displayData(namePtr, scoresPtr, letterPtr, numStudent);
	cleanHeap(namePtr, scoresPtr, letterPtr, numStudent);

	return 0;
}

/*
1-The inputData function accepts a string pointer and a pointer to a double
pointer, both passed by reference.
2-It will return the number of studnets.
3-It asks user to key in the information of students and their scores*/

int inputData(string *&namePtr, double **&scoresPtr) {
	int numStudent = 0;
	while (numStudent < 1) {
		cout << "How many students do you have in the system? ";
		cin >> numStudent;

		if (numStudent < 1)
			cout << "The number shouldn't be less than 1." << endl;
	}

	namePtr = new string[numStudent];
	scoresPtr = new double*[numStudent];

	for (int x = 0; x < numStudent; x++) {
		cout << endl << "Enter the student's name: ";
		cin.ignore();
		getline(cin, *(namePtr + x));

		int numTest = 0;
		while (numTest < 1) {
			cout << "Enter how many tests " << *(namePtr + x) << " took: ";
			cin >> numTest;

			if (numTest < 1)
				cout << "The number shouldn't be less than 1." << endl;
		}

		*(scoresPtr + x) = new double[numTest + 1];

		for (int y = 0; y < numTest; y++) {
			do {
				cout << "Enter grade # " << y + 1 << ": ";
				cin >> *(*(scoresPtr + x) + y);

				if (*(*(scoresPtr + x) + y) < 0 || *(*(scoresPtr + x) + y)
				> 100)
					cout << "Please enter a grade between 0 and 100." << endl;
			} while (*(*(scoresPtr + x) + y) < 0 || *(*(scoresPtr + x) + y) > 100);

			*(*(scoresPtr + x) + numTest) = -1;
		}

	}
	return numStudent;

}

/*
1-The calcGrade function accepts a pointer to the array of student test
scores and the number of students.
2-The function will return a pointer to the dynamically-allocated array
containing every student’s letter grade.
3-The function will calculate each student’s average test score, and convert
the score to a letter grade.*/

char* calcGrade(double**scoresPtr, int numStudent) {

	char *letterPtr = nullptr;
	letterPtr = new char[numStudent];

	for (int x = 0; x < numStudent; x++) {
		int i = 0;
		double total = 0, average = 0;

		while (*(*(scoresPtr + x) + i) > 0) {
			total += *(*(scoresPtr + x) + i);
			i++;
		}
		average = total / i;

		if (average >= 90)
			*(letterPtr + x) = 'A';
		else if (average >= 80)
			*(letterPtr + x) = 'B';
		else if (average >= 70)
			*(letterPtr + x) = 'C';
		else if (average >= 60)
			*(letterPtr + x) = 'D';
		else
			*(letterPtr + x) = 'F';
	}
	return letterPtr;
}

/*
1-The displayData function accepts a pointer to the array of student names,
a pointer to the array of student test scores, a pointer to the array of
student letter grades, and the number of students.
2-There's no return.
3-It displays the data including the number of students, names, all scores,
and letter grade.*/

void displayData(string*namePtr, double**scoresPtr, char*letterPtr,
	int numStudent) {

	cout << "\nYou have " << numStudent << " students in the system.\n";
	for (int x = 0; x < numStudent; x++) {
		cout << endl << "Name of student #" << x + 1 << ": ";
		cout << *(namePtr + x) << endl;
		cout << "Grades for student #" << x + 1 << ": ";

		int i = 0;
		while (*(*(scoresPtr + x) + i) > 0) {
			cout << *(*(scoresPtr + x) + i) << " ";
			i++;
		}
		cout << endl;

		cout << "Average of grades for student #" << x + 1 << ": ";
		cout << *(letterPtr + x) << endl;
	}
}

/*
1-The cleanHeap function accepts a pointer to the array of student names,
a pointer to the array of student test scores, a pointer to the array of
student letter grades, and the number of students.
2-There's no return.
3-It cleans up anything that was dynamically-allocated appropriately.*/

void cleanHeap(string*namePtr, double**scoresPtr, char*letterPtr,
	int numStudent) {

	delete[] namePtr;
	namePtr = nullptr;

	for (int x = 0; x < numStudent; x++) {
		delete[] * (scoresPtr + x);
		*(scoresPtr + x) = nullptr;
	}

	delete[] scoresPtr;
	scoresPtr = nullptr;

	delete[] letterPtr;
	letterPtr = nullptr;
}

/* Sample Run:
How many students do you have in the system? 3

Enter the student's name: John Doe
Enter how many tests John Doe took: 4
Enter grade # 1: 95.5
Enter grade # 2: 84.3
Enter grade # 3: 80
Enter grade # 4: 88.8

Enter the student's name: Anna Mull
Enter how many tests Anna Mull took: 3
Enter grade # 1: 60
Enter grade # 2: 55.9
Enter grade # 3: 77.4

Enter the student's name: Paige Turner
Enter how many tests Paige Turner took: -1
The number shouldn't be less than 1.
Enter how many tests Paige Turner took: 2
Enter grade # 1: 75.6
Enter grade # 2: -10.3
Please enter a grade between 0 and 100.
Enter grade # 2: 50.5

You have 3 students in the system.

Name of student #1: John Doe
Grades for student #1: 95.5 84.3 80 88.8
Average of grades for student #1: B

Name of student #2: Anna Mull
Grades for student #2: 60 55.9 77.4
Average of grades for student #2: D

Name of student #3: Paige Turner
Grades for student #3: 75.6 50.5
Average of grades for student #3: D
*/