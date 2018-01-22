#ifndef CHESSGUI_MAINWINDOW_H
#define CHESSGUI_MAINWINDOW_H

#include <QMainWindow>

// This is a standard class required by Qt
// which controls the entire window
class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow() override;

    void initialise();

private:
    // This is the user interface for the game.
    // It contains all buttons, the board etc
    QWidget *gameUI;

};

#endif // CHESSGUI_MAINWINDOW_H
