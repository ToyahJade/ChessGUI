#ifndef CHESS_FLATBOARD_H
#define CHESS_FLATBOARD_H


#include <array>
#include "pieces/Piece.h"

class FlatBoard {
public:
    FlatBoard();
    FlatBoard(FlatBoard &rhs);
    ~FlatBoard();

    std::array<Piece*, 64>::iterator getBegin() { return _board.begin(); }
    std::array<Piece*, 64>::iterator getEnd() { return _board.end(); }

    Piece* getPiece(int file, int rank);
    Piece* getPiece(std::pair<int,int>);
    Piece* operator[](std::pair<int,int> position);
    FlatBoard& operator=(const FlatBoard &rhs);

    void setPiece(Piece* piece);
    void movePiece(std::pair<int, int> origin, std::pair<int, int> destination);

private:
    std::array<Piece*, 64> _board;
};


#endif //CHESS_FLATBOARD_H
