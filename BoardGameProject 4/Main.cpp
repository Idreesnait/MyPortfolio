#include "Board.h"
#include "Player.h"
#include <iostream>
#include <vector>
#include <fstream>

void loadCharacters(const std::string& filename, std::vector<Player>& characters) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error: Unable to open " << filename << "\n";
        exit(1);
    }

    std::string line;
    while (std::getline(file, line)) {
        size_t delimiter1 = line.find('|');
        size_t delimiter2 = line.find('|', delimiter1 + 1);
        size_t delimiter3 = line.find('|', delimiter2 + 1);
        size_t delimiter4 = line.find('|', delimiter3 + 1);
        size_t delimiter5 = line.find('|', delimiter4 + 1);

        std::string name = line.substr(0, delimiter1);
        int age = std::stoi(line.substr(delimiter1 + 1, delimiter2 - delimiter1 - 1));
        int strength = std::stoi(line.substr(delimiter2 + 1, delimiter3 - delimiter2 - 1));
        int stamina = std::stoi(line.substr(delimiter3 + 1, delimiter4 - delimiter3 - 1));
        int wisdom = std::stoi(line.substr(delimiter4 + 1, delimiter5 - delimiter4 - 1));
        int pridePoints = std::stoi(line.substr(delimiter5 + 1));

        characters.emplace_back(name, age, strength, stamina, wisdom, pridePoints);
    }
}

int main() {
    std::cout << "Welcome to The Circle of Life Board Game!\n";

    std::vector<Player> availableCharacters;
    loadCharacters("characters.txt", availableCharacters);

    Player player1, player2;

    Board gameBoard;

    gameBoard.loadAdvisors("advisors.txt");
    gameBoard.loadRiddles("riddles.txt");
    gameBoard.loadRandomEvents("random_events.txt");

    std::cout << "Player 1, choose your character:\n";
    for (size_t i = 0; i < availableCharacters.size(); ++i) {
        std::cout << i + 1 << ". " << availableCharacters[i].getName() << "\n";
    }
    int choice1;
    std::cin >> choice1;
    player1 = availableCharacters[choice1 - 1];
    availableCharacters.erase(availableCharacters.begin() + (choice1 - 1));

    std::cout << "Player 2, choose your character:\n";
    for (size_t i = 0; i < availableCharacters.size(); ++i) {
        std::cout << i + 1 << ". " << availableCharacters[i].getName() << "\n";
    }
    int choice2;
    std::cin >> choice2;
    player2 = availableCharacters[choice2 - 1];

    bool cubTraining1 = false, cubTraining2 = false;

    std::cout << player1.getName() << ", choose your path:\n";
    std::cout << "1. Cub Training\n";
    std::cout << "2. Straight to the Pride Lands\n";
    int path1;
    std::cin >> path1;

    if (path1 == 1) {
        std::cout << "You chose Cub Training. Let's pick an advisor.\n";
        player1.setPath("Cub Training");
        player1.adjustStats(-5000, 500, 500, 1000);
        cubTraining1 = true;
        gameBoard.chooseAdvisor(player1);
    } else if (path1 == 2) {
        std::cout << "You chose Straight to the Pride Lands.\n";
        player1.setPath("Straight to the Pride Lands");
        player1.adjustStats(5000, 200, 200, 200);
    }

    std::cout << player2.getName() << ", choose your path:\n";
    std::cout << "1. Cub Training\n";
    std::cout << "2. Straight to the Pride Lands\n";
    int path2;
    std::cin >> path2;

    if (path2 == 1) {
        std::cout << "You chose Cub Training. Let's pick an advisor.\n";
        player2.setPath("Cub Training");
        player2.adjustStats(-5000, 500, 500, 1000);
        cubTraining2 = true;
        gameBoard.chooseAdvisor(player2);
    } else if (path2 == 2) {
        std::cout << "You chose Straight to the Pride Lands.\n";
        player2.setPath("Straight to the Pride Lands");
        player2.adjustStats(5000, 200, 200, 200);
    }

    if (cubTraining1 || cubTraining2) {
        gameBoard.initializeBoard(true);
    } else {
        gameBoard.initializeBoard(false);
    }

    gameBoard.setPlayers(player1, player2);

    while (!gameBoard.isGameOver()) {
        std::cout << "It's " << gameBoard.getCurrentPlayerName() << "'s turn!\n";
        int choice = gameBoard.displayMainMenu();

        switch (choice) {
            case 1:
                gameBoard.viewPlayerStats();
                break;
            case 2:
                gameBoard.reviewCharacter();
                break;
            case 3:
                gameBoard.checkPosition();
                break;
            case 4:
                gameBoard.reviewAdvisor();
                break;
            case 5:
                gameBoard.moveCurrentPlayer();
                break;
            default:
                std::cout << "Invalid choice. Try again.\n";
        }

        if (!gameBoard.isGameOver()) {
            gameBoard.switchToNextPlayer();
        }
    }

    gameBoard.endGame();

    return 0;
}
