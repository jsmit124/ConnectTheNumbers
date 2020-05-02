#ifndef BUTTONVALUEWINDOW_H
#define BUTTONVALUEWINDOW_H

#include "Utils.h"

#include <Fl/Fl_Input.H>
#include <Fl/Fl_Window.H>
#include <Fl/Fl_Button.H>
#include <Fl/fl_ask.H>
#include <sstream>
using namespace std;

namespace view
{

/// UI Window for taking user input through Fl_Input textbox
//
class ButtonValueWindow : public Fl_Window
{
    public:
        ButtonValueWindow(int min = 1, int max = 64);
        virtual ~ButtonValueWindow();

        void okHandler();
        void cancelHandler();

        int getValue() const;

    private:
        Fl_Button* okButton;
        Fl_Button* cancelButton;
        Fl_Input* valueInput;

        int minimumNumber;
        int maximumNumber;
        int value;

        static void cbOk(Fl_Widget*, void*);
        static void cbCancel(Fl_Widget*, void*);

        int determineIfValidValueEntered();
};

}

#endif // BUTTONVALUEWINDOW_H
