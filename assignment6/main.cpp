/*Date: 6/12/2019
show a list of composer's info*/
#include"Node.h"
#include"LinkedList.h"
#include"Composer.h"
#include<iostream>
#include<fstream>
#include<string>
#include <cstdlib>
using namespace std;

void populateListFromFile(ifstream&, LinkedList<Composer>&);
char promptToChoose();
void execution(char, LinkedList<Composer>&);

int main() {
	ifstream inFile;
	LinkedList<Composer> list;

	inFile.open("composer.txt");
	if (!inFile)
		cout << "Open error!" << endl;

	populateListFromFile(inFile, list);
	inFile.close();

	char cc = ' ';
	do {
		cc = promptToChoose();
		execution(cc, list);
	} while (cc != 'e');

	return 0;
}
/*receives an file and an object of LinkedList.
returns nothing.
to build the list of composer.*/
void populateListFromFile(ifstream& inFile, LinkedList<Composer>& l) {
	string name, line;
	int year;

	while (!inFile.eof()) {
		getline(inFile, line);
		int pos = line.find(',', 0);
		name = line.substr(0, pos);
		year = stoi(line.substr(pos + 2, line.size() - pos - 1));
		l.insert(Composer(name, year));
	}
}
/*receives nothing and returns a character.
to prompt user to enter a choice.*/
char promptToChoose() {
	char choice;
	cout << "Enter 's' to search, 'r' to remove, 'd' to display, or 'e' to exit: ";
	cin >> choice;

	while (!(choice == 's' || choice == 'r' || choice == 'd' || choice == 'e')) {
		cout << "Error, please enter again: ";
		cin >> choice;
	}
	return choice;
}
/*receives a character and an object of LinkedList.
returns nothing.
to excute the user's choice.*/
void execution(char c, LinkedList<Composer>& l) {
	string name;
	switch (c) {
	case 's':
		cout << "Enter a composer's name to search for: ";
		cin.ignore();
		getline(cin, name);

		if (l.find(Composer(name))) {
			cout << "\n\t" << name << " was found in the list.\n\n";
		}
		else {
			cout << "\n\t" << name << " was not found in the list.\n\n";
		}
		break;
	case 'r':
		cout << "Enter a composer's name to remove: ";
		cin.ignore();
		getline(cin, name);
		if (l.remove(Composer(name)))
			cout << "\n\t" << name << " was successfully removed from the list.\n\n";
		else
			cout << "\n\t" << name << " was not found in the list when attempting to remove.\n\n";
		break;
	case 'd':
		cout << endl;
		l.printList();
		break;
	}
}

/*Sample Run:
Enter 's' to search, 'r' to remove, 'd' to display, or 'e' to exit: d

Claudio Monteverdi - 1643
Henry Purcell - 1695
Antonio Vivaldi - 1741
Johann Sebastian Bach - 1750
George Frideric Handel - 1759
Wolfgang Amadeus Mozart - 1791
Joseph Haydn - 1809
Ludwig van Beethoven - 1827
Franz Schubert - 1828
Felix Mendelssohn - 1847
Frederic Chopin - 1849
Robert Schumann - 1856
Hector Berlioz - 1869
Richard Wagner - 1883
Franz Liszt - 1886
Pyotr Ilyich Tchaikovsky - 1893
Johannes Brahms - 1897
Giuseppe Verdi - 1901
Antonin Dvorak - 1904
Edvard Grieg - 1907
Gustav Mahler - 1911
Claude Debussy - 1918
Camille Saint-Saens - 1921
Giacomo Puccini - 1924
George Gershwin - 1937
Maurice Ravel - 1937
Sergei Rachmaninoff - 1943
Bela Bartok - 1945
Arnold Schoenberg - 1951
Sergei Prokofiev - 1953
Igor Stravinsky - 1971
Dmitri Shostakovich - 1975
Leonard Bernstein - 1990
Aaron Copland - 1990

Enter 's' to search, 'r' to remove, 'd' to display, or 'e' to exit: s
Enter a composer's name to search for: Franz Liszt

		Franz Liszt was found in the list.

Enter 's' to search, 'r' to remove, 'd' to display, or 'e' to exit: s
Enter a composer's name to search for: Hanz Zimmer

		Hanz Zimmer was not found in the list.

Enter 's' to search, 'r' to remove, 'd' to display, or 'e' to exit: r
Enter a composer's name to remove: Camille Saint-Saens

		Camille Saint-Saens was successfully removed from the list.
Enter 's' to search, 'r' to remove, 'd' to display, or 'e' to exit: r
Enter a composer's name to remove: CPE Bach

		CPE Bach was not found in the list when attempting to remove.
Enter 's' to search, 'r' to remove, 'd' to display, or 'e' to exit: d

Claudio Monteverdi - 1643
Henry Purcell - 1695
Antonio Vivaldi - 1741
Johann Sebastian Bach - 1750
George Frideric Handel - 1759
Wolfgang Amadeus Mozart - 1791
Joseph Haydn - 1809
Ludwig van Beethoven - 1827
Franz Schubert - 1828
Felix Mendelssohn - 1847
Frederic Chopin - 1849
Robert Schumann - 1856
Hector Berlioz - 1869
Richard Wagner - 1883
Franz Liszt - 1886
Pyotr Ilyich Tchaikovsky - 1893
Johannes Brahms - 1897
Giuseppe Verdi - 1901
Antonin Dvorak - 1904
Edvard Grieg - 1907
Gustav Mahler - 1911
Claude Debussy - 1918
Giacomo Puccini - 1924
George Gershwin - 1937
Maurice Ravel - 1937
Sergei Rachmaninoff - 1943
Bela Bartok - 1945
Arnold Schoenberg - 1951
Sergei Prokofiev - 1953
Igor Stravinsky - 1971
Dmitri Shostakovich - 1975
Leonard Bernstein - 1990
Aaron Copland - 1990

Enter 's' to search, 'r' to remove, 'd' to display, or 'e' to exit: e

C:\Users\huich\Documents\De Anza\2019spring\C++22B\huichan\Debug\huichan.exe (process 8312) exited with code 0.
*/