#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <fstream>
#include <exception>
#include <Windows.h>
#include "fun.h"

using namespace std;

character::character() : strength(0), manaPoints(0) {};

character::character(string n, string sk, int str, int mp) : name(n), skill(sk), strength(str), manaPoints(mp) {}

const string& character::getName() const {
    return name;
}

void character::setName(const string& n) {
    name = n;
}

const string& character::getSkill() const {
    return skill;
}

void character::setSkill(const string& sk) {
    skill = sk;
}

int character::getStrength() const {
    return strength;
}

void character::setStrength(int str) {
    strength = str;
}


int character::getManaPoints() const {
    return manaPoints;
}

void character::setManaPoints(int i) {
    manaPoints = i;
}


void character::displayInfo() const {
    cout << "Name: " << getName() << endl;
    cout << "Skill: " << getSkill() << endl;
    cout << "Strength: " << getStrength() << endl;
    cout << "Mana: " << getManaPoints() << endl;
}


Spell::Spell() : name("blank"), power(0), manaCost(0) {}

Spell::Spell(string n, int pwr, int manaC)
    : name(n), power(pwr), manaCost(manaC) {}


const string& Spell::getName() const {
    return name;
}
void Spell::setName(string n) {
    name = n;
}

int Spell::getPower() const {
    return power;
}

void Spell::setPower(int pwr) {
    power = pwr;
}


int Spell::getManaCost() const {
    return manaCost;
}

void Spell::setManaCost(int manaC) {
    manaCost = manaC;
}

ostream& operator<<(ostream& os, const Spell& spell) {
    os << "Spell Name: " << spell.getName() << ", Power: " << spell.getPower() << ", Mana Cost: " << spell.getManaCost();
    return os;
}

MagicalCreature::MagicalCreature(string n, string sk, int str, int mp) : character(n, sk, str, mp)
{}

void MagicalCreature::reduceMana(int cost) {
    manaPoints -= cost;
    if (manaPoints < 0) manaPoints = 0;
}

void MagicalCreature::addSpell(const Spell& spell) {
    spells.push_back(spell);
}

void MagicalCreature::displaySpells() {
    std::cout << endl << "Spells list" << std::endl;
    for (Spell spell : spells) {
        cout << "* " << spell.getName() << " Power: " << spell.getPower() << ", Mana Cost: " << spell.getManaCost() << endl;
    }
}

void MagicalCreature::castSpellInDuel(MagicalCreature* opponent) {

    if (spells.empty()) {
        cout << getName() << " has no spells to cast." << endl;
        return;
    }

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(0, static_cast<int>(spells.size() - 1));

    int index = dis(gen);

    if (index >= 0 && index < spells.size()) {
        const Spell& spell = spells[index];

        if (getManaPoints() >= spell.getManaCost()) {
            reduceMana(spell.getManaCost());
            cout << getName() << " casts " << spell.getName() << " on " << opponent->getName() << endl;

            opponent->reduceMana(spell.getPower());
            cout << opponent->getName() << " loses " << spell.getPower() << " mana points due to the spell." << endl;
        }

    }
    else {
        cout << getName() << " tried to cast an unknown spell." << endl;
    }
}


const string Wizards::tool = "Wand";


Wizards::Wizards(string n, string sk, int str, int mp) : MagicalCreature(n, sk, str, mp)
{}

void Wizards::displayInfo() const
{
    cout << "Race: Wizard" << endl;
    character::displayInfo();
    cout << "Tool: " << getTool() << endl;

}
const string& Wizards::getTool() const {
    return tool;
}


void Wizards::training()
{
    manaPoints += 30;
    cout << endl << getName() << " is practising " << skill << endl << "... Increasing ManaPoints. " << endl << "Current ManaPoints : " << getManaPoints() << endl;
}

void Wizards::training(int additionalStrength)
{
    strength += additionalStrength;
    cout << "Wizard also got additional strength" << endl;
}


const string Elf::tool = "Moon water";



Elf::Elf(string n, string sk, int str, int mp) : MagicalCreature(n, sk, str, mp)
{}

void Elf::displayInfo() const
{
    cout << "Race: Elf" << endl;
    character::displayInfo();
    cout << "Tool: " << getTool() << endl;

}
const string& Elf::getTool() const {
    return tool;
}

void Elf::training()
{
    manaPoints += 25;
    cout << endl << getName() << " is practising " << skill << endl << "... Increasing ManaPoints. " << endl << "Current ManaPoints : " << getManaPoints() << endl;

}

void Elf::training(int additionalStrength)
{
    strength += additionalStrength;
    cout << "Elf also got additional strength" << endl;
}

const string Nymph::tool = "Magic Dust";


Nymph::Nymph(string n, string sk, int str, int mp) : MagicalCreature(n, sk, str, mp)
{}

void Nymph::displayInfo() const
{
    cout << "Race: Nymph" << endl;
    character::displayInfo();
    cout << "Tool: " << getTool() << endl;

}

const string& Nymph::getTool() const {
    return tool;
}
void Nymph::training()
{
    manaPoints += 22;
    cout << endl << getName() << " is practising " << skill << endl << "... Increasing ManaPoints. " << endl << "Current ManaPoints : " << getManaPoints() << endl;

}

void Nymph::training(int additionalStrength)
{
    strength += additionalStrength;
    cout << "Nymph also got additional strength" << endl;
}

void duel(MagicalCreature* mag1, MagicalCreature* mag2) {
    if (mag1->getStrength() > mag2->getStrength()) {
        cout << endl << "Duel starts between " << mag1->getName() << " and " << mag2->getName() << "!" << endl;
        while (mag1->getManaPoints() > 0 && mag2->getManaPoints() > 0) {
            Sleep(2000);
            mag1->castSpellInDuel(mag2);

            if (mag2->getManaPoints() <= 0) {
                break;
            }

            Sleep(2000);
            mag2->castSpellInDuel(mag1);

            if (mag1->getManaPoints() <= 0) {
                break;
            }
        }
    }
    else {
        cout << endl << "Duel starts between " << mag2->getName() << " and " << mag1->getName() << "!" << endl;
        while (mag1->getManaPoints() > 0 && mag2->getManaPoints() > 0) {
            Sleep(2000);
            mag2->castSpellInDuel(mag1);

            if (mag1->getManaPoints() <= 0) {
                break;
            }

            Sleep(2000);
            mag1->castSpellInDuel(mag2);

            if (mag2->getManaPoints() <= 0) {
                break;
            }
        }
    }



    if (mag1->getManaPoints() > mag2->getManaPoints())
        cout << endl << endl << mag1->getName() << " won the battle." << endl;
    else
        cout << endl << endl << mag2->getName() << " won the battle." << endl;

}


void saveSpellsToBinaryFile() {
    vector<string> spellNames = {
        "Lightning bolt",
        "Ice Blast",
        "Earthquake",
        "Wind Gust",
        "Lightning Strike"
    };

    try {
        ofstream outputFile("spellsbase.bin", ios::binary);

        if (!outputFile) {
            throw ios_base::failure("Cannot open file for writing");
        }

        for (const auto& spellName : spellNames) {
            size_t length = spellName.size();
            outputFile.write(reinterpret_cast<const char*>(&length), sizeof(length));
            outputFile.write(spellName.c_str(), length);
        }

        outputFile.close();
    }
    catch (const ios_base::failure& e) {
        cerr << "Error: " << e.what() << endl;
    }
}


vector<string> loadSpellsFromBinaryFile() {
    vector<string> spellNames;
    try {
        ifstream inputFile("spellsbase.bin", ios::binary);

        if (!inputFile) {
            throw MyException("Cannot open file for reading");
        }

        while (!inputFile.eof()) {
            size_t length;
            inputFile.read(reinterpret_cast<char*>(&length), sizeof(length));

            if (inputFile) {
                string spellName(length, '\0');
                inputFile.read(&spellName[0], length);

                if (!spellName.empty()) {
                    spellNames.push_back(spellName);
                }
            }
        }

        inputFile.close();
    }
    catch (const MyException& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return spellNames;
}

