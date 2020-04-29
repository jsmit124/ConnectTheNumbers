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

class ButtonValueWindow : public Fl_Window
{
    public:
        enum WindowResult {OK, CANCEL, NONE};
        ButtonValueWindow();
        virtual ~ButtonValueWindow();
        void okHandler();
        void cancelHandler();
        int getValue() const;
        ButtonValueWindow::WindowResult setWindowResult(ButtonValueWindow::WindowResult);
        ButtonValueWindow::WindowResult getWindowResult(ButtonValueWindow::WindowResult);

    private:
        Fl_Button* okButton;
        Fl_Button* cancelButton;
        Fl_Input* valueInput;
        WindowResult buttonInvoked;
        int value;
        void setOKLocation(int, int);
        void setCancelLocation(int, int);
        static void cbOk(Fl_Widget*, void*);
        static void cbCancel(Fl_Widget*, void*);

        int determineIfValidValueEntered();
};

}

#endif // BUTTONVALUEWINDOW_H
