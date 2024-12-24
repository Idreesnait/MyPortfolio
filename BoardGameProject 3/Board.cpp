#include "Board.h"
#include "Tile.h"
#include "Player.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <iomanip> 
//line 170

Board::Board() : currentPlayerIndex(0), moves(0), gameOver(false) {
    srand(static_cast<unsigned int>(time(0))); // Seed random number generator
}

void Board::setPlayers(const Player& player1, const Player& player2) {
    players.push_back(player1);
    players.push_back(player2);
}

void Board::initializeBoard(bool cubTraining) {
    tiles.resize(104, Tile("Regular")); 
    tiles[0] = Tile("Start");
    tiles[tiles.size() - 1] = Tile("Pride Rock");

    int specialTileCount = 20;
    for (int i = 0; i < specialTileCount; ++i) {
        int index = rand() % (tiles.size() - 2) + 1; 
        if (cubTraining) {
            if (i % 4 == 0) {
                tiles[index] = Tile("Oasis");
            } else if (i % 4 == 1) {
                tiles[index] = Tile("Counseling");
            } else if (i % 4 == 2) {
                tiles[index] = Tile("Graveyard");
            } else {
                tiles[index] = Tile("Hyenas");
            }
        } else {
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

void Board::loadRiddles(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error: Unable to open " << filename << "\n";
        exit(1);
    }

    std::string line;
    while (std::getline(file, line)) {
        size_t delimiter = line.find('|');
        riddles.push_back(line.substr(0, delimiter));
        riddleAnswers.push_back(line.substr(delimiter + 1));
    }
}

void Board::loadRandomEvents(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error: Unable to open " << filename << "\n";
        exit(1);
    }

    std::string line;
    while (std::getline(file, line)) {
        randomEvents.push_back(line);
    }
}

void Board::chooseAdvisor(Player& player) {
    if (advisors.empty()) { 
        std::cout << "No advisors available to choose from.\n";
        return;
    }

    std::cout << "Choose your advisor:\n";
    for (size_t i = 0; i < advisors.size(); ++i) {
        std::cout << i + 1 << ". " << advisors[i].first << " - " << advisors[i].second << "\n"; 
    }

    int choice;
    std::cin >> choice;

    if (choice >= 1 && choice <= static_cast<int>(advisors.size())) { 
        player.setAdvisor(advisors[choice - 1].first); 
        std::cout << "Advisor " << advisors[choice - 1].first << " selected!\n";
    } else {
        std::cout << "Invalid choice. No advisor selected.\n";
    }
}

void Board::loadAdvisors(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error: Unable to open " << filename << "\n";
        exit(1); 
    }

    std::string line;
    while (std::getline(file, line)) {
        size_t delimiter1 = line.find('|');
        size_t delimiter2 = line.find('|', delimiter1 + 1);

        if (delimiter1 != std::string::npos && delimiter2 != std::string::npos) {
            std::string name = line.substr(0, delimiter1);
            std::string ability = line.substr(delimiter1 + 1, delimiter2 - delimiter1 - 1);
            std::string description = line.substr(delimiter2 + 1);

            advisors.emplace_back(name, ability + ": " + description); 
        } else {
            std::cerr << "Error: Malformed line in advisors file: " << line << "\n";
        }
    }
}

bool Board::isGameOver() const {
    return gameOver;
}

std::string Board::getCurrentPlayerName() const {
    return players[currentPlayerIndex].getName();
}

void Board::viewPlayerStats() const {
    players[currentPlayerIndex].printStats();
}

void Board::reviewCharacter() const {
    const Player& player = players[currentPlayerIndex];
    std::cout << "Name: " << player.getName() << "\n"
              << "Age: " << player.getAge() << "\n"
              << "Strength: " << player.getStrength() << "\n"
              << "Stamina: " << player.getStamina() << "\n"
              << "Wisdom: " << player.getWisdom() << "\n"
              << "Pride Points: " << player.getPridePoints() << "\n";
}

void Board::checkPosition() const {
    int position = players[currentPlayerIndex].getPosition();
    std::cout << "You are currently on tile " << position << ".\n";
}

void Board::reviewAdvisor() const {
    std::cout << "Advisor: " << players[currentPlayerIndex].getAdvisor() << "\n";
}

void Board::moveCurrentPlayer() {
    int diceRoll = rand() % 6 + 1;
    std::cout << "You rolled a " << diceRoll << "!\n";

    int currentPosition = players[currentPlayerIndex].getPosition();
    int newPosition = currentPosition + diceRoll;

    if (newPosition >= static_cast<int>(tiles.size())) {
        gameOver = true;
        newPosition = tiles.size() - 1; 
        std::cout << "Congratulations! You reached Pride Rock!\n";
    }

    players[currentPlayerIndex].setPosition(newPosition);

    std::string tileType = tiles[newPosition].getType();
    std::cout << "You landed on a " << tileType << " tile.\n";

    if (tileType == "Regular") {
        int randomEventOrRiddle = rand() % 2; 
        if (randomEventOrRiddle == 0) {
            triggerRandomEvent();
        } else {
            solveRiddle();
        }
    } else if (tileType == "Oasis") {
        std::cout << "You found an Oasis! You gain an extra turn and 200 Stamina, Strength, and Wisdom Points.\n";
        players[currentPlayerIndex].adjustStats(0, 200, 200, 200);
        moveCurrentPlayer();
    } else if (tileType == "Counseling") {
        std::cout << "Welcome to the Counseling Tile! You gain 300 Stamina, Strength, and Wisdom Points.\n";
        players[currentPlayerIndex].adjustStats(0, 300, 300, 300);
        chooseAdvisor(players[currentPlayerIndex]); 
    } else if (tileType == "Graveyard") {
        std::cout << "Uh-oh, you've stumbled into the Graveyard! Move back 10 tiles and lose 100 Stamina, Strength, and Wisdom Points.\n";
        players[currentPlayerIndex].adjustStats(0, -100, -100, -100);
        players[currentPlayerIndex].setPosition(currentPosition - 10); 
        if (players[currentPlayerIndex].getPosition() < 0) players[currentPlayerIndex].setPosition(0); 
    } else if (tileType == "Hyenas") {
        std::cout << "The Hyenas are on the prowl! You return to your previous position and lose 300 Stamina Points.\n";
        players[currentPlayerIndex].adjustStats(0, -300, 0, 0);
        players[currentPlayerIndex].setPosition(currentPosition); 
    } else if (tileType == "Challenge") {
        solveRiddle(); 
    }

    displayBoard(); 
}


   
void Board::displayBoard() const {
    for (size_t i = 0; i < tiles.size(); ++i) {
        if (i % 10 == 0 && i != 0) {
            std::cout << "\n";
        }

        bool playerOnTile = false;
        for (size_t j = 0; j < players.size(); ++j) {
            if (players[j].getPosition() == static_cast<int>(i)) {
                std::cout << (j + 1); 
                playerOnTile = true;
                break;
            }
        }

        if (!playerOnTile) {
           
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

        std::cout << " ";
    }
    std::cout << "\n";
}

void Board::triggerRandomEvent() {
    if (!randomEvents.empty()) {
        int eventIndex = rand() % randomEvents.size();
        std::string event = randomEvents[eventIndex];
        std::cout << "Random Event: " << event << "\n";

        size_t delimiter = event.find('|');
        if (delimiter != std::string::npos) {
            std::string effect = event.substr(delimiter + 1);

            if (effect.find("Lose") != std::string::npos) {
                try {
                    int points = std::stoi(effect.substr(effect.find_last_of(' ') + 1));
                    players[currentPlayerIndex].adjustStats(-points, 0, 0, 0);
                    std::cout << players[currentPlayerIndex].getName() << " lost " << points << " Pride Points.\n";
                } catch (const std::invalid_argument&) {
                    std::cerr << "Error: Invalid points value in random event.\n";
                }
            } else if (effect.find("Gain") != std::string::npos) {
                try {
                    int points = std::stoi(effect.substr(effect.find_last_of(' ') + 1));
                    players[currentPlayerIndex].adjustStats(points, 0, 0, 0);
                    std::cout << players[currentPlayerIndex].getName() << " gained " << points << " Pride Points.\n";
                } catch (const std::invalid_argument&) {
                    std::cerr << "Error: Invalid points value in random event.\n";
                }
            }
        } else {
            std::cerr << "Error: Malformed random event string.\n";
        }
    } else {
        std::cout << "No random events to trigger.\n";
    }
}


void Board::solveRiddle() {
    if (!riddles.empty()) {
        int riddleIndex = rand() % riddles.size();
        std::cout << "Riddle: " << riddles[riddleIndex] << "\nYour answer: ";
        std::string answer;
        std::cin.ignore();
        std::getline(std::cin, answer);

        if (answer == riddleAnswers[riddleIndex]) {
            std::cout << "Correct! You gain 500 Wisdom Points.\n";
            players[currentPlayerIndex].adjustWisdom(500);
        } else {
            std::cout << "Incorrect! No points awarded.\n";
        }
    } else {
        std::cout << "No riddles to solve.\n";
    }
}

void Board::switchToNextPlayer() {
    currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
}

void Board::endGame() {
    std::cout << "Game Over! Final Scores:\n";
    for (const auto& player : players) {
        int finalScore = player.getPridePoints() +
                         (player.getStrength() / 100) * 1000 +
                         (player.getStamina() / 100) * 1000 +
                         (player.getWisdom() / 100) * 1000;
        std::cout << player.getName() << ": " << finalScore << " Pride Points.\n";
    }

    if (players[0].getPridePoints() > players[1].getPridePoints()) {
        std::cout << players[0].getName() << " is the new Pride Leader!\n";
    } else if (players[0].getPridePoints() < players[1].getPridePoints()) {
        std::cout << players[1].getName() << " is the new Pride Leader!\n";
    } else {
        std::cout << "It's a tie! Both players are Pride Leaders!\n";
    }
    gameOver = true;
}

int Board::displayMainMenu() const {
    std::cout << "\nMain Menu:\n"
              << "1. Check Player Progress\n"
              << "2. Review Character\n"
              << "3. Check Position\n"
              << "4. Review Advisor\n"
              << "5. Move Forward\n"
              << "Choose an option: ";
    int choice;
    std::cin >> choice;
    return choice;
}

