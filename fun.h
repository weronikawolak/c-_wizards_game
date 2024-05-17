/**
* @file fun.h
* @brief This file contains the declarations of classes related to a fantasy game, including characters, spells, magical creatures, and utilities for managing them.
**/


#pragma once

using namespace std;

/**
 * @class character
 * @brief  Base class representing a character in the game.
 *
 * This class provides basic methods and common attributes for all types of characters.
 */
class character {
protected:
    string name;           ///< Name of the character.
    string skill;          ///< Skill of the character.
    int strength;          ///< Strength of the character.
    int manaPoints;        ///< Mana points of the character.


public:
    /**
      * Default constructor.
      */
    character();

    /**
         * Constructor with parameters for initializing a character.
         * @param name Name of the character.
         * @param skill Skill of the character.
         * @param strength Strength of the character.
         * @param manaPoints Mana points of the character.
         */
    character(string, string, int, int);
    /**
       * Virtual destructor.
     */
    virtual ~character() {};

    /**
     * @brief Returns the name of the character.
     * @return The name of the character as a constant string reference.
     */
    const string& getName() const;

    /**
 * @brief Sets the name of the character.
 * @param n A string representing the new name of the character.
 */
    void setName(const string& n);
    /**
 * @brief Returns the skill of the character.
 * @return The skill of the character as a constant string reference.
 */
    const string& getSkill() const;
    /**
 * @brief Sets the skill of the character.
 * @param sk A string representing the new skill of the character.
 */
    void setSkill(const string& sk);

    /**
 * @brief Returns the strength of the character.
 * @return The strength of the character as an integer.
 */
    int getStrength() const;

    /**
 * @brief Sets the strength of the character.
 * @param str An integer representing the new strength of the character.
 */
    void setStrength(int str);

    /**
 * @brief Returns the mana points of the character.
 * @return The mana points of the character as an integer.
 */
    int getManaPoints() const;

    /**
 * @brief Sets the mana points of the character.
 * @param i An integer representing the new mana points of the character.
 */
    void setManaPoints(int i);
    /**
       * Displays information about the character.
       */
    void displayInfo() const;
    /**
     * Pure virtual function for training the character.
     */
    virtual void training() = 0;
    /**
     * Pure virtual function for training the character with additional strength.
     * @param additionalStrength Additional strength to be added to the character during training.
     */
    virtual void training(int additionalStrength) = 0;


};
/**
 * @class Spell
 * @brief Class representing a spell in the game.
 *
 * The Spell class contains information about the name, power, and mana cost of the spell.
 */

class Spell {
    string name;       ///< Name of the spell.
    int power;         ///< Power of the spell.
    int manaCost;      ///< Mana cost required to cast the spell.
public:
    /**
         * Default constructor.
         */
    Spell();
    /**
         * Constructor initializing the spell with given parameters.
         * @param n Name of the spell.
         * @param pwr Power of the spell.
         * @param manaC Mana cost of the spell.
         */
    Spell(string n, int pwr, int manaC);

    /**
        * Returns the name of the spell.
        * @return Name of the spell as a constant string reference.
        */
    const string& getName() const;

    /**
         * Sets the name of the spell.
         * @param n New name of the spell.
         */
    void setName(string n);

    /**
 * Returns the power of the spell.
 * @return Power of the spell as an int value.
 */
    int getPower() const;

    /**
    * Sets the power of the spell.
    * @param pwr New power of the spell.
    */
    void setPower(int pwr);

    /**
     * Returns the mana cost of the spell.
     * @return Mana cost of the spell as an int value.
     */
    int getManaCost() const;

    /**
      * Sets the mana cost of the spell.
      * @param manaC New mana cost of the spell.
      */
    void setManaCost(int manaC);

    /**
       * Overloaded operator<< for outputting information about the spell.
       * @param os Output stream to which the data will be written.
       * @param spell Spell class object whose data is to be written.
       * @return Reference to the output stream.
       */
    friend ostream& operator<<(ostream& os, const Spell& spell);

};

/**
 * @class MagicalCreature
 * @brief A class representing a magical creature, derived from the character class.
 *
 * This class extends the character class by adding the ability to handle spells.
 */
class MagicalCreature : public character {

    vector<Spell> spells; ///< Vector storing spells possessed by the magical creature.

public:
    /**
   * Constructor initializing a magical creature with given parameters.
   * @param name Name of the magical creature.
   * @param skill Skill of the magical creature.
   * @param strength Strength of the magical creature.
   * @param manaPoints Mana points of the magical creature.
   */
    MagicalCreature(string, string, int, int);

    /**
     * Destructor.
     */
    ~MagicalCreature() {};

    /**
     * Reduces the mana points of the magical creature.
     * @param cost The amount by which to reduce the mana points.
     */
    void reduceMana(int cost);

    /**
     * Adds a new spell to the magical creature's spell list.
     * @param spell A Spell object to be added to the spells vector.
     */
    void addSpell(const Spell& spell);

    /**
     * Displays all spells possessed by the magical creature.
     */
    void displaySpells();

    /**
     * Casts a spell in a duel against another magical creature.
     * @param opponent Pointer to the magical creature that is the opponent in the duel.
     */
    void castSpellInDuel(MagicalCreature* opponent);

    /**
     * Friend template function that allows a magical creature to attend magic school.
     * This function enables magical creatures to learn new spells.
     * @param character Pointer to the character attending the magic school.
     */
    template<typename T>
    friend void attendMagicSchool(T* character);

};


/**
 * @class Wizards
 * @brief A class representing wizards, derived from the MagicalCreature class.
 *
 * This class provides specific functionalities and attributes for wizards,
 * including their unique tools and specialized training methods.
 */
class Wizards : public MagicalCreature
{
    static const string tool; ///< Static constant representing the tool specific to Wizards.
public:
    /**
  * Constructor initializing a wizard with given parameters.
  * @param name Name of the wizard.
  * @param skill Skill of the wizard.
  * @param strength Strength of the wizard.
  * @param manaPoints Mana points of the wizard.
  */
    Wizards(string, string, int, int);
    /**
     * Destructor.
     */
    ~Wizards() {};

    /**
   * Displays information about the wizard.
   */
    void displayInfo() const;

    /**
    * Returns the tool specific to wizards.
    * @return The tool of the wizard as a constant string reference.
    */
    const string& getTool() const;

    /**
     * Performs training for the wizard. Specific implementation for wizards.
     */
    void training();

    /**
    * Performs training for the wizard with additional strength.
    * @param additionalStrength Additional strength to be added to the wizard during training.
    */
    void training(int additionalStrength);

};

/**
 * @class Elf
 * @brief A class representing an Elf, derived from the MagicalCreature class.
 *
 * This class provides specific functionalities and attributes for Elves,
 * including their unique tools and specialized training methods.
 */
class Elf : public MagicalCreature
{
    static const string tool; ///< Static constant representing the tool specific to Elves.
public:
    /**
 * Constructor initializing an Elf with given parameters.
 * @param name Name of the Elf.
 * @param skill Skill of the Elf.
 * @param strength Strength of the Elf.
 * @param manaPoints Mana points of the Elf.
 */
    Elf(string, string, int, int);

    /**
 * Destructor.
 */
    ~Elf() {};

    /**
     * Displays information about the Elf.
     */
    void displayInfo() const;

    /**
     * Returns the tool specific to Elves.
     * @return The tool of the Elf as a constant string reference.
     */
    const string& getTool() const;

    /**
     * Performs training for the Elf. Specific implementation for Elves.
     */
    void training();

    /**
     * Performs training for the Elf with additional strength.
     * @param additionalStrength Additional strength to be added to the Elf during training.
     */
    void training(int additionalStrength);

};

/**
 * @class Nymph
 * @brief A class representing a Nymph, derived from the MagicalCreature class.
 *
 * This class provides specific functionalities and attributes for Nymphs,
 * including their unique tools and specialized training methods.
 */
class Nymph : public MagicalCreature
{
    static const string tool; ///< Static constant representing the tool specific to Nymphs.

public:

    /**
 * Constructor initializing a Nymph with given parameters.
 * @param name Name of the Nymph.
 * @param skill Skill of the Nymph.
 * @param strength Strength of the Nymph.
 * @param manaPoints Mana points of the Nymph.
 */

    Nymph(string, string, int, int);

    /**
    * Destructor.
    */
    ~Nymph() {};

    /**
    * Displays information about the Nymph.
    */
    void displayInfo() const;

    /**
  * Returns the tool specific to Nymphs.
  * @return The tool of the Nymph as a constant string reference.
  */
    const string& getTool() const;

    /**
    * Performs training for the Nymph. Specific implementation for Nymphs.
    */
    void training();

    /**
  * Performs training for the Nymph with additional strength.
  * @param additionalStrength Additional strength to be added to the Nymph during training.
  */
    void training(int additionalStrength);


};

/**
 * @brief Conducts a duel between two magical creatures.
 *
 * This function simulates a duel between two instances of MagicalCreature.
 * It involves the interaction of their spells and attributes in the duel.
 * @param mag1 Pointer to the first MagicalCreature participating in the duel.
 * @param mag2 Pointer to the second MagicalCreature participating in the duel.
 */
void duel(MagicalCreature * mag1, MagicalCreature * mag2);

/**
 * @brief Saves the current spells to a binary file.
 *
 * This function serializes the spells into a binary format and saves them to a file.
 * This is useful for persisting the current state of spells for later retrieval.
 */
void saveSpellsToBinaryFile();

/**
 * @brief Loads spells from a binary file.
 *
 * This function reads a binary file containing spell data and deserializes it into
 * a vector of strings, each representing a spell. It's used to retrieve the state of spells
 * saved by the saveSpellsToBinaryFile function.
 * @return A vector of strings, where each string represents a spell's name.
 */
vector<string> loadSpellsFromBinaryFile();

/**
 * @brief Template function for allowing a character to attend a magic school.
 *
 * This function simulates the character's attendance at a magic school where they can learn new spells.
 * It checks the existing spells of the character and adds new ones from a predefined list.
 * @tparam T The type of character attending the magic school. Must be a subclass of MagicalCreature.
 * @param character Pointer to the character attending the magic school.
 */
template<typename T>
void attendMagicSchool(T * character) {
    cout << endl << character->getName() << " enters the magic school." << endl;
    cout << "Attending a lesson on elemental magic..." << endl;
    Sleep(2000);

    const int spellPower = 40;
    const int spellCost = 15;

    vector<string> spellNames = loadSpellsFromBinaryFile();

    vector<string> newSpells;

    for (const string& spellName : spellNames) {
        bool alreadyHasSpell = false;
        for (const Spell& existingSpell : character->spells) {
            if (existingSpell.getName() == spellName) {
                alreadyHasSpell = true;
                break;
            }
        }
        if (!alreadyHasSpell) {
            newSpells.push_back(spellName);
        }
    }

    if (newSpells.empty()) {
        cout << character->getName() << " already knows all available spells." << endl;
    }
    else {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> distrib(0, newSpells.size() - 1);
        string spellName = newSpells[distrib(gen)];

        Spell newSpell = Spell(spellName, spellPower, spellCost);
        character->addSpell(newSpell);

        cout << character->getName() << " has learned a new spell: " << endl;
        cout << newSpell;
    }
}

/**
 * @class MyException
 * @brief Custom exception class for the game.
 *
 * This class provides a mechanism for throwing and catching custom exceptions.
 * It inherits from the standard exception class in C++.
 */
class MyException : public exception {
private:
    string msg; ///< Message describing the exception.


public:

    /**
    * Constructor with a message parameter.
    * @param message Description of the exception.
    */
    MyException(const string& message) : msg(message) {}

    /**
         * Provides the exception message.
         * @return The exception message as a C-style string.
         */
    const char* what() const noexcept override {
        return msg.c_str();
    }
};
