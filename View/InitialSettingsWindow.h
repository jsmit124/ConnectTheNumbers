#ifndef INITIALSETTINGSWINDOW_H
#define INITIALSETTINGSWINDOW_H

#include "Utils.h"
#include "../Enum/Difficulty.h"

#include "../Controller/GameManager.h"
using namespace controller;

#include "ColorSelectionWindow.h"
#include "ButtonValueWindow.h"
using namespace view;

#include <Fl/Fl_Input.H>
#include <Fl/Fl_Window.H>
#include <Fl/Fl_Button.H>
#include <Fl/fl_ask.H>
#include <cstdlib>
#include <Fl/Fl.H>
#include <stdlib.h>
#include <sstream>
#include <iostream>
using namespace std;

namespace view
{

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

        void setLoadSavedPuzzle(bool condition);
        void setSavedButtonState(bool condition);
        void setButtonColor(Fl_Color color);
        void setBackgroundColor(Fl_Color color);
        void setDifficulty(Difficulty selection);
        void setSelectedPuzzle(int puzzleNumber);
        void setTextColor(Fl_Color color);

        void setColorToAllButtons(Fl_Color color);
        void setTextColorToAllButtons(Fl_Color color);

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

        void setStartButtonLocation(int, int);
        void setCloseButtonLocation(int, int);
        void setLastSavedButtonLocation(int, int);
        void setButtonColorButtonLocation(int, int);
        void setBackgroundColorButtonLocation(int, int);
        void setDifficultySelectionButtonLocation(int, int);
        void setChoosePuzzleButtonLocation(int, int);
        void setChooseTextColorButtonLocation(int, int);

        static void cbStart(Fl_Widget*, void*);
        static void cbClose(Fl_Widget*, void*);
        static void cbButtonColorButtonClick(Fl_Widget*, void*);
        static void cbBackgroundColorButtonClick(Fl_Widget*, void*);
        static void cbDifficultyButtonClick(Fl_Widget*, void*);
        static void cbLoadSave(Fl_Widget*, void*);
        static void cbSelectPuzzle(Fl_Widget*, void*);
        static void cbChooseTextColor(Fl_Widget*, void*);
};

}

#endif // INITIALSETTINGSWINDOW_H
