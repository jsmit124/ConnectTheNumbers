#include "ButtonValueWindow.h"

namespace view
{

/// Instantiates a new ButtonValueWindow
//
// @pre none
// @post this->minimumNumber EQUALS min AND this->maximumNumer EQUALS max
//
// @param min the maximum number that can be input
// @param max the minimum number that can be input
//
ButtonValueWindow::ButtonValueWindow(int min, int max) : Fl_Window(175, 100, "Value to set")
{
    begin();

    this->minimumNumber = min;
    this->maximumNumber = max;
    this->value = 0;

    this->valueInput = new Fl_Input(80, 10, 60, 25, "Value:");
    this->okButton = new Fl_Button(15, 50, 70, 30, "OK");
    this->cancelButton = new Fl_Button(90, 50, 70, 30, "Cancel");

    this->okButton->callback(cbOk, this);
    this->cancelButton->callback(cbCancel, this);
    this->valueInput->callback(cbOk, this);

    this->okButton->when(FL_WHEN_ENTER_KEY);

    end();
}

/// Handles the OK button click by verifying and setting user input to memory
//
// @pre none
// @post this->value EQUALS user input
//
void ButtonValueWindow::okHandler()
{
    try
    {
        this->value = this->determineIfValidValueEntered();
        this->hide();
    }
    catch (const char* message)
    {
        fl_message("%s", message);
    }
}

/// Handles the cancel button click event by hiding the current window
//
// @pre none
// @post none
//
void ButtonValueWindow::cancelHandler()
{
    this->hide();
}

/// Returns the value entered by the user into the text box
//
// @pre none
// @post none
//
// @return this->value
//
int ButtonValueWindow::getValue() const
{
    return this->value;
}

void ButtonValueWindow::cbOk(Fl_Widget* widget, void* data)
{
    ButtonValueWindow* window = (ButtonValueWindow*)data;
    window->okHandler();
}

void ButtonValueWindow::cbCancel(Fl_Widget* widget, void* data)
{
    ButtonValueWindow* window = (ButtonValueWindow*)data;
    window->cancelHandler();
}

int ButtonValueWindow::determineIfValidValueEntered()
{
    string value = this->valueInput->value();
    int intValue = toInt(value, "Error converting value to an integer.");

    if (intValue < this->minimumNumber || intValue > this->maximumNumber)
    {
        throw "Please enter a value between 1 and 64.";
    }

    return intValue;
}

/// Destructs the window and frees up all allocated memory
//
ButtonValueWindow::~ButtonValueWindow()
{
    delete this->okButton;
    delete this->cancelButton;
    delete this->valueInput;
}

}
