/*
Date: 5/16/2019
This program acts like a vending machine. You can enter 
a number of quarters and choose what you wanna buy.
*/
#include<iostream>
#include<string>
#include<ctime>
#include<iomanip>
#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS
using namespace std;

class Snack {
private:
	string name;
	double price;
	int num_stock, num_sold;
	string *ptrTime = nullptr;

	/* It generates the time when called. 
	It accepts nothing and retures a string of time.*/
	string getCurrentTime() {
		time_t t = time(0);
		struct tm ts;
		char buff[10];
		ts = *localtime(&t);
		strftime(buff, sizeof(buff), "%X", &ts);
		return buff;
	}

public:
	/*default constructor. It accepts nothing and returns nothing.*/
	Snack() {
		name = " ";
		price = 0.0;
		num_stock = 0;
		num_sold = 0;
	}
	
	/*overloaded constructor. It accepts snack name, snack price and 
	number of stock. It returns nothing.*/
	Snack(string snackName, double snackPrice, int stockNum) {
		name = snackName;
		price = snackPrice;
		num_stock = stockNum;
		num_sold = 0;
		ptrTime = new string[num_stock + 1];
	}
	
	/*setter. It aceepts snack name and returns nothing.*/
	void setName(string snackName) {
		name = snackName;
	}
	
	/*setter. It aceepts snack price and returns nothing.*/
	void setPrice(double snackPrice) {
		price = snackPrice;
	}
	
	/*setter. It aceepts number of stock and returns nothing.*/
	void setNumStock(int stockNum) {
		num_stock = stockNum;
		ptrTime = new string[num_stock + 1];
	}
	
	/*getter. It accepts nothing and returns the snack name.*/
	string getName() const {
		return name;
	}
	
	/*getter. It accepts nothing and returns the snack price.*/
	double getPrice() const {
		return price;
	}
	
	/*getter. It accepts nothing and returns the number of stock.*/
	int getNumStock() const {
		return num_stock;
	}
	
	/*getter. It accepts nothing and returns the number of sold.*/
	int getNumSold() const {
		return num_sold;
	}
	
	/*It accepts a value of money and returns true or false. It proceeds whether 
	the buying succeds or not and makes records of trading time and numbers.*/
	bool buyItem(double &moneyEntered) {
		if (moneyEntered >= price) {
			if (num_stock > 0) {
				moneyEntered -= price;
				num_stock--;
				num_sold++;
				cout << "Item has been dispensed below." << endl;
				*(ptrTime + num_sold - 1) = getCurrentTime();
				return true;
			}
			else {
				cout << "Error: item is sold-out!" << endl;
				return false;
			}
		}
		else {
			cout << "The money you entered is insufficient." << endl;
			return false;
		}
	}

	/*destructor. It doesn't aceept or return anything. It shows the 
	trading info and delete data in heap.*/
	~Snack() {
		cout << "\n\nClosing info for " << name << ":" << endl;
		cout << "\t" << num_stock << " in stock" << endl;
		cout << "\t" << num_sold << " sold for a profit of $" 
			<< num_sold * price << endl;

		if (*ptrTime != "\0") {
			cout << "\nTransactions occurred at:" << endl;
			int i = 0;
			while (*(ptrTime + i) != "\0") { //
				cout << "\t" << *(ptrTime + i) << endl;
				i++;
			}
		}
		delete[]ptrTime;
		ptrTime = nullptr;
	}
};

void displayVendingMachine(const Snack[], int);
double getQuarters();
void userBuyItem(Snack[], int);
bool promptToContinue();

int main() {
	Snack arr[3] = { {}, { "Candy", 1.25, 5 }, { "Soda", 1.00, 2 } };

	arr[0].setName("Chips");
	arr[0].setPrice(1.75);
	arr[0].setNumStock(3);

	cout << "Welcome to the vending machine!" << endl;

	do {
		userBuyItem(arr, 3);
	} while (promptToContinue());

	return 0;
}

/*1. It accepts the array of Snack objects and the number of elements 
in the array.
2. It returns nothing.
3. It displays the vending machine’s contents.*/
void displayVendingMachine(const Snack ary[], int size) {

	cout << left << setw(8) << "\nItem #" << setw(11) << "Item Name"
		<< setw(7) << "Price" << setw(10) << "# in-stock" << endl;
	cout << "------------------------------------" << endl;
	for (int i = 0; i < size; i++) {
		cout << left << setw(8) << (i + 1) << setw(11) << ary[i].getName()
			<< setw(7) << ary[i].getPrice() << setw(10) << ary[i].getNumStock()
			<< endl;
	}
}

/*1. It accepts nothing.
2. It returns the value of money.
3. It prompts the user to enter a number of quarters and converts 
it to a value.*/
double getQuarters() {
	int num_quarter;
	double value;
	do {
		cout << "\nEnter a number of quarters: ";
		cin >> num_quarter;
		if (num_quarter < 1)
			cout << "Please enter a number greater than 0." << endl;
	} while (num_quarter < 1);

	value = 0.25*num_quarter;
	return value;
}

/*1. It accepts the array of Snack objects and the number of elements 
in the array.
2. It returns nothing.
3. It proceeds the buying process.*/
void userBuyItem(Snack ary[], int size) {
	int item;
	double value;

	displayVendingMachine(ary, size);
	value = getQuarters();
	cout << setprecision(2) << fixed << "Amount Entered: $"
		<< value << endl;

	do {
		cout << "\nEnter a number between 1 and 3 to make your selection: ";
		cin >> item;

		if (item < 1 || item > 3)
			cout << "Error! The number should be between 1 and 3." << endl;
	} while (item < 1 || item > 3);

	bool result;
	result = (ary[item - 1].buyItem(value));

	if (value > 0)
		cout << "$" << value << " dispensed below." << endl;
}

/*1. It accepts nothing.
2. It returns true or false for whether to continue or not.
3. This function will ask the user if they want to continue 
running the program.*/
bool promptToContinue() {
	string cont;

	do {
		cin.ignore();
		cout << "\nContinue? (Y / N): ";
		cin >> cont;
	} while (!(cont == "y" || cont == "Y" || cont == "n" || cont == "N"));

	if (cont == "Y" || cont == "y")
		return true;
	else
		return false;
}

/* Sample Run:
Welcome to the vending machine!

Item # Item Name  Price  # in - stock
------------------------------------
1       Chips      1.75   3
2       Candy      1.25   5
3       Soda       1      2

Enter a number of quarters : -1
Please enter a number greater than 0.

Enter a number of quarters : 8
Amount Entered : $2.00

Enter a number between 1 and 3 to make your selection : 3
Item has been dispensed below.
$1.00 dispensed below.

Continue ? (Y / N) : y

Item # Item Name  Price  # in - stock
------------------------------------
1       Chips      1.75   3
2       Candy      1.25   5
3       Soda       1.00   1

Enter a number of quarters : 4
Amount Entered : $1.00

Enter a number between 1 and 3 to make your selection : 3
Item has been dispensed below.

Continue ? (Y / N) : y

Item # Item Name  Price  # in - stock
------------------------------------
1       Chips      1.75   3
2       Candy      1.25   5
3       Soda       1.00   0

Enter a number of quarters : 4
Amount Entered : $1.00

Enter a number between 1 and 3 to make your selection : 3
Error : item is sold - out!
	$1.00 dispensed below.

	Continue ? (Y / N) : y

	Item # Item Name  Price  # in - stock
	------------------------------------
	1       Chips      1.75   3
	2       Candy      1.25   5
	3       Soda       1.00   0

	Enter a number of quarters : 10
	Amount Entered : $2.50

	Enter a number between 1 and 3 to make your selection : 1
	Item has been dispensed below.
	$0.75 dispensed below.

	Continue ? (Y / N) : y

	Item # Item Name  Price  # in - stock
	------------------------------------
	1       Chips      1.75   2
	2       Candy      1.25   5
	3       Soda       1.00   0

	Enter a number of quarters : 5
	Amount Entered : $1.25

	Enter a number between 1 and 3 to make your selection : 2
	Item has been dispensed below.

	Continue ? (Y / N) : y

	Item # Item Name  Price  # in - stock
	------------------------------------
	1       Chips      1.75   2
	2       Candy      1.25   4
	3       Soda       1.00   0

	Enter a number of quarters : 9
	Amount Entered : $2.25

	Enter a number between 1 and 3 to make your selection : 1
	Item has been dispensed below.
	$0.50 dispensed below.

	Continue ? (Y / N) : n


	Closing info for Soda :
	0 in stock
	2 sold for a profit of $2.00

	Transactions occurred at :
17 : 56 : 36
17 : 56 : 56


Closing info for Candy :
	4 in stock
	1 sold for a profit of $1.25

	Transactions occurred at :
17 : 58 : 03


Closing info for Chips :
	1 in stock
	2 sold for a profit of $3.50

	Transactions occurred at :
17 : 57 : 49
17 : 58 : 18
*/