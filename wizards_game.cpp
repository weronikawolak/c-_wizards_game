#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <cctype>
#include <fstream>
#include <random>
#include <Windows.h>
#include "fun.h"


using namespace std;


int main(int argc, char* argv[])
{
	string playerName;
	bool isNameValid = true;

	if (argc > 1) {
		playerName = argv[1];
		for (char const& c : playerName) {
			if (!isalpha(c)) {
				isNameValid = false;
				break;
			}
		}

		if (isNameValid) {
			cout << "Hello " << playerName << ", welcome to the magical Duel Game!" << endl;
		}
		else {
			cout << "Invalid name. Please use only letters." << endl << endl << "Hello stranger! Welcome to the magical Duel Game!" << endl;
		}
	}
	else {
		cout << "Hello stranger! Welcome to the magical Duel Game!" << endl;
	}

	saveSpellsToBinaryFile();

	int choice1, choice2;
	Spell illusion("illusion", 40, 10);
	Spell curse("curse", 60, 60);
	Spell fireball("fireball", 40, 20);

	Spell blinding("blinding", 40, 10);
	Spell paralysis("paralysis", 60, 60);
	Spell hurricane("hurricane", 40, 20);

	Spell hallucinations("hallucinations", 40, 10);
	Spell explosion("explosion", 60, 60);
	Spell watervortex("water vortex", 40, 20);


	Wizards* Cynthia = new Wizards("Cynthia", "Invisibility", 70, 100);
	Cynthia->addSpell(illusion);
	Cynthia->addSpell(curse);
	Cynthia->addSpell(fireball);

	Wizards* Jack = new Wizards("Jack", "reading in minds", 80, 100);
	Jack->addSpell(blinding);
	Jack->addSpell(paralysis);
	Jack->addSpell(hurricane);

	Wizards* Eva = new Wizards("Eva", "speed", 50, 100);
	Eva->addSpell(explosion);
	Eva->addSpell(hallucinations);
	Eva->addSpell(watervortex);

	MagicalCreature* mc1 = Cynthia;
	MagicalCreature* mc2 = Jack;
	MagicalCreature* mc3 = Eva;




	int ctr = 1;

	unordered_map<int, MagicalCreature*> charactersMap;
	charactersMap[ctr++] = mc1;
	charactersMap[ctr++] = mc2;
	charactersMap[ctr++] = mc3;




	int menuChoice;
	string input;
	bool exitGame = false;
	MagicalCreature* myCharacter = nullptr;
	bool characterCreated = false;

	cout << "---------------------------------" << std::endl;



	while (!exitGame) {

		do {
			cout << endl << endl << "1- Display Information about the characters" << std::endl;
			cout << "2- Create a Duel" << endl;
			cout << "3- Attend Magic school" << endl;
			cout << "4- Train your character" << endl;
			if (!characterCreated) {
				cout << "5- Create a new character" << endl;
				cout << "6- Exit the game" << endl;
			}
			else
				cout << "5- Exit the game" << endl;

			cout << "---------------------------------" << endl;
			cout << "Enter your choice: ";
			getline(cin, input);

			if (input.length() == 1 && isdigit(input[0])) {
				menuChoice = input[0] - '0';
			}
			else {
				cout << endl << "Invalid input. Please try again" << endl;
				continue;
			}

			switch (menuChoice) {
			case 1:
				Cynthia->displayInfo();
				Cynthia->displaySpells();
				cout << endl << endl << "---------------------------------" << endl << endl;
				Jack->displayInfo();
				Jack->displaySpells();
				cout << endl << endl << "---------------------------------" << endl << endl;
				Eva->displayInfo();
				Eva->displaySpells();
				cout << endl << endl << "---------------------------------" << endl << endl;

				if (characterCreated) {
					myCharacter->displayInfo();
					myCharacter->displaySpells();
					cout << endl << endl << "---------------------------------" << endl << endl;

				}
				break;

			case 2: {
				cout << "Time for battle! " << endl;
				cout << "Choose two wizards to duel:" << endl;
				cout << "1- Cynthia" << endl;
				cout << "2- Jack" << endl;
				cout << "3- Eva" << endl;

				if (characterCreated) {
					cout << "4- " << myCharacter->getName() << endl;
				}

				bool validChoice2 = false;
				do {
					cout << "Choose the first wizard: ";
					getline(cin, input);
					if (input.length() == 1 && isdigit(input[0]) && charactersMap.find(input[0] - '0') != charactersMap.end()) {
						choice1 = input[0] - '0';
					}
					else {
						cout << endl << "Invalid choice. Please enter a valid number." << endl;
						continue;
					}
					cout << "Choose the second wizard: ";
					getline(cin, input);
					if (input.length() == 1 && isdigit(input[0]) && input[0] - '0' != choice1 && charactersMap.find(input[0] - '0') != charactersMap.end()) {
						choice2 = input[0] - '0';
						validChoice2 = true;
					}
					else {
						cout << endl << "Invalid choice or same wizard chosen. Please enter a different valid number." << endl;
						continue;
					}
				} while (!validChoice2);

				while (choice1 == choice2 || charactersMap.find(choice1) == charactersMap.end() || charactersMap.find(choice2) == charactersMap.end()) {
					cout << endl << "Invalid choices or same wizard chosen. Please choose again." << std::endl;
					cout << "Choose the first character: ";
					cin >> choice1;
					cout << "Choose the second character: ";
					cin >> choice2;
				}

				MagicalCreature* character1 = charactersMap[choice1];
				MagicalCreature* character2 = charactersMap[choice2];

				duel(character1, character2);

				system("pause");
				break;
			}

			case 3:
			{
				int choice3;
				string input3;
				bool validChoice3 = false;
				do {
					cout << "Choose a character: " << endl;
					for (int i = 1; i < ctr; i++) {
						if (charactersMap.find(i) != charactersMap.end()) {
							cout << i << "- " << charactersMap[i]->getName() << endl;
						}
					}

					cout << "Enter your choice: ";
					getline(cin, input3);

					if (input3.length() == 1 && isdigit(input3[0]) && charactersMap.find(input3[0] - '0') != charactersMap.end()) {
						choice3 = input3[0] - '0';
						validChoice3 = true;
					}
					else {
						cout << endl << "Invalid choice. Try again." << endl;
					}

				} while (!validChoice3);

				auto x = charactersMap.find(choice3);
				if (x != charactersMap.end()) {
					MagicalCreature* student = x->second;

					if (student) {
						attendMagicSchool(student);
					}
					else {
						cout << endl << "No character found for this choice." << endl;
					}
				}
				else {
					cout << endl << "Invalid choice. Try again" << endl;
				}
				break;

			}
			case 4:
			{
				string input4;
				int choice4;
				bool validChoice4 = false;

				do {
					cout << "Choose a character: " << endl;
					for (int i = 1; i < ctr; i++) {
						cout << i << "- " << charactersMap[i]->getName() << endl;
					}

					cout << endl << "Enter your choice: ";
					getline(cin, input4);

					if (input4.length() == 1 && isdigit(input4[0]) && charactersMap.find(input4[0] - '0') != charactersMap.end()) {
						choice4 = input4[0] - '0';
						validChoice4 = true;
					}
					else {
						cout << endl << "Invalid choice. Try again." << endl;
					}

				} while (!validChoice4);


				auto it = charactersMap.find(choice4);
				if (it != charactersMap.end()) {
					MagicalCreature* character_to_train = it->second;
					if (character_to_train) {
						character_to_train->training();
						character_to_train->training(5);
					}
					else {
						cout << endl << "No character found for this choice." << endl;
					}
				}
				else {
					cout << endl << "Invalid choice. Try again" << endl;
				}
				break;
			}

			case 5:
			{
				if (characterCreated == false)
				{
					int choice5;
					string input5;
					bool validChoice5 = false;


					do {
						cout << "Choose the type of creature to create:\n";
						cout << "1. Wizard\n2. Elf\n3. Witch\n";
						cout << "Enter your choice: ";
						getline(cin, input5);

						if (input5.length() == 1 && isdigit(input5[0])) {
							choice5 = input5[0] - '0';
							if (choice5 >= 1 && choice5 <= 3) {
								validChoice5 = true;
							}
						}
						else {
							cout << endl << "Invalid choice. Try again." << endl;
						}

					} while (!validChoice5);



					string name;
					string skill;
					int strength;

					auto containsOnlyDigits = [](const string& s) {
						for (char c : s) {
							if (!isdigit(c)) return false;
						}
						return true;
					};
					auto containsOnlyLetters = [](const string& s) {
						for (char c : s) {
							if (!isalpha(c)) return false;
						}
						return true;
					};


					do {
						cout << "Enter the name: ";
						getline(cin, name);
						if (!containsOnlyLetters(name)) {
							cout << endl << "Invalid name. Try again." << endl;
						}
					} while (!containsOnlyLetters(name));


					do {
						cout << "Enter the special skill: ";
						getline(cin, skill);
						if (!containsOnlyLetters(skill)) {
							cout << "Invalid skill. Try again." << endl;
						}
					} while (!containsOnlyLetters(skill));

					bool validStrength = false;

					while (!validStrength) {
						cout << "Enter the strength points: ";

						getline(cin, input);

						if (containsOnlyDigits(input)) {
							validStrength = true;
							strength = stoi(input);
						}
						else {
							cout << endl << "Invalid strength. Try again." << endl;
						}
					}
					if (choice5 == 1) {
						myCharacter = new Wizards(name, skill, strength, 100);
						charactersMap[ctr++] = myCharacter;

					}
					else if (choice5 == 2) {
						myCharacter = new Elf(name, skill, strength, 100);
						charactersMap[ctr++] = myCharacter;

					}
					else if (choice5 == 3) {

						myCharacter = new Nymph(name, skill, strength, 100);
						charactersMap[ctr++] = myCharacter;

					}
					else {
						cout << endl << "Invalid choice. Try again" << endl;
						break;
					}



					for (int i = 0; i < 3; i++)
					{
						string spellName;
						Spell newSpell;

						do {
							cout << "Add spells!: ";
							getline(cin, spellName);
							if (!containsOnlyLetters(spellName)) {
								cout << endl << "Invalid Spell. Try again." << endl;
							}
						} while (!containsOnlyLetters(spellName));

						if (i == 0)
							newSpell = Spell(spellName, 40, 10);
						else if (i == 1)
							newSpell = Spell(spellName, 60, 60);
						else
							newSpell = Spell(spellName, 40, 20);
						myCharacter->addSpell(newSpell);
					}

					characterCreated = true;
					break;
				}

				else
				{
					exitGame = true;
					cout << endl << "Exiting Game. Thank you for playing!" << std::endl;
					break;

				}
			}
			case 6:
				if (characterCreated == false)
				{
					exitGame = true;
					cout << endl << "Exiting Game. Thank you for playing!" << std::endl;
					break;
				}
			default:
				cout << endl << "Invalid input. Please try again" << endl;
				break;
			}
		} while (!exitGame);

		for (auto& mm : charactersMap) {
			delete mm.second;
		}
		charactersMap.clear();
		return 0;
	}
}
