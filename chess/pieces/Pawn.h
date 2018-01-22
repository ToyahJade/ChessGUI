#ifndef CHESS_PAWN_H
#define CHESS_PAWN_H


#include "Piece.h"

class Pawn : public Piece {
public:
    Pawn(int file, int rank, short colour);
    ~Pawn() override = default;
};


#endif //CHESS_PAWN_H
