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
    this->lastSaveButton = new Fl_Button(0, 0, 200, 30, "Load Saved Puzzle");

    this->setStartButtonLocation(25, 65);
    this->setCloseButtonLocation(25, 225);
    this->setButtonColorButtonLocation(25, 185);
    this->setBackgroundColorButtonLocation(25, 145);
    this->setDifficultySelectionButtonLocation(25, 105);
    this->setLastSavedButtonLocation(25, 25);

    this->startButton->callback(cbStart, this);
    this->closeButton->callback(cbClose, this);
    this->chooseButtonColorButton->callback(cbButtonColorButtonClick, this);
    this->chooseBackgroundColorButton->callback(cbBackgroundColorButtonClick, this);
    this->chooseDifficultyButton->callback(cbDifficultyButtonClick, this);
    this->lastSaveButton->callback(cbLoadSave, this);

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

void InitialSettingsWindow::setLastSavedButtonLocation(int x, int y)
{
    this->lastSaveButton->position(x, y);
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
    this->setColorToAllButtons(color);

}

void InitialSettingsWindow::setColorToAllButtons(Fl_Color color)
{
    this->startButton->color(color);
    this->closeButton->color(color);
    this->chooseButtonColorButton->color(color);
    this->chooseBackgroundColorButton->color(color);
    this->chooseDifficultyButton->color(color);
    this->lastSaveButton->color(color);

    this->startButton->redraw();
    this->closeButton->redraw();
    this->chooseButtonColorButton->redraw();
    this->chooseBackgroundColorButton->redraw();
    this->chooseDifficultyButton->redraw();
    this->lastSaveButton->redraw();
}

void InitialSettingsWindow::setBackgroundColor(Fl_Color color)
{
    this->chosenBackgroundColor = color;
    this->color(color);
    this->redraw();
}

void InitialSettingsWindow::setDifficulty(Difficulty selection)
{
    this->chosenDifficulty = selection;
}

void InitialSettingsWindow::setLoadSavedPuzzle(bool condition)
{
    this->loadSavedPuzzle = condition;
}

void InitialSettingsWindow::setSavedButtonState(bool condition)
{
    if (condition)
    {
        this->lastSaveButton->activate();
    }
    else
    {
        this->lastSaveButton->deactivate();
    }
}

void InitialSettingsWindow::cbStart(Fl_Widget* widget, void* data)
{
    InitialSettingsWindow* window = (InitialSettingsWindow*)data;
    window->setWindowResult(InitialSettingsWindow::START);
    window->startHandler();
}

void InitialSettingsWindow::cbLoadSave(Fl_Widget* widget, void* data)
{
    InitialSettingsWindow* window = (InitialSettingsWindow*)data;
    window->setLoadSavedPuzzle(true);
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

bool InitialSettingsWindow::getLoadSavedPuzzle()
{
    return this->loadSavedPuzzle;
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
