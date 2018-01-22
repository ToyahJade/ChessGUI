#include "FlatBoard.h"
#include "pieces/Piece.h"
#include "pieces/Empty.h"
#include "pieces/Queen.h"


FlatBoard::FlatBoard() {
    for (int i = 0; i < 64; ++i) {
        _board[i] = new Empty(i / 8, i % 8);
    }
}

void FlatBoard::setPiece(Piece *piece) {
    delete _board[(piece->getFile() * 8) + piece->getRank()];
    _board[(piece->getFile() * 8) + piece->getRank()] = piece;
}

Piece* FlatBoard::getPiece(int file, int rank) {
    return _board[(file * 8) + rank];
}

Piece* FlatBoard::getPiece(std::pair<int, int> position) {
    return _board[(position.first * 8) + position.second];
}

Piece* FlatBoard::operator[](std::pair<int, int> position) {
    return getPiece(position);
}

void FlatBoard::movePiece(std::pair<int, int> origin, std::pair<int, int> destination) {
    int temp_color = _board[(origin.first * 8) + origin.second]->getColour();

    if (_board[(origin.first * 8) + origin.second]->isPawn()) {
        if (_board[(origin.first * 8) + origin.second]->getColour() == WHITE && destination.second == 7) {
            delete _board[(origin.first * 8) + origin.second];
            _board[(origin.first * 8) + origin.second] = new Queen(origin.first, origin.second, WHITE);

        } else if (_board[(origin.first * 8) + origin.second]->getColour() == BLACK && destination.second == 0) {
            delete _board[(origin.first * 8) + origin.second];
            _board[(origin.first * 8) + origin.second] = new Queen(origin.first, origin.second, BLACK);
        }
    }

    std::swap(_board[(origin.first * 8) + origin.second], _board[(destination.first * 8) + destination.second]);

    _board[(origin.first * 8) + origin.second]->setPosition(origin);
    _board[(destination.first * 8) + destination.second]->setPosition(destination);
    _board[(destination.first * 8) + destination.second]->setColour(temp_color);
}

FlatBoard::~FlatBoard() {
    for (int i = 0; i < 64; ++i) {
        delete _board[i];
    }
}

FlatBoard::FlatBoard(FlatBoard &rhs) : FlatBoard() {
    for (int i = 0; i < 64; ++i) {
        (*_board[i]) = (*rhs._board[i]);
    }
}

FlatBoard &FlatBoard::operator=(const FlatBoard &rhs) {
    if (&rhs != this) {
        for (int i = 0; i < 64; i++) {
            (*_board[i]) = (*rhs._board[i]);
            _board[i]->setColour(rhs._board[i]->getColour());
        }
    }

    return *this;
}