#include "InitialSettingsWindow.h"

namespace view
{

InitialSettingsWindow::InitialSettingsWindow() : Fl_Window(250, 300, "Welcome to Connect the Numbers!")
{
    this->buttonInvoked = WindowResult::NONE;

    begin();

    this->value = 0;

    this->startButton = new Fl_Button(0, 0, 200, 30, "Start");
    this->closeButton = new Fl_Button(0, 0, 200, 30, "Close");
    this->chooseButtonColorButton = new Fl_Button(0, 0, 200, 30, "Choose button color");
    this->chooseBackgroundColorButton = new Fl_Button(0, 0, 200, 30, "Choose background color");
    this->chooseDifficultyButton = new Fl_Button(0, 0, 200, 30, "Choose difficulty");

    this->setStartButtonLocation(25, 25);
    this->setCloseButtonLocation(25,225);
    this->setButtonColorButtonLocation(25, 175);
    this->setBackgroundColorButtonLocation(25, 125);
    this->setDifficultySelectionButtonLocation(25, 75);

    this->startButton->callback(cbStart, this);
    this->closeButton->callback(cbClose, this);
    this->chooseButtonColorButton->callback(cbButtonColorButtonClick, this);
    this->chooseBackgroundColorButton->callback(cbBackgroundColorButtonClick, this);
    this->chooseDifficultyButton->callback(cbDifficultyButtonClick, this);

    this->chosenBackgroundColor = fl_darker(fl_darker(fl_darker(FL_DARK_BLUE)));
    this->chosenButtonColor = FL_DARK3;
    this->chosenDifficulty = Difficulty::EASY;

    end();
}

void InitialSettingsWindow::startHandler()
{
    this->hide();
}

void InitialSettingsWindow::closeHandler()
{
    exit(EXIT_FAILURE);
}

void InitialSettingsWindow::setStartButtonLocation(int x, int y)
{
    this->startButton->position(x, y);
}

void InitialSettingsWindow::setButtonColorButtonLocation(int x, int y)
{
    this->chooseButtonColorButton->position(x, y);
}

void InitialSettingsWindow::setBackgroundColorButtonLocation(int x, int y)
{
    this->chooseBackgroundColorButton->position(x, y);
}

void InitialSettingsWindow::setDifficultySelectionButtonLocation(int x, int y)
{
    this->chooseDifficultyButton->position(x, y);
}

void InitialSettingsWindow::setCloseButtonLocation(int x, int y)
{
    this->closeButton->position(x, y);
}

void InitialSettingsWindow::setButtonColor(Fl_Color color)
{
    this->chosenButtonColor = color;
}

void InitialSettingsWindow::setBackgroundColor(Fl_Color color)
{
    this->chosenBackgroundColor = color;
}

void InitialSettingsWindow::setDifficulty(Difficulty selection)
{
    this->chosenDifficulty = selection;
}

void InitialSettingsWindow::cbStart(Fl_Widget* widget, void* data)
{
    InitialSettingsWindow* window = (InitialSettingsWindow*)data;
    window->setWindowResult(InitialSettingsWindow::START);
    window->startHandler();
}

void InitialSettingsWindow::cbClose(Fl_Widget* widget, void* data)
{
    InitialSettingsWindow* window = (InitialSettingsWindow*)data;
    window->setWindowResult(InitialSettingsWindow::CLOSE);
    window->closeHandler();
}

void InitialSettingsWindow::cbButtonColorButtonClick(Fl_Widget* widget, void* data)
{
    InitialSettingsWindow* window = (InitialSettingsWindow*)data;

    ColorSelectionWindow colorWindow;
    colorWindow.set_modal();
    colorWindow.show();

    while (colorWindow.shown())
    {
        Fl::wait();
    }
    if (colorWindow.getColor() >= 0)
    {
        window->setButtonColor(colorWindow.getColor());
    }
}

void InitialSettingsWindow::cbBackgroundColorButtonClick(Fl_Widget* widget, void* data)
{
    InitialSettingsWindow* window = (InitialSettingsWindow*)data;

    ColorSelectionWindow colorWindow;
    colorWindow.set_modal();
    colorWindow.show();

    while (colorWindow.shown())
    {
        Fl::wait();
    }
    if (colorWindow.getColor() >= 0)
    {
        window->setBackgroundColor(colorWindow.getColor());
    }
}

void InitialSettingsWindow::cbDifficultyButtonClick(Fl_Widget* widget, void* data)
{
    InitialSettingsWindow* window = (InitialSettingsWindow*)data;
    cout << "Difficulty clicked" << endl;
}

Fl_Color InitialSettingsWindow::getSelectedButtonColor()
{
    return this->chosenButtonColor;
}

Fl_Color InitialSettingsWindow::getSelectedBackgroundColor()
{
    return this->chosenBackgroundColor;
}

Difficulty InitialSettingsWindow::getSelectedDifficulty()
{
    return this->chosenDifficulty;
}

InitialSettingsWindow::WindowResult InitialSettingsWindow::setWindowResult(InitialSettingsWindow::WindowResult result)
{
    this->buttonInvoked = result;
}

InitialSettingsWindow::WindowResult InitialSettingsWindow::getWindowResult(InitialSettingsWindow::WindowResult)
{
    return this->buttonInvoked;
}

InitialSettingsWindow::~InitialSettingsWindow()
{
    delete this->startButton;
    delete this->closeButton;
}

}
