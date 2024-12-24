#include "Board.h"
#include <iostream>
#include <cstdlib>
using namespace std;

Board::Board() : _player_count(1) {
    initializeBoard();
}

Board::Board(int player_count) : _player_count(player_count) {
    initializeBoard();
}

void Board::initializeTiles(int player_index) {
    for (int i = 0; i < _BOARD_SIZE; i++) {
        int random = rand() % 100;
        if (player_index == 0) {
            if (i < _BOARD_SIZE / 2 && random < 25) {
                cout << "Adding Graveyard tile\n";
            } else {
                cout << "Adding Grassland tile\n";
            }
        } else {
            if (random < 20) {
                cout << "Adding Advisor tile\n";
            } else {
                cout << "Adding Grassland tile\n";
            }
        }
    }
}

void Board::initializeBoard() {
    for (int i = 0; i < _MAX_PLAYERS; i++) {
        _player_position[i] = 0;
    }
    for (int i = 0; i < 2; i++) {
        initializeTiles(i);
    }
}

void Board::displayBoard() {
    cout << "Displaying the board.\n";
}

bool Board::movePlayer(int player_index) {
    cout << "Moving player " << player_index << "\n";
    return true;
}

int Board::getPlayerPosition(int player_index) const {
    return _player_position[player_index];
}
