#include <iostream>
#include <algorithm>
#include <sstream>
#include "Game.h"

Game::Game() {
    _board = new Board;
    _previous_board = new Board;
}

Game::~Game() {
    delete _board;
}

// When a new game is started,
// we create a new board
void Game::newGame() {
    _currentPlayer = WHITE;

    delete _board;
    delete _previous_board;
    _board = new Board;
    _previous_board= new Board;
}

// We have to switch players after each turn,
// otherwise we get a very unfair game
void Game::switchPlayers() {
    if (_currentPlayer == WHITE) {
        _currentPlayer = BLACK;

    } else {
        _currentPlayer = WHITE;
    }

    // This seems as good a place as any to see if someone's in check
    if (_board->isInCheck(_currentPlayer)) {
        std::cout << "Check! Ha!" << std::endl;
    }
}

// This function checks whether a selected piece has any moves available
bool Game::isPieceSelectable(std::pair<int, int> selected) {
    // We find a list of all moveable pieces...
    Piece::positionList available = _board->listAllMovablePieces(_currentPlayer);

    // ...and if the move is not found in that list, return false...
    if (std::find(available.begin(), available.end(), selected) == available.end()) {
        return false;

    // ...otherwise, we select the piece and return true
    } else {
        _originalPiece = selected;
        return true;
    }
}

std::string Game::getLabel(int file, int rank) {
    return _board->getLabel(file, rank);
}

int Game::getLabelCode(int file, int rank) {
    return _board->getLabelCode(file, rank);
}

// Similarly to isMoveSelectable,
// we check if a selected piece can move to a given destination
bool Game::isMoveValid(std::pair<int, int> move) {
    // Make a list of all moves to an empty square and moves to take another piece
    _board->predictCheck = true;
    Piece::positionList empty = _board->listMovesToEmpty(_originalPiece);

    _board->predictCheck = true;
    Piece::positionList take = _board->listMovesToTake(_originalPiece);

    // If the selected move is found in either list, return true
    if (std::find(empty.begin(), empty.end(), move) != empty.end() ||
            std::find(take.begin(), take.end(), move) != take.end()) {
        _destinationPiece = move;
        return true;

    } else {
        return false;
    }
}

// Once a pair of piece and it's destination are selected as valid,
// we can move the piece
void Game::movePiece() {
    (*_previous_board) = (*_board);

    _board->movePiece(_originalPiece, _destinationPiece);
}

int Game::getPlayer() {
    return _currentPlayer;
}

bool Game::isInCheck() {
    return _board->isInCheck(_currentPlayer);
}

void Game::undo() {
    (*_board) = (*_previous_board);
}

std::string Game::getPiecePosition() {
    std::string translateFile[8] = {"A", "B", "C", "D", "E", "F", "G", "H"};
    std::stringstream rank;
    rank << (_originalPiece.second + 1);
    return translateFile[_originalPiece.first] + rank.str();
}

std::string Game::getMovePosition() {
    std::string translateFile[8] = {"A", "B", "C", "D", "E", "F", "G", "H"};
    std::stringstream rank;
    rank << (_destinationPiece.second + 1);
    return translateFile[_destinationPiece.first] + rank.str();
}
