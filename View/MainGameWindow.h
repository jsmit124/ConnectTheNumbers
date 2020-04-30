#ifndef MAINGAMEWINDOW_H
#define MAINGAMEWINDOW_H

#include "../Controller/GameManager.h"
using namespace controller;

#include "PuzzleGrid.h"

#include <FL/Fl_Button.H>
#include <Fl/Fl.H>
#include <Fl/Fl_Box.H>
#include <FL/Fl_Group.H>
#include <Fl/Fl_Window.H>
#include <Fl/Fl_Export.H>
#include <string>

namespace view
{

class MainGameWindow : public Fl_Window
{
    private:
        PuzzleGrid* puzzleGrid;
        GameManager* gameManager;

        Fl_Box* highScoresLabel;
        Fl_Button* evaluateButton;
        Fl_Button* resetButton;
        Fl_Box* puzzleNumberLabel;

        string* getPuzzleNumberOutput();

    public:
        MainGameWindow(int width, int height, const char* title);
        virtual ~MainGameWindow();

        GameManager* getGameManager();

        void updateBoardForNextPuzzle();
        void drawPuzzleNumberLabel();
        void addEvaluateButton();
        void addResetButton();
        void drawHighScoresLabel();

        static void cbEvaluateButtonClicked(Fl_Widget*, void*);
        static void cbResetButtonClicked(Fl_Widget*, void*);
};

}

#endif // MAINGAMEWINDOW_H
