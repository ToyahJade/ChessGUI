#ifndef CHESS_EMPTY_H
#define CHESS_EMPTY_H


#include "Piece.h"

class Empty : public Piece {
public:
    Empty(int file, int rank);
    ~Empty() override = default;
};


#endif //CHESS_EMPTY_H
