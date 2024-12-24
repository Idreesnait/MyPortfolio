#ifndef PLAYER_H
#define PLAYER_H

#include <string> // Includes the standard string library for handling text data

// The Player class represents a player in the game, with attributes and methods to manage their state
class Player {
private:
    std::string name;       // Player's name
    int age;                // Player's age
    int strength;           // Player's strength attribute
    int stamina;            // Player's stamina attribute
    int wisdom;             // Player's wisdom attribute
    int pridePoints;        // Player's pride points, representing their score
    int position;           // Player's position on the board
    std::string advisor;    // Player's selected advisor
    std::string path;       // Player's chosen path in the game (e.g., "Cub Training")

public:
    // Default constructor initializing player with default values
    Player();

    // Parameterized constructor initializing player with specific values
    Player(const std::string& name, int age, int strength, int stamina, int wisdom, int pridePoints);

    // Accessor methods to get private attributes
    std::string getName() const;      // Returns the player's name
    int getAge() const;               // Returns the player's age
    int getStrength() const;          // Returns the player's strength
    int getStamina() const;           // Returns the player's stamina
    int getWisdom() const;            // Returns the player's wisdom
    int getPridePoints() const;       // Returns the player's pride points
    int getPosition() const;          // Returns the player's position on the board
    std::string getAdvisor() const;   // Returns the player's advisor
    std::string getPath() const;      // Returns the player's chosen path

    // Mutator methods to set private attributes
    void setName(const std::string& name);        // Sets the player's name
    void setAge(int age);                         // Sets the player's age
    void setStrength(int strength);              // Sets the player's strength, ensuring it is not below 100
    void setStamina(int stamina);                // Sets the player's stamina, ensuring it is not below 100
    void setWisdom(int wisdom);                  // Sets the player's wisdom, ensuring it is not below 100
    void setPridePoints(int pridePoints);        // Sets the player's pride points
    void setPosition(int pos);                   // Sets the player's position on the board
    void setAdvisor(const std::string& advisor); // Sets the player's advisor
    void setPath(const std::string& path);       // Sets the player's chosen path

    // Methods to adjust player attributes dynamically
    void adjustStats(int pridePoints, int strength, int stamina, int wisdom); // Adjusts the player's stats by specified values
    void adjustWisdom(int wisdomPoints);                                      // Adjusts the player's wisdom by a specific value

    // Method to print all player's stats
    void printStats() const; // Displays the player's attributes and status
};

#endif // End of the PLAYER_H header guard