#include "Board.h"
#include <iostream>
using namespace std;

int main() {
    Board board(1);
    board.displayBoard();
    board.movePlayer(0);
    return 0;
}
