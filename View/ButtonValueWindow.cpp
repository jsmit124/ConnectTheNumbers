#include "ButtonValueWindow.h"

namespace view
{

ButtonValueWindow::ButtonValueWindow() : Fl_Window(175, 100, "Value to set")
{
    this->buttonInvoked = WindowResult::NONE;

    begin();

    this->value = 0;

    this->valueInput = new Fl_Input(80, 10, 60, 25, "Value:");

    this->okButton = new Fl_Button(0,0,70, 30, "OK");
    this->cancelButton = new Fl_Button(0,0,70,30, "Cancel");

    this->setOKLocation(15, 50);
    this->setCancelLocation(90,50);

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

void ButtonValueWindow::setOKLocation(int x, int y)
{
    this->okButton->position(x, y);
}

void ButtonValueWindow::setCancelLocation(int x, int y)
{
    this->cancelButton->position(x, y);
}

void ButtonValueWindow::cbOk(Fl_Widget* widget, void* data)
{
    ButtonValueWindow* window = (ButtonValueWindow*)data;
    window->setWindowResult(ButtonValueWindow::OK);
    window->okHandler();
}

void ButtonValueWindow::cbCancel(Fl_Widget* widget, void* data)
{
    ButtonValueWindow* window = (ButtonValueWindow*)data;
    window->setWindowResult(ButtonValueWindow::CANCEL);
    window->cancelHandler();
}

int ButtonValueWindow::determineIfValidValueEntered()
{
    string value = this->valueInput->value();
    int intValue = toInt(value, "Error converting value to an integer.");

    if (intValue <= 0 || intValue > 64)
    {
        throw "Please enter a value between 1 and 64.";
    }

    return intValue;
}

ButtonValueWindow::WindowResult ButtonValueWindow::setWindowResult(ButtonValueWindow::WindowResult result)
{
    this->buttonInvoked = result;
}

ButtonValueWindow::WindowResult ButtonValueWindow::getWindowResult(ButtonValueWindow::WindowResult)
{
    return this->buttonInvoked;
}

ButtonValueWindow::~ButtonValueWindow()
{
    delete this->okButton;
    delete this->cancelButton;
}

}
