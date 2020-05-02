#ifndef INITIALSETTINGSWINDOW_H
#define INITIALSETTINGSWINDOW_H

#include "Utils.h"
#include "../Enum/Difficulty.h"

#include "../Controller/GameManager.h"
using namespace controller;

#include "ColorSelectionWindow.h"
#include "ButtonValueWindow.h"
#include "PuzzleSelectionWindow.h"
#include "DifficultySelectionWindow.h"
using namespace view;

#include <Fl/Fl_Input.H>
#include <Fl/Fl_Window.H>
#include <Fl/Fl_Button.H>
#include <Fl/fl_ask.H>
#include <cstdlib>
#include <Fl/Fl.H>
#include <stdlib.h>
#include <sstream>
using namespace std;

namespace view
{

/// Handles implementation of the InitialSettingsWindow UI window
//
class InitialSettingsWindow : public Fl_Window
{
    public:
        InitialSettingsWindow();
        virtual ~InitialSettingsWindow();

        void startHandler();
        void closeHandler();

        Fl_Color getSelectedButtonColor();
        Fl_Color getSelectedBackgroundColor();
        Difficulty getSelectedDifficulty();
        bool getLoadSavedPuzzle();
        int getSelectedPuzzle();
        Fl_Color getSelectedTextColor();

        void setLoadSavedPuzzle(bool);
        void setSavedButtonState(bool);
        void setButtonColor(Fl_Color);
        void setBackgroundColor(Fl_Color);
        void setDifficulty(Difficulty);
        void setSelectedPuzzle(int);
        void setTextColor(Fl_Color);

        void setColorToAllButtons(Fl_Color);
        void setTextColorToAllButtons(Fl_Color);

    private:
        static const int MAX_PUZZLE_COUNT = 12;

        Fl_Button* startButton;
        Fl_Button* closeButton;
        Fl_Button* chooseButtonColorButton;
        Fl_Button* chooseBackgroundColorButton;
        Fl_Button* chooseDifficultyButton;
        Fl_Button* lastSaveButton;
        Fl_Button* chooseLevelButton;
        Fl_Button* chooseTextColorButton;

        Difficulty chosenDifficulty;
        Fl_Color chosenButtonColor;
        Fl_Color chosenBackgroundColor;
        Fl_Color chosenTextColor;
        int chosenPuzzleNumber;
        int value;
        bool loadSavedPuzzle;

        static void cbStart(Fl_Widget*, void*);
        static void cbClose(Fl_Widget*, void*);
        static void cbButtonColorButtonClick(Fl_Widget*, void*);
        static void cbBackgroundColorButtonClick(Fl_Widget*, void*);
        static void cbDifficultyButtonClick(Fl_Widget*, void*);
        static void cbLoadSave(Fl_Widget*, void*);
        static void cbSelectPuzzle(Fl_Widget*, void*);
        static void cbChooseTextColor(Fl_Widget*, void*);
        static void cbOnWindowClose(Fl_Widget*, void *);

        void drawAllButtons();
        void setCallbacks();
        void setDefaultValues();
        void setColorScheme();
        void redrawButtons();
};

}

#endif // INITIALSETTINGSWINDOW_H
