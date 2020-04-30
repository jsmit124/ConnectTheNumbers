cmake_minimum_required(VERSION 3.15)
project(MoviePlaiter)

set(CMAKE_CXX_STANDARD 11)

set(FLTK_SKIP_FLUID)
find_package(FLTK REQUIRED)

include_directories(Model)
include_directories(Utils)
include_directories(View)

add_executable(ConnectTheNumbers
        main.cpp
        Controller/GameManager.cpp Controller/GameManager.h
        IO/PuzzleReader.cpp IO/PuzzleReader.h IO/PuzzleWriter.cpp IO/PuzzleWriter.h
        Model/Puzzle.cpp Model/Puzzle.h Model/PuzzleManager.cpp Model/PuzzleManager.h Model/PuzzleNode.cpp Model/PuzzleNode.h
        Utils/Exceptions.h Utils/Utils.cpp Utils/Utils.h
        View/MainGameWindow.cpp View/MainGameWindow.h
        View/PuzzleGrid.cpp View/PuzzleGrid.h
        View/ButtonValueWindow.cpp View/ButtonValueWindow.h
        View/PuzzleGridButton.cpp View/PuzzleGridButton.h
        Model/HighScoreManager.cpp Model/HighScoreManager.h
        Model/HighScoreEntry.cpp Model/HighScoreEntry.h)
TARGET_LINK_LIBRARIES(ConnectTheNumbers ${FLTK_LIBRARIES})
TARGET_LINK_LIBRARIES(ConnectTheNumbers ${OPENGL_LIBRARIES})