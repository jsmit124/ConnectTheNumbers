#ifndef MAINGAMEWINDOW_H
#define MAINGAMEWINDOW_H

#include "../Controller/GameManager.h"

#include "PuzzleGrid.h"
#include "InitialSettingsWindow.h"

#include <FL/Fl_Button.H>
#include <Fl/Fl.H>
#include <Fl/Fl_Box.H>
#include <FL/Fl_Group.H>
#include <Fl/Fl_Window.H>
#include <Fl/Fl_Export.H>
#include <algorithm>
#include <string>
#include <thread>
#include <chrono>
using namespace std;

#include "../Settings/PlayerSettings.h"

using namespace settings;
using namespace controller;
using namespace std;

namespace view
{

class MainGameWindow : public Fl_Window
{
    private:
        PuzzleGrid* puzzleGrid;
        GameManager* gameManager;
        InitialSettingsWindow* settingsWindow;

        Fl_Box* highScoresLabel;
        Fl_Button* evaluateButton;
        Fl_Button* resetButton;
        Fl_Button* pauseButton;
        Fl_Box* pausePuzzleOverlay;
        Fl_Box* puzzleNumberLabel;
        Fl_Box* gameTimerLabel;
        vector<Fl_Box*> highScoreLabels;

        string getPuzzleNumberOutput();
        void colorEvaluationPath();
        void refreshColors();
        void initialize();

    public:
        MainGameWindow(int width, int height, const char* title);
        virtual ~MainGameWindow();

        GameManager* getGameManager();

        void refreshBoard();
        void drawPuzzleNumberLabel();
        void addEvaluateButton();
        void addResetButton();
        void addPauseButton();
        void drawHighScoresLabel();

        void togglePuzzleOverlay(bool condition);
        void startGame();
        void stopGame();

        static void cbEvaluateButtonClicked(Fl_Widget*, void*);
        static void cbResetButtonClicked(Fl_Widget*, void*);
        static void cbOnWindowClose(Fl_Widget*, void*);
        static void cbPauseButtonClicked(Fl_Widget* widget, void* data);

        void startGameTimer();
        static void onTimerTick(void *data);

        void drawTimerLabel();

        void refreshTimerLabel();

        void updateHighScoreLabels();
};

}

#endif // MAINGAMEWINDOW_H
