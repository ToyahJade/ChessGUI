#ifndef CHESS_QUEEN_H
#define CHESS_QUEEN_H


#include "Piece.h"

class Queen : public Piece {
public:
    Queen(int file, int rank, short colour);
    ~Queen() override = default;
};


#endif //CHESS_QUEEN_H
