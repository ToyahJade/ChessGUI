#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H


#include <array>
#include "FlatBoard.h"
#include "pieces/Empty.h"

// A class containing all the pieces, rules etc
class Board {
public:
    Board();

    Piece::positionList listMovesToEmpty(std::pair<int,int> piece);
    Piece::positionList listMovesToTake(std::pair<int, int> piece);
    Piece::positionList listAllMovablePieces(int colour);

    bool isInCheck(int colour);
    bool isPathClear(std::pair<int, int> piece, std::pair<int, int> move);
    std::string getLabel(int file, int rank);
    int getLabelCode(int file, int rank);

    void movePiece(std::pair<int, int> piece, std::pair<int, int> move);

    bool predictCheck = false;

private:
    // This is a container object that stores the pieces
    FlatBoard _board;
    // This is needed for predicting whether a move will put the king in check
    FlatBoard _temp_board;
    std::array<std::pair<int, int>, 2> _kingTracker;

    // Two functions to swap between the main board and the temporary board
    void storeOriginalBoard();
    void restoreOriginalBoard();

    Piece::positionList removeMovesToCheck(std::pair<int, int> pair, Piece::positionList moves);
};


#endif //CHESS_BOARD_H