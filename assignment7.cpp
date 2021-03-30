/*Date: 6/18/2019
The function is creating a game.
In this game we pick up two of four different types 
of creatures to have a flight.*/

#include <iostream>
#include<string>
#include<ctime>
using namespace std;

class Creature {
private:
	int strength;
	int hitpoints;
public:
	Creature();
	Creature(int newStrength, int newHit);
	void setStrength(int);
	void setHit(int);
	int getStrength();
	int getHit();
	virtual int getDamage();
	virtual string getSpecies();
};

Creature::Creature() {
	strength = 10;
	hitpoints = 10;
}

Creature::Creature(int newStrength, int newHit) {
	strength = newStrength;
	hitpoints = newHit;
}

void Creature::setStrength(int newStrength) {
	strength = newStrength;
}
void Creature::setHit(int newHit) {
	hitpoints = newHit;
}
int Creature::getStrength() {
	return strength;
}
int Creature::getHit() {
	return hitpoints;
}

string Creature::getSpecies() {
	return "Unknown";
}

int Creature::getDamage() {
	int damage;
	damage = (rand() % strength) + 1;
	cout << getSpecies() << " attacks for " <<
		damage << " points!" << endl;
	return damage;
}

class Demon : public Creature {
public:
	Demon() {}
	Demon(int newStrength, int newHit) : Creature(newStrength, newHit) {}
	int getDamage();
};

int Demon::getDamage() {
	int damage = Creature::getDamage();
	if ((rand() % 100) < 5) {
		damage = damage + 50;
		cout << "Demonic attack inflicts 50 "
			<< " additional damage points!" << endl;
	}
	return damage;
}

class Elf : public Creature {
public:
	Elf() {}
	Elf(int newStrength, int newHit) : Creature(newStrength, newHit) {}
	int getDamage();
	string getSpecies();
};
string Elf::getSpecies() {
	return "Elf";
}
int Elf::getDamage() {
	int damage = Creature::getDamage();
	if ((rand() % 10) == 0)
	{
		cout << "Magical attack inflicts " << damage <<
			" additional damage points!" << endl;
		damage = damage * 2;
	}
	return damage;
}

class Human : public Creature {
public:
	Human() {}
	Human(int newStrength, int newHit) : Creature(newStrength, newHit) {}
	string getSpecies();
};
string Human::getSpecies() {
	return "Human";
}

class Cyberdemon : public Demon {
public:
	Cyberdemon() {}
	Cyberdemon(int newStrength, int newHit) : Demon(newStrength, newHit) {}
	string getSpecies();
};
string Cyberdemon::getSpecies() {
	return "Cyberdemon";
}

class Balrog : public Demon {
public:
	Balrog() {}
	Balrog(int newStrength, int newHit) : Demon(newStrength, newHit) {}
	int getDamage();
	string getSpecies();
};
string Balrog::getSpecies() {
	return "Balrog";
}

int Balrog::getDamage() {
	int damage = Demon::getDamage();
	int damage2 = (rand() % getStrength()) + 1;
	cout << "Balrog speed attack inflicts " << damage2 <<
		" additional damage points!" << endl;
	damage = damage + damage2;
	return damage;
}

void battleArena(Creature &creature1, Creature &creature2);

int main() {
	srand(static_cast<int>(time(NULL)));
	Human human1(30, 10);
	human1.getDamage();
	cout << endl;
	Elf elf1;
	elf1.getDamage();
	cout << endl;
	Balrog balrog1(50, 50);;
	balrog1.getDamage();
	cout << endl;
	Cyberdemon cdemon(30, 40);
	cdemon.getDamage();
	cout << endl;
	Elf elf2(50, 50);
	Balrog balrog2(50, 50);
	cout << endl;
	battleArena(elf2, balrog2);
	return 0;
}

void battleArena(Creature &creature1, Creature &creature2) {

	do {
		creature2.setHit(creature2.getHit() - creature1.getDamage());
		cout << "Creature 2 has " << creature2.getHit() << " hit points." << endl;
		creature1.setHit(creature1.getHit() - creature2.getDamage());
		cout << "Creature 1 has " << creature1.getHit() << " hit points." << endl;
	} while (creature1.getHit() > 0 && creature2.getHit());
	cout << endl;

	if (creature1.getHit() > creature2.getHit())
		cout << "Creature 1 wins!" << endl;
	else if (creature1.getHit() < creature2.getHit())
		cout << "Creature 2 wins!" << endl;
	else
		cout << "It's tied." << endl;
}

/*
Sample run:
Human attacks for 26 points!

Elf attacks for 7 points!

Balrog attacks for 21 points!
Balrog speed attack inflicts 34 additional damage points!

Cyberdemon attacks for 24 points!


Elf attacks for 3 points!
Creature 2 has 47 hit points.
Balrog attacks for 49 points!
Balrog speed attack inflicts 15 additional damage points!
Creature 1 has -14 hit points.

Creature 2 wins!

Press any key to close this window . . .
*/
