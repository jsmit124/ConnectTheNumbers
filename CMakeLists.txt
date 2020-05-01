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
        IO/SettingsReader.cpp IO/SettingsReader.h IO/SettingsWriter.cpp IO/SettingsWriter.h
        Model/Puzzle.cpp Model/Puzzle.h Model/PuzzleManager.cpp Model/PuzzleManager.h Model/PuzzleNode.cpp Model/PuzzleNode.h
        Utils/Exceptions.h Utils/Utils.cpp Utils/Utils.h
        Enum/Difficulty.h
        View/PuzzleSelectionWindow.cpp View/PuzzleSelectionWindow.h
        View/ColorSelectionWindow.cpp View/ColorSelectionWindow.h
        View/MainGameWindow.cpp View/MainGameWindow.h
        View/PuzzleGrid.cpp View/PuzzleGrid.h
        View/ButtonValueWindow.cpp View/ButtonValueWindow.h
        View/PuzzleGridButton.cpp View/PuzzleGridButton.h
        Model/HighScoreManager.cpp Model/HighScoreManager.h
        Model/HighScoreEntry.cpp Model/HighScoreEntry.h IO/HighScoreReader.cpp IO/HighScoreReader.h IO/HighScoreWriter.cpp IO/HighScoreWriter.h
        Settings/PlayerSettings.cpp Settings/PlayerSettings.h
        View/InitialSettingsWindow.cpp View/InitialSettingsWindow.h View/HighScoreboardTable.cpp View/HighScoreboardTable.h)
TARGET_LINK_LIBRARIES(ConnectTheNumbers ${FLTK_LIBRARIES})
TARGET_LINK_LIBRARIES(ConnectTheNumbers ${OPENGL_LIBRARIES})