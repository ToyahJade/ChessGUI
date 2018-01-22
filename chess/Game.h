#ifndef CHESSGUI_GAME_H
#define CHESSGUI_GAME_H

#include "pieces/Piece.h"
#include "Board.h"

// This is the main control class for the whole game.
// It stores the board, the pieces being moved and the player
class Game {
public:
    Game();
    ~Game();

    void newGame();
    void switchPlayers();
    void movePiece();
    bool isPieceSelectable(std::pair<int, int> selected);
    bool isMoveValid(std::pair<int, int> move);

    // We start with no pieces selected
    // This flag is used inside of GameUI
    bool isPieceSelected = false;
    std::string getLabel(int file, int rank);
    int getLabelCode(int file, int rank);
    int getPlayer();
    bool isInCheck();

    void undo();
    std::string getPiecePosition();
    std::string getMovePosition();

private:
    // Stores a copy of the board class,
    // which contains all of the pieces and information about them,
    // as well as all of the rules.
    Board* _board;
    Board* _previous_board;
    int _currentPlayer;

    // To do: rename these!
    // Used by isPieceSelected and isMoveValid
    // when determining if a piece at the position originalPiece
    // can be moved to the position of destinationPiece
    std::pair<int, int> _originalPiece;
    std::pair<int, int> _destinationPiece;
};


#endif //CHESSGUI_GAME_H
