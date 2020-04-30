#ifndef MAINGAMEWINDOW_H
#define MAINGAMEWINDOW_H

#include "../Controller/GameManager.h"

#include "PuzzleGrid.h"

#include <FL/Fl_Button.H>
#include <Fl/Fl.H>
#include <Fl/Fl_Box.H>
#include <FL/Fl_Group.H>
#include <Fl/Fl_Window.H>
#include <Fl/Fl_Export.H>
#include <algorithm>
#include <string>

using namespace controller;
using namespace std;

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
        Fl_Box* gameTimerLabel;
        vector<Fl_Box*> highScoreLabels;

        string getPuzzleNumberOutput();

    public:
        MainGameWindow(int width, int height, const char* title);
        virtual ~MainGameWindow();

        GameManager* getGameManager();

        void refreshBoard();
        void drawPuzzleNumberLabel();
        void addEvaluateButton();
        void addResetButton();
        void drawHighScoresLabel();

        static void cbEvaluateButtonClicked(Fl_Widget*, void*);
        static void cbResetButtonClicked(Fl_Widget*, void*);
        static void cbOnWindowClose(Fl_Widget*, void*);

        void startGameTimer();
        static void onTimerTick(void *data);

        void drawTimerLabel();

        void refreshTimerLabel();

    void updateHighScoreLabels();
};

}

#endif // MAINGAMEWINDOW_H
