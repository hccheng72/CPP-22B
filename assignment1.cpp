/*********
4/13/2019
This program will play a simple memory game with you by choosing two cards
each time. There are eight pairs, find all matches then you win the game.
*********/

#include <iostream>
#include <string>
#include <fstream>
#include <time.h>

const int LENGTH = 4;
using namespace std;

void InitializeCards(int cards[][LENGTH]);
void ShowCards(int cards[][LENGTH], bool faceup[][LENGTH]);

void InitializeCards(int cards[][LENGTH]) {
	//seed rand() - remember to always do this before using rand()
	// also make sure to include the <time.h> library.
	srand(time(NULL));
	int x1, y1, x2, y2;
	int i;
	int temp;

	// Place pairs in known locations -  this is how our array looks like after
	cards[0][0] = 1; cards[0][1] = 1;//   1  1  2  2
	cards[0][2] = 2; cards[0][3] = 2;
	cards[1][0] = 3; cards[1][1] = 3;//   3  3  4  4
	cards[1][2] = 4; cards[1][3] = 4;
	cards[2][0] = 5; cards[2][1] = 5;//   5  5  6   6
	cards[2][2] = 6; cards[2][3] = 6;
	cards[3][0] = 7; cards[3][1] = 7;//   7  7  8   8
	cards[3][2] = 8; cards[3][3] = 8;

	// Now that 2D has been initialized with 8 pairs, we want to shuffle the board so
	// that the pairs aren't right next to each other
	for (int i = 0; i < 30; i++) {
		//Get set of random coordinates and swap
		//First random coordinate on our 2d "grid"
		y1 = rand() % LENGTH;
		x1 = rand() % LENGTH;
		//Second random coordinate of our 2d "grid"
		y2 = rand() % LENGTH;
		x2 = rand() % LENGTH;

		//Now we swap value at (x1, y1) with value at(x2, y2)
		temp = cards[x1][y1];
		cards[x1][y1] = cards[x2][y2];
		cards[x2][y2] = temp;
		//Note: just like with 1D arrays, modifying an n-dimensional array inside
		// a function will change the array itself
	}
}

// ======================
//     main function
// ======================
int main() {
	ofstream outfile;
	string name;
	string sentinel;
	bool faceup[LENGTH][LENGTH] = { false };
	int cards[LENGTH][LENGTH], x1, y1, x2, y2, counter = 0, found = 0;

	// Welcome the user and ask him to enter his full name.
	cout << "Welcome to my game!" << endl;
	cout << "Please enter your full name: ";
	getline(cin, name);
	cout << "Find all the matching pairs on the board!\n\n";

	// call InitializeCards function to create the board.
	InitializeCards(cards);

	do {
		// Display the current state of the game board.
		ShowCards(cards, faceup);

		// Prompt the user to enter the valid coordinates of two cards.
		do {
			cout << "\nEnter x and y position of the first card: ";
			cin >> x1 >> y1;
		} while (!(x1 >= 0 && x1 <= 3 && y1 >= 0 && y1 <= 3));

		do {
			cout << "Enter x and y position of the second card: ";
			cin >> x2 >> y2;
		} while (!(x2 >= 0 && x2 <= 3 && y2 >= 0 && y2 <= 3));

		// flip over the cards choosed to show the user the values
		faceup[x1][y1] = faceup[x2][y2] = true;
		cout << endl;
		ShowCards(cards, faceup);

		// If the values do not match, then flip them over again. 
		// Otherwise, keep them faceup forever.
		if (cards[x1][y1] != cards[x2][y2]) {
			faceup[x1][y1] = faceup[x2][y2] = false;
			cout << "No match." << endl << endl;
			cout << "Flipping cards over again." << endl;
		}
		else {
			cout << "Congrats! A match has been found." << endl;
			found++;
		}

		// If game isn't finished yet, ask user to proceed or not.
		if (found != 8) {
			cout << "Enter 'q' to quit or press any key to continue...";
			cin.ignore();
			getline(cin, sentinel);
		}
		else
			cout << "Well done! You've found out all pairs.";

		// accumulate how many turns have been used. 
		counter++;

	} while (!(sentinel == "q" || found == 8));

	// send data out to a file.
	outfile.open("output.txt");
	outfile << name << endl;
	if (found == 8)
		outfile << "You took " << counter << " turns to win the game.";
	else
		outfile << "Don’t give up";
	outfile.close();

	return 0;
}
// ======================
// ShowCards Function
// It receives the arrays of cards and faceup.
// We use this function to show each state of the board.
// If the faceup of the element is ture, the number will be shown.
// Otherwise, a '*' is shown at the position of the element.
// ======================
void ShowCards(int cards[][LENGTH], bool faceup[][LENGTH]) {
	cout << "   0 1 2 3" << endl;
	cout << "   ========" << endl;
	for (int x = 0; x < LENGTH; x++) {
		cout << x << "| ";
		for (int y = 0; y < LENGTH; y++) {
			if (!faceup[x][y])
				cout << "* ";
			else
				cout << cards[x][y] << " ";
		}
		cout << "|" << endl;
	}
	cout << "   ========" << endl;
}

// one input with an invalid value.
/*
Welcome to my game!
Please enter your full name : David
Find all the matching pairs on the board!

   0 1 2 3
   ========
0| * * * * |
1| * * * * |
2| * * * * |
3| * * * * |
   ========

Enter x and y position of the first card : 2 4

Enter x and y position of the first card :
*/

// Three inputs with valid values.
/*
Welcome to my game!
Please enter your full name: David
Find all the matching pairs on the board!

   0 1 2 3
   ========
0| * * * * |
1| * * * * |
2| * * * * |
3| * * * * |
   ========

Enter x and y position of the first card: 0 0
Enter x and y position of the second card: 1 4
Enter x and y position of the second card:
*/

// one input with the quit choice.
/*
Welcome to my game!
Please enter your full name: David
Find all the matching pairs on the board!

   0 1 2 3
   ========
0| * * * * |
1| * * * * |
2| * * * * |
3| * * * * |
   ========

Enter x and y position of the first card: 0 0
Enter x and y position of the second card: 0 1

   0 1 2 3
   ========
0| 8 6 * * |
1| * * * * |
2| * * * * |
3| * * * * |
   ========
No match.

Flipping cards over again.
Enter 'q' to quit or press any key to continue...q

Press any key to close this window . . .
*/