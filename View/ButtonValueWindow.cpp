#include "ButtonValueWindow.h"

namespace view
{

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

void ButtonValueWindow::cancelHandler()
{
    this->hide();
}

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

ButtonValueWindow::~ButtonValueWindow()
{
    delete this->okButton;
    delete this->cancelButton;
    delete this->valueInput;
}

}
