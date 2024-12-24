#ifndef BOARD_H
#define BOARD_H
#include "Tile.h"

class Board {
private:
    static const int _BOARD_SIZE = 52;
    Tile _tiles[2][_BOARD_SIZE];
    static const int _MAX_PLAYERS = 2;
    int _player_count;
    int _player_position[_MAX_PLAYERS];
    void initializeTiles(int player_index);
    void initializeBoard();

public:
    Board();
    Board(int player_count);
    void displayBoard();
    bool movePlayer(int player_index);
    int getPlayerPosition(int player_index) const;
};

#endif
