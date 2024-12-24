#include "Board.h" // Includes the Board class definition
#include "Tile.h"  // Includes the Tile class definition
#include "Player.h" // Includes the Player class definition
#include <iostream>   // Enables input and output operations
#include <fstream>    // Provides file input/output operations
#include <cstdlib>    // Provides random number generation functions
#include <ctime>      // Provides time-related functions (used for seeding random numbers)
#include <vector>     // Provides the vector container for dynamic arrays
#include <iomanip>    // Provides input/output manipulators like formatting numbers

// Board constructor to initialize default values and seed the random number generator
Board::Board() : currentPlayerIndex(0), moves(0), gameOver(false) {
    srand(static_cast<unsigned int>(time(0))); // Seeds the random number generator with the current time
}

// Sets the two players for the game by adding them to the players vector
void Board::setPlayers(const Player& player1, const Player& player2) {
    players.push_back(player1); // Add player1 to the players vector
    players.push_back(player2); // Add player2 to the players vector
}

// Initializes the game board with tiles, including special tiles based on game mode
void Board::initializeBoard(bool cubTraining) {
    tiles.resize(104, Tile("Regular")); // Sets the board to have 104 tiles, all initially "Regular"
    tiles[0] = Tile("Start"); // The first tile is the "Start" tile
    tiles[tiles.size() - 1] = Tile("Pride Rock"); // The last tile is the "Pride Rock" tile

    int specialTileCount = 20; // Number of special tiles to add
    for (int i = 0; i < specialTileCount; ++i) {
        int index = rand() % (tiles.size() - 2) + 1; // Randomly selects a tile index between 1 and second-to-last tile
        if (cubTraining) { // If in Cub Training mode, use these special tiles
            if (i % 4 == 0) {
                tiles[index] = Tile("Oasis");
            } else if (i % 4 == 1) {
                tiles[index] = Tile("Counseling");
            } else if (i % 4 == 2) {
                tiles[index] = Tile("Graveyard");
            } else {
                tiles[index] = Tile("Hyenas");
            }
        } else { // Otherwise, use these special tiles for regular mode
            if (i % 3 == 0) {
                tiles[index] = Tile("Challenge");
            } else if (i % 3 == 1) {
                tiles[index] = Tile("Graveyard");
            } else {
                tiles[index] = Tile("Hyenas");
            }
        }
    }
}

// Loads riddles and their answers from a file
void Board::loadRiddles(const std::string& filename) {
    std::ifstream file(filename); // Opens the file for reading
    if (!file) { // Checks if the file failed to open
        std::cerr << "Error: Unable to open " << filename << "\n"; // Prints error message
        exit(1); // Exits the program
    }

    std::string line; // Temporary string to hold each line of the file
    while (std::getline(file, line)) { // Reads the file line by line
        size_t delimiter = line.find('|'); // Finds the position of the delimiter '|'
        riddles.push_back(line.substr(0, delimiter)); // Adds the riddle to the riddles vector
        riddleAnswers.push_back(line.substr(delimiter + 1)); // Adds the answer to the riddleAnswers vector
    }
}

// Loads random events from a file
void Board::loadRandomEvents(const std::string& filename) {
    std::ifstream file(filename); // Opens the file for reading
    if (!file) { // Checks if the file failed to open
        std::cerr << "Error: Unable to open " << filename << "\n"; // Prints error message
        exit(1); // Exits the program
    }

    std::string line; // Temporary string to hold each line of the file
    while (std::getline(file, line)) { // Reads the file line by line
        randomEvents.push_back(line); // Adds the line to the randomEvents vector
    }
}

// Allows a player to choose an advisor from the list of available advisors
void Board::chooseAdvisor(Player& player) {
    if (advisors.empty()) { // If no advisors are available
        std::cout << "No advisors available to choose from.\n";
        return;
    }

    std::cout << "Choose your advisor:\n";
    for (size_t i = 0; i < advisors.size(); ++i) { // Displays all advisors
        std::cout << i + 1 << ". " << advisors[i].first << " - " << advisors[i].second << "\n";
    }

    int choice;
    std::cin >> choice; // Takes user input for the advisor choice

    if (choice >= 1 && choice <= static_cast<int>(advisors.size())) { // Validates the choice
        player.setAdvisor(advisors[choice - 1].first); // Assigns the chosen advisor to the player
        std::cout << "Advisor " << advisors[choice - 1].first << " selected!\n";
    } else {
        std::cout << "Invalid choice. No advisor selected.\n";
    }
}

// Loads advisors and their abilities/descriptions from a file
void Board::loadAdvisors(const std::string& filename) {
    std::ifstream file(filename); // Opens the file for reading
    if (!file) { // Checks if the file failed to open
        std::cerr << "Error: Unable to open " << filename << "\n"; // Prints error message
        exit(1); // Exits the program
    }

    std::string line; // Temporary string to hold each line of the file
    while (std::getline(file, line)) { // Reads the file line by line
        size_t delimiter1 = line.find('|'); // Finds the first delimiter
        size_t delimiter2 = line.find('|', delimiter1 + 1); // Finds the second delimiter

        if (delimiter1 != std::string::npos && delimiter2 != std::string::npos) { // Checks if the delimiters are valid
            std::string name = line.substr(0, delimiter1); // Extracts the advisor's name
            std::string ability = line.substr(delimiter1 + 1, delimiter2 - delimiter1 - 1); // Extracts the advisor's ability
            std::string description = line.substr(delimiter2 + 1); // Extracts the advisor's description

            advisors.emplace_back(name, ability + ": " + description); // Adds the advisor to the list
        } else {
            std::cerr << "Error: Malformed line in advisors file: " << line << "\n"; // Prints error for malformed line
        }
    }
}

// Returns whether the game is over
bool Board::isGameOver() const {
    return gameOver;
}

// Returns the name of the current player
std::string Board::getCurrentPlayerName() const {
    return players[currentPlayerIndex].getName();
}

// Displays the current player's stats
void Board::viewPlayerStats() const {
    players[currentPlayerIndex].printStats();
}

void Board::reviewCharacter() const {
    // Gets the current player using their index
    const Player& player = players[currentPlayerIndex];
    // Prints out all attributes of the current player
    std::cout << "Name: " << player.getName() << "\n"
              << "Age: " << player.getAge() << "\n"
              << "Strength: " << player.getStrength() << "\n"
              << "Stamina: " << player.getStamina() << "\n"
              << "Wisdom: " << player.getWisdom() << "\n"
              << "Pride Points: " << player.getPridePoints() << "\n";
}

void Board::checkPosition() const {
    // Gets the current position of the current player
    int position = players[currentPlayerIndex].getPosition();
    // Prints the current position on the board
    std::cout << "You are currently on tile " << position << ".\n";
}

void Board::reviewAdvisor() const {
    // Prints the name of the current player's advisor
    std::cout << "Advisor: " << players[currentPlayerIndex].getAdvisor() << "\n";
}

void Board::moveCurrentPlayer() {
    // Rolls a six-sided dice to determine movement
    int diceRoll = rand() % 6 + 1;
    std::cout << "You rolled a " << diceRoll << "!\n";

    // Gets the current position and calculates the new position
    int currentPosition = players[currentPlayerIndex].getPosition();
    int newPosition = currentPosition + diceRoll;

    // Checks if the new position is past the final tile
    if (newPosition >= static_cast<int>(tiles.size())) {
        gameOver = true; // Sets game over to true
        newPosition = tiles.size() - 1; // Moves to the last tile
        std::cout << "Congratulations! You reached Pride Rock!\n";
    }

    // Updates the player's position
    players[currentPlayerIndex].setPosition(newPosition);

    // Gets the type of tile the player landed on
    std::string tileType = tiles[newPosition].getType();
    std::cout << "You landed on a " << tileType << " tile.\n";

    // Handles actions based on the type of tile
    if (tileType == "Regular") {
        int randomEventOrRiddle = rand() % 2; // Randomly decides between event or riddle
        if (randomEventOrRiddle == 0) {
            triggerRandomEvent(); // Triggers a random event
        } else {
            solveRiddle(); // Prompts the player with a riddle
        }
    } else if (tileType == "Oasis") {
        std::cout << "You found an Oasis! You gain an extra turn and 200 Stamina, Strength, and Wisdom Points.\n";
        players[currentPlayerIndex].adjustStats(0, 200, 200, 200);
        moveCurrentPlayer(); // Grants the player another turn
    } else if (tileType == "Counseling") {
        std::cout << "Welcome to the Counseling Tile! You gain 300 Stamina, Strength, and Wisdom Points.\n";
        players[currentPlayerIndex].adjustStats(0, 300, 300, 300);
        chooseAdvisor(players[currentPlayerIndex]); // Allows the player to choose an advisor
    } else if (tileType == "Graveyard") {
        std::cout << "Uh-oh, you've stumbled into the Graveyard! Move back 10 tiles and lose 100 Stamina, Strength, and Wisdom Points.\n";
        players[currentPlayerIndex].adjustStats(0, -100, -100, -100);
        players[currentPlayerIndex].setPosition(currentPosition - 10); // Moves the player back 10 tiles
        if (players[currentPlayerIndex].getPosition() < 0) players[currentPlayerIndex].setPosition(0); // Ensures position is not negative
    } else if (tileType == "Hyenas") {
        std::cout << "The Hyenas are on the prowl! You return to your previous position and lose 300 Stamina Points.\n";
        players[currentPlayerIndex].adjustStats(0, -300, 0, 0);
        players[currentPlayerIndex].setPosition(currentPosition); // Resets to the previous position
    } else if (tileType == "Challenge") {
        solveRiddle(); // Prompts the player with a riddle
    }

    displayBoard(); // Displays the updated board
}

void Board::displayBoard() const {
    // Loops through all the tiles on the board
    for (size_t i = 0; i < tiles.size(); ++i) {
        if (i % 10 == 0 && i != 0) {
            std::cout << "\n"; // Prints a new line every 10 tiles
        }

        bool playerOnTile = false; // Tracks if a player is on the current tile
        for (size_t j = 0; j < players.size(); ++j) {
            if (players[j].getPosition() == static_cast<int>(i)) {
                std::cout << (j + 1); // Displays the player number
                playerOnTile = true;
                break;
            }
        }

        if (!playerOnTile) {
            // Prints the tile type abbreviation
            std::string tileType = tiles[i].getType();
            if (tileType == "Start") {
                std::cout << "S"; 
            } else if (tileType == "Pride Rock") {
                std::cout << "P"; 
            } else if (tileType == "Oasis") {
                std::cout << "O"; 
            } else if (tileType == "Counseling") {
                std::cout << "C"; 
            } else if (tileType == "Graveyard") {
                std::cout << "G"; 
            } else if (tileType == "Hyenas") {
                std::cout << "H"; 
            } else if (tileType == "Challenge") {
                std::cout << "X"; 
            } else {
                std::cout << "R"; 
            }
        }

        std::cout << " "; // Adds space between tiles
    }
    std::cout << "\n"; // Final new line
}
void Board::triggerRandomEvent() {
    // Checks if there are any random events available
    if (!randomEvents.empty()) {
        int eventIndex = rand() % randomEvents.size(); // Selects a random event index
        std::string event = randomEvents[eventIndex]; // Retrieves the event
        std::cout << "Random Event: " << event << "\n"; // Displays the event

        size_t delimiter = event.find('|'); // Finds the delimiter separating event description and effect
        if (delimiter != std::string::npos) {
            std::string effect = event.substr(delimiter + 1); // Extracts the effect part of the event

            if (effect.find("Lose") != std::string::npos) { // Checks if the effect involves losing points
                try {
                    int points = std::stoi(effect.substr(effect.find_last_of(' ') + 1)); // Parses the points value
                    players[currentPlayerIndex].adjustStats(-points, 0, 0, 0); // Deducts pride points
                    std::cout << players[currentPlayerIndex].getName() << " lost " << points << " Pride Points.\n";
                } catch (const std::invalid_argument&) {
                    std::cerr << "Error: Invalid points value in random event.\n"; // Handles invalid points value
                }
            } else if (effect.find("Gain") != std::string::npos) { // Checks if the effect involves gaining points
                try {
                    int points = std::stoi(effect.substr(effect.find_last_of(' ') + 1)); // Parses the points value
                    players[currentPlayerIndex].adjustStats(points, 0, 0, 0); // Adds pride points
                    std::cout << players[currentPlayerIndex].getName() << " gained " << points << " Pride Points.\n";
                } catch (const std::invalid_argument&) {
                    std::cerr << "Error: Invalid points value in random event.\n"; // Handles invalid points value
                }
            }
        } else {
            std::cerr << "Error: Malformed random event string.\n"; // Handles malformed event strings
        }
    } else {
        std::cout << "No random events to trigger.\n"; // Informs the user that no events are available
    }
}

void Board::solveRiddle() {
    // Checks if there are any riddles available
    if (!riddles.empty()) {
        int riddleIndex = rand() % riddles.size(); // Selects a random riddle index
        std::cout << "Riddle: " << riddles[riddleIndex] << "\nYour answer: "; // Displays the riddle
        std::string answer;
        std::cin.ignore(); // Clears the input buffer
        std::getline(std::cin, answer); // Gets the player's answer

        if (answer == riddleAnswers[riddleIndex]) { // Checks if the answer is correct
            std::cout << "Correct! You gain 500 Wisdom Points.\n";
            players[currentPlayerIndex].adjustWisdom(500); // Awards points for a correct answer
        } else {
            std::cout << "Incorrect! No points awarded.\n"; // No points for incorrect answers
        }
    } else {
        std::cout << "No riddles to solve.\n"; // Informs the user that no riddles are available
    }
}

void Board::switchToNextPlayer() {
    // Advances to the next player in the players vector
    currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
}

void Board::endGame() {
    std::cout << "Game Over! Final Scores:\n"; // Displays the end game message
    for (const auto& player : players) {
        // Calculates the final score for each player
        int finalScore = player.getPridePoints() +
                         (player.getStrength() / 100) * 1000 +
                         (player.getStamina() / 100) * 1000 +
                         (player.getWisdom() / 100) * 1000;
        std::cout << player.getName() << ": " << finalScore << " Pride Points.\n"; // Displays the player's score
    }

    // Determines the winner or if there is a tie
    if (players[0].getPridePoints() > players[1].getPridePoints()) {
        std::cout << players[0].getName() << " is the new Pride Leader!\n";
    } else if (players[0].getPridePoints() < players[1].getPridePoints()) {
        std::cout << players[1].getName() << " is the new Pride Leader!\n";
    } else {
        std::cout << "It's a tie! Both players are Pride Leaders!\n";
    }
    gameOver = true; // Ends the game
}

int Board::displayMainMenu() const {
    // Displays the main menu options
    std::cout << "\nMain Menu:\n"
              << "1. Check Player Progress\n"
              << "2. Review Character\n"
              << "3. Check Position\n"
              << "4. Review Advisor\n"
              << "5. Move Forward\n"
              << "Choose an option: ";
    int choice;
    std::cin >> choice; // Takes user input for menu selection
    return choice; // Returns the selected option
}