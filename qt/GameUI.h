#ifndef CHESSGUI_GAMEUI_H
#define CHESSGUI_GAMEUI_H

#include <QWidget>
#include <array>
#include <QtWidgets/QPushButton>
#include <QTextEdit>
#include <unordered_map>
#include "../MainWindow.h"
#include "ClickableSquares.h"
#include "../chess/Board.h"
#include "../chess/Game.h"
#include "Timer.h"

class GameUI : public QWidget {
Q_OBJECT

public:
    explicit GameUI(MainWindow *parent);
    ~GameUI();
    // Function updating the board with correct labels for each piece.
    // This is called each time a move is made
    void drawPieces();

private:
    // Class containing the chess game.
    // This includes all pieces and the board,
    // along with the rules
    Game _game;
    // A button to start undo the last move
    QPushButton *undoButton;
    // A button to start a new game
    QPushButton *newGameButton;
    // A button to show a hint
    QPushButton *christmasButton;
    // Making a clickable board
    // This is chess, so 8x8 squares
    std::array<std::array<ClickableSquares*, 8>, 8> _gamingField;
    // A log of the whole game
    QTextEdit *logBox;
    std::array<Timer*, 2> timerLCD;
    std::array<QLabel*, 2> takenPieces;

    QLabel *whiteBox;
    QLabel *blackBox;

    bool _isChristmas = false;
    std::unordered_map<int, QPixmap> _christmasTheme;

// Qt operates on the principle of sending signals to designated slots.
// This tells different parts of the code what actions to perform.
// (This is basically a glorified goto)
public slots:
    // Function called when a ClickableSquare is pressed
    void squareClicked(int x, int y);
    // Function called when newGameButton is pressed
    void pressedNewGame();
    // Undo previous move if pressed undo button
    void pressedUndo();
    // Set a christmas theme!
    void pressedChristmas();

    void loadChristmas();
};

#endif // CHESSGUI_GAMEUI_H
