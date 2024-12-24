#ifndef BOARD_H
#define BOARD_H

#include "Player.h" // Includes the Player class for player-related operations
#include "Tile.h"   // Includes the Tile class for managing board tiles
#include <vector>    // Provides the vector container for dynamic arrays
#include <string>    // Provides the string class for text data
#include <utility>   // Provides the pair class for storing advisor name and description pairs

class Board {
private:
    std::vector<Tile> tiles; // Holds all the tiles on the board
    std::vector<Player> players; // Holds the players participating in the game
    int currentPlayerIndex; // Index of the player whose turn it is
    int moves; // Tracks the total number of moves made in the game
    bool gameOver; // Flag to indicate if the game has ended

    std::vector<std::string> riddles; // Stores riddles for riddle challenges
    std::vector<std::string> riddleAnswers; // Stores answers corresponding to the riddles
    std::vector<std::string> randomEvents; // Stores random events that can occur on tiles
    std::vector<std::pair<std::string, std::string>> advisors; // Stores advisors and their descriptions

public:
    Board(); // Default constructor initializes the board

    void setPlayers(const Player& player1, const Player& player2); // Assigns the players for the game
    void initializeBoard(bool cubTraining); // Initializes the board with tiles and special tiles based on mode
    void loadRiddles(const std::string& filename); // Loads riddles and answers from a file
    void loadRandomEvents(const std::string& filename); // Loads random events from a file
    void loadAdvisors(const std::string& filename); // Loads advisors and their descriptions from a file
    void chooseAdvisor(Player& player); // Allows a player to choose an advisor

    bool isGameOver() const; // Checks if the game is over
    std::string getCurrentPlayerName() const; // Gets the name of the current player

    void viewPlayerStats() const; // Displays the stats of the current player
    void reviewCharacter() const; // Reviews detailed character information of the current player
    void checkPosition() const; // Displays the current tile position of the player
    void reviewAdvisor() const; // Displays the advisor of the current player
    void moveCurrentPlayer(); // Handles the movement of the current player
    void triggerRandomEvent(); // Triggers a random event for the current player
    void solveRiddle(); // Handles a riddle challenge for the current player
    void switchToNextPlayer(); // Switches the turn to the next player
    void endGame(); // Ends the game and calculates the final scores
    void displayBoard() const; // Displays the board with tile and player information

    int getMoves() const; // Returns the total number of moves made in the game
    int displayMainMenu() const; // Displays the main menu and gets the player's choice
};

#endif
