#ifndef MAINGAMEWINDOW_H
#define MAINGAMEWINDOW_H

#include "../Controller/GameManager.h"

#include "Messenger.h"
#include "PuzzleGrid.h"
#include "InitialSettingsWindow.h"
#include "HighScoresWindow.h"

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
#include <cstdlib>
using namespace std;

#include "../Settings/PlayerSettings.h"

using namespace settings;
using namespace controller;
using namespace std;

namespace view
{

/// Class manages the Main Game Window
//
class MainGameWindow : public Fl_Window
{

private:
    /// Members
    PuzzleGrid* puzzleGrid;
    GameManager* gameManager;
    InitialSettingsWindow* settingsWindow;
    HighScoresWindow* highScoresWindow;

    /// Fltk Controls
    Fl_Box* highScoresLabel;
    Fl_Button* evaluateButton;
    Fl_Button* resetButton;
    Fl_Button* pauseButton;
    Fl_Button* peekButton;
    Fl_Button* viewHighScoresButton;
    Fl_Box* pausePuzzleOverlay;
    Fl_Box* puzzleNumberLabel;
    Fl_Box* gameTimerLabel;

    /// Private Helpers
    string formatPuzzleNumberOutput();
    void setupMainWindowControls();
    void colorEvaluationPath();
    void colorPeekPath();
    void refreshColors();
    void initializeSettingsWindow();
    void initializeSettings();

    void addViewHighScoresButton();
    void addPuzzleOverlayBox();
    void addEvaluateButton();
    void addResetButton();
    void addPauseButton();
    void addPeekButton();

public:
    MainGameWindow(int width, int height, const char* title);
    virtual ~MainGameWindow();

    /// Getters
    HighScoresWindow* getHighScoresWindow();
    string getRandomEvaluationMessage();

    /// Game Update Events
    void startGame();
    void stopGame();
    void showRoundEndWindow();
    void showFinalRoundWindow();

    void refreshTimerLabel();
    void refreshBoard();

    void drawPuzzleNumberLabel();
    void drawTimerLabel();

    void handlePause();
    void handleGameFinished();
    void handleEvaluateCorrectly();

    /// Fltk ctrl callbacks
    static void cbEvaluateButtonClicked(Fl_Widget*, void*);
    static void cbResetButtonClicked(Fl_Widget*, void*);
    static void cbOnWindowClose(Fl_Widget*, void*);
    static void cbPauseButtonClicked(Fl_Widget* widget, void* data);
    static void cbViewHighScoresClicked(Fl_Widget *widget, void *data);
    static void cbPeekButtonClicked(Fl_Widget *widget, void *data);

    /// Events
    void startGameTimer();
    static void onTimerTick(void *data);
};

}

#endif // MAINGAMEWINDOW_H
