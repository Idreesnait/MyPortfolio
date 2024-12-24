#ifndef BOARD_H
#define BOARD_H

#include "Player.h"
#include "Tile.h"
#include <vector>
#include <string>
#include <utility>

class Board {
private:
    std::vector<Tile> tiles; 
    std::vector<Player> players; 
    int currentPlayerIndex; 
    int moves; 
    bool gameOver; 

   
    std::vector<std::string> riddles;
    std::vector<std::string> riddleAnswers;
    std::vector<std::string> randomEvents;
    std::vector<std::pair<std::string, std::string>> advisors;

public:
    Board();

    void setPlayers(const Player& player1, const Player& player2);
    void initializeBoard(bool cubTraining); 
    void loadRiddles(const std::string& filename);
    void loadRandomEvents(const std::string& filename);
    void loadAdvisors(const std::string& filename);
    void chooseAdvisor(Player& player);

    bool isGameOver() const;
    std::string getCurrentPlayerName() const;

    void viewPlayerStats() const;
    void reviewCharacter() const;
    void checkPosition() const;
    void reviewAdvisor() const;
    void moveCurrentPlayer();
    void triggerRandomEvent();
    void solveRiddle();
    void switchToNextPlayer();
    void endGame();
    void displayBoard() const; 

    int getMoves() const;
    int displayMainMenu() const;
};

#endif


//check this thingy