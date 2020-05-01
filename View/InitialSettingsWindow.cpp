#include "InitialSettingsWindow.h"

namespace view
{

InitialSettingsWindow::InitialSettingsWindow() : Fl_Window(250, 350, "Connect the Numbers")
{
    begin();

    this->value = 0;

    this->lastSaveButton = new Fl_Button(25, 25, 200, 30, "Continue game");
    this->startButton = new Fl_Button(25, 65, 200, 30, "Start");
    this->chooseLevelButton = new Fl_Button(25, 105, 200, 30, "Select Puzzle");
    this->chooseDifficultyButton = new Fl_Button(25, 145, 200, 30, "Choose difficulty");
    this->chooseBackgroundColorButton = new Fl_Button(25, 185, 200, 30, "Choose background color");
    this->chooseButtonColorButton = new Fl_Button(25, 225, 200, 30, "Choose button color");
    this->chooseTextColorButton = new Fl_Button(25, 265, 200, 30, "Choose text color");
    this->closeButton = new Fl_Button(25, 305, 200, 30, "Close");

    this->startButton->callback(cbStart, this);
    this->closeButton->callback(cbClose, this);
    this->chooseButtonColorButton->callback(cbButtonColorButtonClick, this);
    this->chooseBackgroundColorButton->callback(cbBackgroundColorButtonClick, this);
    this->chooseDifficultyButton->callback(cbDifficultyButtonClick, this);
    this->lastSaveButton->callback(cbLoadSave, this);
    this->chooseLevelButton->callback(cbSelectPuzzle, this);
    this->chooseTextColorButton->callback(cbChooseTextColor, this);

    this->chosenBackgroundColor = fl_darker(fl_darker(fl_darker(FL_DARK_BLUE)));
    this->chosenButtonColor = FL_DARK3;
    this->chosenTextColor = FL_WHITE;
    this->chosenDifficulty = Difficulty::EASY;
    this->chosenPuzzleNumber = 0;
    this->loadSavedPuzzle = false;

    this->color(this->chosenBackgroundColor);
    this->setColorToAllButtons(this->chosenButtonColor);
    this->setTextColorToAllButtons(this->chosenTextColor);

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
    this->chooseLevelButton->color(color);
    this->chooseTextColorButton->color(color);

    this->startButton->redraw();
    this->closeButton->redraw();
    this->chooseButtonColorButton->redraw();
    this->chooseBackgroundColorButton->redraw();
    this->chooseDifficultyButton->redraw();
    this->lastSaveButton->redraw();
    this->chooseLevelButton->redraw();
    this->chooseTextColorButton->redraw();
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

void InitialSettingsWindow::setTextColor(Fl_Color color)
{
    this->chosenTextColor = color;
    this->setTextColorToAllButtons(color);
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

void InitialSettingsWindow::setSelectedPuzzle(int puzzleNumber)
{
    this->loadSavedPuzzle = false;
    this->chosenPuzzleNumber = puzzleNumber;
}

void InitialSettingsWindow::cbStart(Fl_Widget* widget, void* data)
{
    InitialSettingsWindow* window = (InitialSettingsWindow*)data;
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

    DifficultySelectionWindow difficultyWindow;
    difficultyWindow.set_modal();
    difficultyWindow.show();

    while (difficultyWindow.shown())
    {
        Fl::wait();
    }

    if (difficultyWindow.getDifficultyValue() >= 0)
    {
        window->setDifficulty(difficultyWindow.getDifficultyValue());
    }
}

void InitialSettingsWindow::cbSelectPuzzle(Fl_Widget* widget, void* data)
{
    InitialSettingsWindow* window = (InitialSettingsWindow*)data;

    PuzzleSelectionWindow puzzleSelector;
    puzzleSelector.set_modal();
    puzzleSelector.show();
    while (puzzleSelector.shown())
    {
        Fl::wait();
    }

    window->setSelectedPuzzle(puzzleSelector.getPuzzleSelectionValue());

}

void InitialSettingsWindow::cbChooseTextColor(Fl_Widget* widget, void* data)
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
        window->setTextColor(colorWindow.getColor());
    }
}

void InitialSettingsWindow::setTextColorToAllButtons(Fl_Color color)
{
    this->startButton->labelcolor(color);
    this->closeButton->labelcolor(color);
    this->chooseButtonColorButton->labelcolor(color);
    this->chooseBackgroundColorButton->labelcolor(color);
    this->chooseDifficultyButton->labelcolor(color);
    this->lastSaveButton->labelcolor(color);
    this->chooseLevelButton->labelcolor(color);
    this->chooseTextColorButton->labelcolor(color);

    this->startButton->redraw();
    this->closeButton->redraw();
    this->chooseButtonColorButton->redraw();
    this->chooseBackgroundColorButton->redraw();
    this->chooseDifficultyButton->redraw();
    this->lastSaveButton->redraw();
    this->chooseLevelButton->redraw();
    this->chooseTextColorButton->redraw();
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

int InitialSettingsWindow::getSelectedPuzzle()
{
    return this->chosenPuzzleNumber;
}

Fl_Color InitialSettingsWindow::getSelectedTextColor()
{
    return this->chosenTextColor;
}

InitialSettingsWindow::~InitialSettingsWindow()
{
    delete this->startButton;
    delete this->closeButton;
    delete this->chooseButtonColorButton;
    delete this->chooseBackgroundColorButton;
    delete this->chooseDifficultyButton;
    delete this->lastSaveButton;
    delete this->chooseLevelButton;
    delete this->chooseTextColorButton;
}

}
