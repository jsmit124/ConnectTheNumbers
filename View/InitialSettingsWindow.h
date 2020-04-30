#ifndef INITIALSETTINGSWINDOW_H
#define INITIALSETTINGSWINDOW_H

#include "Utils.h"
#include "Difficulty.h"

#include <Fl/Fl_Input.H>
#include <Fl/Fl_Window.H>
#include <Fl/Fl_Button.H>
#include <Fl/fl_ask.H>
#include <stdlib.h>
#include <sstream>
#include <iostream>
using namespace std;

namespace view
{

class InitialSettingsWindow : public Fl_Window
{
    public:
        enum WindowResult {START, CLOSE, NONE};

        InitialSettingsWindow();
        virtual ~InitialSettingsWindow();

        void startHandler();
        void closeHandler();

        InitialSettingsWindow::WindowResult setWindowResult(InitialSettingsWindow::WindowResult);
        InitialSettingsWindow::WindowResult getWindowResult(InitialSettingsWindow::WindowResult);

        Fl_Color getSelectedButtonColor();
        Fl_Color getSelectedBackgroundColor();
        Difficulty getSelectedDifficulty();

    private:
        Fl_Button* startButton;
        Fl_Button* closeButton;

        Fl_Button* chooseButtonColorButton;
        Fl_Button* chooseBackgroundColorButton;
        Fl_Button* chooseDifficultyButton;

        Difficulty chosenDifficulty;
        Fl_Color chosenButtonColor;
        Fl_Color chosenBackgroundColor;
        int value;

        WindowResult buttonInvoked;

        void setStartButtonLocation(int, int);
        void setCloseButtonLocation(int, int);
        void setButtonColorButtonLocation(int, int);
        void setBackgroundColorButtonLocation(int, int);
        void setDifficultySelectionButtonLocation(int, int);

        static void cbStart(Fl_Widget*, void*);
        static void cbClose(Fl_Widget*, void*);
        static void cbButtonColorButtonClick(Fl_Widget*, void*);
        static void cbBackgroundColorButtonClick(Fl_Widget*, void*);
        static void cbDifficultyButtonClick(Fl_Widget*, void*);
};

}

#endif // INITIALSETTINGSWINDOW_H
