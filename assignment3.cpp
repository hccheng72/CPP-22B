/* Date: 5/4/2019
This program is creating a movie database by reading information in file. 
Then, user can search it by entering filename.*/
#include <iostream>
#include <string>
#include<fstream>
#include<iomanip>
using namespace std;

struct Movie {
	string title;
	double gross_total;
	string director;
	string release_date;
	int runtime;
};

int numberOfLines(ifstream&);
void populateMovieFromFile(ifstream&, Movie&);
void displayMovie(const Movie&);
Movie* createDatabase(int&);
bool caseInsensitiveCmp(string, string);
void findMovie(Movie*, int);
void saveToFile(const Movie&);
bool promptToContinue();
void displayFavorites();

int main() {
	int num_movies;
	Movie *ptr;
	bool exit;

	ptr = createDatabase(num_movies);

	do {
		findMovie(ptr, num_movies);
		exit = promptToContinue();
	} while (exit == 1);

	displayFavorites();

	delete[] ptr;
	ptr = nullptr;

	return 0;
}

/*
1- the function receives an input file.
2- returns an integer representing the number of lines in the file.
3- it counts how many movoies in the file.
*/
int numberOfLines(ifstream &inFile) {
	int count = 0;
	string temp;

	while (getline(inFile, temp))
		count++;

	inFile.clear();
	inFile.seekg(0, ios::beg);

	return count;
}

/*
1- The function receives an input file and a Movie object.
2- returns nothing.
3- it builds different kinds of info of a movie to a Movie object.
*/
void populateMovieFromFile(ifstream &inFile, Movie &object) {
	string str;

	getline(inFile, str);

	int pos1 = str.find(',', 0);
	object.title = str.substr(0, pos1);

	int pos2 = str.find(',', pos1 + 1);
	object.gross_total = stod(str.substr(pos1 + 2, pos2 - pos1 - 2));

	int pos3 = str.find(',', pos2 + 1);
	object.director = str.substr(pos2 + 2, pos3 - pos2 - 2);

	int pos4 = str.find(',', pos3 + 1);
	object.release_date = str.substr(pos3 + 2, pos4 - pos3 - 2);

	object.runtime = stoi(str.substr(pos4 + 2, str.size() - pos4 - 1));
}

/*
1- the function receives a Movie object passed by constant reference.
2- returns nothing.
3- it displays the contents of that object in a formatted fashion.
*/
void displayMovie(const Movie& object) {
	cout << endl;
	cout << setw(14) << "Title: " << object.title << endl;
	cout << setw(14) << "Gross Total: " << object.gross_total
		<< " billion dollars" << endl;
	cout << setw(14) << "Director: " << object.director << endl;
	cout << setw(14) << "Release Date: " << object.release_date << endl;
	cout << setw(14) << "Runtime: " << object.runtime << " minutes" << endl;
}

/*
1- the function receives the number of movies in the database by reference.
2- returns a pointer pointing to a array of Movie objects.
3- it creats the movie database.
*/
Movie* createDatabase(int& num_movies) {
	ifstream inFile;
	string filename;

	do {
		cout << "Please enter filename: ";
		getline(cin, filename);
		inFile.open(filename);

		if (!inFile)
			cout << "The filename is invalid, please enter it again.\n";
	} while (!inFile);

	num_movies = numberOfLines(inFile);
	Movie *list = new Movie[num_movies];

	for (int i = 0; i < num_movies; i++) {
		populateMovieFromFile(inFile, list[i]);
	}

	inFile.close();

	return list;
}

/*
1- the function receives two strings.
2- returns true or false.
3- it performs a noncase-sensitive comparison on the two strings.
*/
bool caseInsensitiveCmp(string title, string title_to_search) {

	int x = 0;
	while (title[x] != '\0') {
		title[x] = tolower(title[x]);
		x++;
	}

	int y = 0;
	while (title_to_search[y] != '\0') {
		title_to_search[y] = tolower(title_to_search[y]);
		y++;
	}

	if (title == title_to_search)
		return 1;
	else
		return 0;
}

/*
1- the function receives a pointer to an array of Movie objects 
and number of Movies.
2- returns nothing.
3- it finds if any movie in database matches with the filename entered by user.
*/
void findMovie(Movie* list, int num_movies) {
	string title_to_search, save;
	bool find;
	int sub = 0;

	cout << "\nEnter a movie title to search for: ";
	getline(cin, title_to_search);

	for (; sub < num_movies; sub++) {

		find = list[sub].title.size() == title_to_search.size() ? 1 : 0;

		if (find) {
			find = caseInsensitiveCmp(list[sub].title, title_to_search);
		}

		if (find)
			break;
	}

	if (find) {
		displayMovie(list[sub]);
		do {
			cout << "\nWould you like to save the movie? (Y or N ): ";
			getline(cin, save);
		} while (!(save == "y" || save == "Y" || save == "n" || save == "N"));

		if (save == "y" || save == "Y")
			saveToFile(list[sub]);
	}
	else
		cout << "\nSorry, we didn't find the filename you entered." << endl;

}

/*
1- the function receives a Movie object, passed by constant reference.
2- returns nothing.
3- it saves the Movie object to the “favorites.txt” file.
*/
void saveToFile(const Movie& object) {
	ofstream outFile;
	outFile.open("favorites.txt", ios::app);

	outFile << object.title << ", " << object.gross_total << ", "
		<< object.director << ", " << object.release_date
		<< ", " << object.runtime << endl;

	if (outFile)
		cout << "Successfully saved to the favorites.txt!" << endl;
	else
		cout << "Unsuccessfully saved!" << endl;

	outFile.close();
}

/*
1- the function receives nothing.
2- returns nothing.
3- it will ask user wether wants to continue the program or not.
*/
bool promptToContinue() {
	string cont;

	do {
		cout << "\nWould you like to exit? (Y/N) ";
		cin >> cont;
	} while (!(cont == "y" || cont == "Y" || cont == "n" || cont == "N"));

	cin.ignore();

	if (cont == "Y" || cont == "y")
		return 0;
	else
		return 1;
}

/*
1- the function receives nothing.
2- returns nothing.
3- it will display all saved favorite movies.
*/
void displayFavorites() {
	ifstream input;
	input.open("favorites.txt");

	if (!input)
		cout << "\nThere's no favorite saved." << endl;
	else {
		int num_favorites;

		num_favorites = numberOfLines(input);
		Movie *favorite = new Movie[num_favorites];

		cout << "\nYour saved movies are:" << endl;
		for (int i = 0; i < num_favorites; i++) {
			populateMovieFromFile(input, favorite[i]);
			displayMovie(favorite[i]);
		}
		delete[] favorite;
		favorite = nullptr;
	}

	input.close();
}

/* Sample Run:
Please enter filename: movie.txt

Enter a movie title to search for: AvaTar

	   Title: Avatar
 Gross Total: 2.788 billion dollars
	Director: James Cameron
Release Date: 12/18/09
	 Runtime: 161 minutes

Would you like to save the movie? (Y or N ): y
Successfully saved to the favorites.txt!

Would you like to exit? (Y/N) n

Enter a movie title to search for: FINDING dory

	   Title: Finding Dory
 Gross Total: 1.029 billion dollars
	Director: Andrew Stanton
Release Date: 6/17/16
	 Runtime: 97 minutes

Would you like to save the movie? (Y or N ): Y
Successfully saved to the favorites.txt!

Would you like to exit? (Y/N) N

Enter a movie title to search for: jurassic word

Sorry, we didn't find the filename you entered.

Would you like to exit? (Y/N) y

Your saved movies are:

	   Title: Avatar
 Gross Total: 2.788 billion dollars
	Director: James Cameron
Release Date: 12/18/09
	 Runtime: 161 minutes

	   Title: Finding Dory
 Gross Total: 1.029 billion dollars
	Director: Andrew Stanton
Release Date: 6/17/16
	 Runtime: 97 minutes
*/