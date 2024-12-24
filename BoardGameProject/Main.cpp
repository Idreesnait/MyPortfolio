#include "Board.h" // Includes the Board class definition and associated functions
#include "Player.h" // Includes the Player class definition and associated functions
#include <iostream>   // Enables input and output operations (e.g., std::cin, std::cout)
#include <vector>     // Provides the vector container for dynamic arrays
#include <fstream>    // Enables file input/output operations

// Function to load character data from a file into a vector of Player objects
void loadCharacters(const std::string& filename, std::vector<Player>& characters) {
    std::ifstream file(filename); // Opens the specified file for reading
    if (!file) { // Checks if the file failed to open
        std::cerr << "Error: Unable to open " << filename << "\n"; // Displays error message
        exit(1); // Exits the program with error status
    }

    std::string line; // Variable to store each line of the file
    while (std::getline(file, line)) { // Reads the file line by line
        // Find the positions of the delimiters '|' in the line
        size_t delimiter1 = line.find('|');
        size_t delimiter2 = line.find('|', delimiter1 + 1);
        size_t delimiter3 = line.find('|', delimiter2 + 1);
        size_t delimiter4 = line.find('|', delimiter3 + 1);
        size_t delimiter5 = line.find('|', delimiter4 + 1);

        // Extract character attributes using substrings
        std::string name = line.substr(0, delimiter1);
        int age = std::stoi(line.substr(delimiter1 + 1, delimiter2 - delimiter1 - 1));
        int strength = std::stoi(line.substr(delimiter2 + 1, delimiter3 - delimiter2 - 1));
        int stamina = std::stoi(line.substr(delimiter3 + 1, delimiter4 - delimiter3 - 1));
        int wisdom = std::stoi(line.substr(delimiter4 + 1, delimiter5 - delimiter4 - 1));
        int pridePoints = std::stoi(line.substr(delimiter5 + 1));

        // Create a Player object and add it to the vector
        characters.emplace_back(name, age, strength, stamina, wisdom, pridePoints);
    }
}

int main() {
    std::cout << "Welcome to The Circle of Life Board Game!\n"; // Greets the player

    std::vector<Player> availableCharacters; // Vector to hold all available characters
    loadCharacters("characters.txt", availableCharacters); // Loads character data from a file

    Player player1, player2; // Player objects for the two players

    Board gameBoard; // Creates the game board object

    // Load additional game components from files
    gameBoard.loadAdvisors("advisors.txt");
    gameBoard.loadRiddles("riddles.txt");
    gameBoard.loadRandomEvents("random_events.txt");

    // Player 1 chooses their character
    std::cout << "Player 1, choose your character:\n";
    for (size_t i = 0; i < availableCharacters.size(); ++i) { // Displays all characters
        std::cout << i + 1 << ". " << availableCharacters[i].getName() << "\n";
    }
    int choice1;
    std::cin >> choice1; // Takes input for character selection
    player1 = availableCharacters[choice1 - 1]; // Assigns the chosen character to player1
    availableCharacters.erase(availableCharacters.begin() + (choice1 - 1)); // Removes chosen character from the list

    // Player 2 chooses their character
    std::cout << "Player 2, choose your character:\n";
    for (size_t i = 0; i < availableCharacters.size(); ++i) { // Displays remaining characters
        std::cout << i + 1 << ". " << availableCharacters[i].getName() << "\n";
    }
    int choice2;
    std::cin >> choice2; // Takes input for character selection
    player2 = availableCharacters[choice2 - 1]; // Assigns the chosen character to player2

    // Flags to track if players choose Cub Training
    bool cubTraining1 = false, cubTraining2 = false;

    // Player 1 chooses their path
    std::cout << player1.getName() << ", choose your path:\n";
    std::cout << "1. Cub Training\n";
    std::cout << "2. Straight to the Pride Lands\n";
    int path1;
    std::cin >> path1; // Takes input for path selection

    if (path1 == 1) {
        std::cout << "You chose Cub Training. Let's pick an advisor.\n";
        player1.setPath("Cub Training"); // Sets the player's path
        player1.adjustStats(-5000, 500, 500, 1000); // Adjusts stats for the chosen path
        cubTraining1 = true;
        gameBoard.chooseAdvisor(player1); // Player picks an advisor
    } else if (path1 == 2) {
        std::cout << "You chose Straight to the Pride Lands.\n";
        player1.setPath("Straight to the Pride Lands"); // Sets the player's path
        player1.adjustStats(5000, 200, 200, 200); // Adjusts stats for the chosen path
    }

    // Player 2 chooses their path
    std::cout << player2.getName() << ", choose your path:\n";
    std::cout << "1. Cub Training\n";
    std::cout << "2. Straight to the Pride Lands\n";
    int path2;
    std::cin >> path2; // Takes input for path selection

    if (path2 == 1) {
        std::cout << "You chose Cub Training. Let's pick an advisor.\n";
        player2.setPath("Cub Training"); // Sets the player's path
        player2.adjustStats(-5000, 500, 500, 1000); // Adjusts stats for the chosen path
        cubTraining2 = true;
        gameBoard.chooseAdvisor(player2); // Player picks an advisor
    } else if (path2 == 2) {
        std::cout << "You chose Straight to the Pride Lands.\n";
        player2.setPath("Straight to the Pride Lands"); // Sets the player's path
        player2.adjustStats(5000, 200, 200, 200); // Adjusts stats for the chosen path
    }

    // Initialize the board based on the players' choices
    if (cubTraining1 || cubTraining2) {
        gameBoard.initializeBoard(true); // Initializes the board with additional features
    } else {
        gameBoard.initializeBoard(false); // Initializes the standard board
    }

    gameBoard.setPlayers(player1, player2); // Sets the players on the game board

    // Main game loop
    while (!gameBoard.isGameOver()) { // Continues until the game ends
        std::cout << "It's " << gameBoard.getCurrentPlayerName() << "'s turn!\n"; // Displays current player's turn
        int choice = gameBoard.displayMainMenu(); // Displays the main menu and gets player's choice

        switch (choice) {
            case 1:
                gameBoard.viewPlayerStats(); // Views the player's stats
                break;
            case 2:
                gameBoard.reviewCharacter(); // Reviews character details
                break;
            case 3:
                gameBoard.checkPosition(); // Checks the player's position on the board
                break;
            case 4:
                gameBoard.reviewAdvisor(); // Reviews the advisor's details
                break;
            case 5:
                gameBoard.moveCurrentPlayer(); // Moves the current player on the board
                break;
            default:
                std::cout << "Invalid choice. Try again.\n"; // Handles invalid input
        }

        if (!gameBoard.isGameOver()) {
            gameBoard.switchToNextPlayer(); // Switches to the next player's turn
        }
    }

    gameBoard.endGame(); // Ends the game and displays the results

    return 0; // Program exit
}
