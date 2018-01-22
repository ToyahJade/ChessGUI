#include <iostream>
#include <algorithm>
#include <vector>
#include "Board.h"
#include "pieces/Pawn.h"
#include "pieces/Bishop.h"
#include "pieces/Knight.h"
#include "pieces/King.h"
#include "pieces/Queen.h"
#include "pieces/Rook.h"
#include "pieces/Empty.h"

// The constuctor for class Board creates the pieces and puts them on the board
Board::Board() {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if ((i == 2 && j == 0) || (i == 5 && j == 0)) {
                _board.setPiece(new Bishop(i, j, WHITE));

            } else if ((i == 2 && j == 7) || (i == 5 && j == 7)) {
                _board.setPiece(new Bishop(i, j, BLACK));

            } else if ((i == 1 && j == 0) || (i == 6 && j == 0)) {
                _board.setPiece(new Knight(i, j, WHITE));

            } else if ((i == 1 && j == 7) || (i == 6 && j == 7)) {
                _board.setPiece(new Knight(i, j, BLACK));

            } else if (i == 4 && j == 0) {
                _board.setPiece(new King(i, j, WHITE));
                _kingTracker[WHITE] = std::make_pair(i, j);

            } else if (i == 4 && j == 7) {
                _board.setPiece(new King(i, j, BLACK));
                _kingTracker[BLACK] = std::make_pair(i, j);

            } else if (j == 1) {
                _board.setPiece(new Pawn(i, j, WHITE));

            } else if (j == 6) {
                _board.setPiece(new Pawn(i, j, BLACK));

            } else if (i == 3 && j == 0) {
                _board.setPiece(new Queen(i, j, WHITE));

            } else if (i == 3 && j == 7) {
                _board.setPiece(new Queen(i, j, BLACK));

            } else if ((i == 0 && j == 0) || (i == 7 && j == 0)) {
                _board.setPiece(new Rook(i, j, WHITE));

            } else if ((i == 0 && j == 7) || (i == 7 && j == 7)) {
                _board.setPiece(new Rook(i, j, BLACK));

            } else {
                _board.setPiece(new Empty(i, j));
            }
        }
    }
}

// For a given piece, list all moves it can do to an empty square
Piece::positionList Board::listMovesToEmpty(std::pair<int,int> piece) {
    // First, get a list of all moves the piece could do if no other pieces existed
    Piece::positionList moves = _board[piece]->listMoves();

    // For each move, check it it's valid
    for (auto it = moves.begin(); it != moves.end(); ) {
        // If the move is to an occupied square, remove it
        if (!_board[*it]->isEmpty()) {
            it = moves.erase(it);

        // Otherwise, unless the piece is a knight (aka "can hop" from the script...)...
        } else if (!_board[piece]->isKnight()) {
            // ...check if the path between the piece and the move is clear.
            // If the piece is a pawn, make sure it can only move vertically
            if ((!isPathClear(piece, *it)) ||
                (_board[piece]->isPawn() && (abs(piece.first - it->first) == abs(piece.second - it->second)))) {
                it = moves.erase(it);

            } else {
                ++it;
            }

        } else {
            ++it;
        }
    }

    // Moves that expose the king to check are not valid,
    // so we must predict what the board will look like after each potential move is done.
    // We then can remove any move that would put him in check.
    // The predictCheck flag is used to stop the function from recursively checking the predicted moves
    if (predictCheck) {
        moves = removeMovesToCheck(piece, moves);
    }

    return moves;
}

// Finds all pieces that can be taken by the selected piece
Piece::positionList Board::listMovesToTake(std::pair<int, int> piece) {
    // First, find all moves that a piece can take and all moves to empty
    Piece::positionList emptyMovesList = listMovesToEmpty(piece);
    Piece::positionList allMovesList = _board[piece]->listMoves();

    emptyMovesList.sort();
    allMovesList.sort();

    // Remove the moves which we already know are not moves to the position of another piece
    // i.e. moves to empty
    Piece::positionList moves;
    // This is done by subtracting one list from another using a standard library routine
    std::set_difference(allMovesList.begin(), allMovesList.end(),
                        emptyMovesList.begin(), emptyMovesList.end(),
                        std::inserter(moves, moves.begin()));

    // For all remaining moves...
    for (auto it = moves.begin(); it != moves.end(); ) {
        // if the piece is of the same color as the selected piece,
        // we cannot take this piece so we remove it
        if (_board[piece]->getColour() == _board[*it]->getColour() ||
                (_board[piece]->isPawn() && (abs(piece.first - it->first) == 0)) ||
                _board[*it]->isEmpty()) {
            it = moves.erase(it);

        } else if (!_board[piece]->isKnight()) {
            // if the path is clear we can do the move
            if (isPathClear(piece, *it)) {
                it++;

            } else {
                it = moves.erase(it);
            }

        } else {
                ++it;
        }
    }

    if (predictCheck) {
        moves = removeMovesToCheck(piece, moves);
    }

    return moves;
}

// A function that checks if the squares along the path of the selected piece are empty
bool Board::isPathClear(std::pair<int, int> piece, std::pair<int, int> move) {
    // Find the horizontal and vertical distance between squares
    int dx = move.first - piece.first;
    int dy = move.second - piece.second;
    int distance = std::max<int>(abs(dx), abs(dy));

    bool isClear = true;
    // Check if any pieces lay along the path between the piece and move.
    // If yes, then isClear will be multiplied by false hence will be always false
    for (int i = 1; i < distance; ++i) {
        isClear *= _board.getPiece(piece.first + (dx * i / distance),
                                   piece.second + (dy * i / distance))->isEmpty();
    }

    return isClear;
}

// Check which pieces of a given color can be moved
Piece::positionList Board::listAllMovablePieces(int colour) {
    Piece::positionList moveablePiece;

    // Loop through every piece
    for (auto it = _board.getBegin(); it != _board.getEnd(); it++) {
        // If the color of the piece matches whose turn it is...
        if (colour == (*it)->getColour()) {
            // ...check if either listMovesToEmpty or listMovesToTake does not return an empty list
            if (!listMovesToEmpty((*it)->getPosition()).empty() ||
                    !listMovesToTake((*it)->getPosition()).empty()) {
                // If so, then this piece is moveable
                moveablePiece.push_back((*it)->getPosition());
            }
        }
    }

    return moveablePiece;
}

// Check if the king of "color" is in check
// (checking for check... nice sentence)
bool Board::isInCheck(int colour) {
    bool inCheck = false;

    // Looop through every piece
    for (auto it = _board.getBegin(); it != _board.getEnd(); it++) {
        // If the piece is not empty and the color is the color of the opponent...
        if (!(*it)->isEmpty() && colour != (*it)->getColour()) {
            // ...find a list of all pieces that piece can take
            Piece::positionList moves = listMovesToTake((*it)->getPosition());

            // If the king is in that list, the king is in check
            // (Uh-oh!)
            if (std::find(moves.begin(), moves.end(), _kingTracker[colour]) != moves.end()) {
                inCheck = true;
            }
        }
    }

    return inCheck;
}

std::string Board::getLabel(int file, int rank) {
    return _board.getPiece(file, rank)->getLabel();
}

// Moves the piece while also tracking the king
void Board::movePiece(std::pair<int, int> piece, std::pair<int, int> move) {
    _board.movePiece(piece, move);
    _board.setPiece(new Empty(piece.first, piece.second));

    if (_board[move]->isKing()) {
        _kingTracker[_board[move]->getColour()] = move;
    }
}

void Board::storeOriginalBoard() {
    _temp_board = _board;
}

void Board::restoreOriginalBoard() {
    _board = _temp_board;
}

// Removes moves which would lead to exposing the king to check
Piece::positionList Board::removeMovesToCheck(std::pair<int, int> piece, Piece::positionList moves) {
    predictCheck = false;
    Piece::positionList temp = moves;
    int currentPlayer = _board[piece]->getColour();

    for (auto it = temp.begin(); it != temp.end();) {
        // Make a temporary copy of the board
        storeOriginalBoard();
        // Make a mock move on the temporary board
        movePiece(piece, (*it));
        // I have a ladybug...
        // Colors aren't copied between the temporary and real board
        _board[piece]->setColour(currentPlayer);

        // If the mock move would put the king in check, remove it
        if (isInCheck(currentPlayer)) {
            it = temp.erase(it);

        } else {
            it++;
        }

        restoreOriginalBoard();
    }

    return temp;
}

int Board::getLabelCode(int file, int rank) {
    return _board.getPiece(file, rank)->getLabelCode();
}
