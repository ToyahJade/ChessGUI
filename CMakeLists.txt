cmake_minimum_required(VERSION 3.8)
project(ChessGUI)
set(CMAKE_AUTOMOC ON)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        chess/pieces/Bishop.cpp
        chess/pieces/Bishop.h
        chess/pieces/Empty.cpp
        chess/pieces/Empty.h
        chess/pieces/King.cpp
        chess/pieces/King.h
        chess/pieces/Knight.cpp
        chess/pieces/Knight.h
        chess/pieces/Pawn.cpp
        chess/pieces/Pawn.h
        chess/pieces/Piece.cpp
        chess/pieces/Piece.h
        chess/pieces/Queen.cpp
        chess/pieces/Queen.h
        chess/pieces/Rook.cpp
        chess/pieces/Rook.h
        chess/Board.cpp
        chess/Board.h
        chess/FlatBoard.cpp
        chess/FlatBoard.h
        main.cpp
        MainWindow.cpp
        MainWindow.h
        qt/GameUI.cpp
        qt/GameUI.h
        qt/ClickableSquares.cpp
        qt/ClickableSquares.h chess/Game.cpp chess/Game.h qt/Timer.cpp qt/Timer.h)

find_package(Qt5Widgets REQUIRED)

add_executable(ChessGUI ${SOURCE_FILES})
target_link_libraries(ChessGUI Qt5::Widgets)