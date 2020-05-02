#include "InitialSettingsWindow.h"

namespace view
{

/// Instantiates a new InitialSettingsWindow window for taking user input
//
// @pre none
// @post none
//
InitialSettingsWindow::InitialSettingsWindow() : Fl_Window(250, 350, "Connect the Numbers")
{
    begin();

    this->drawAllButtons();
    this->setCallbacks();
    this->setDefaultValues();
    this->setColorScheme();

    end();
}

/// Handles functionality for the start button click event
//
// @pre none
// @post none
//
void InitialSettingsWindow::startHandler()
{
    this->hide();
}

/// Handles functionality for the close button click event
//
// @pre none
// @post none
//
void InitialSettingsWindow::closeHandler()
{
    exit(EXIT_FAILURE);
}

/// Returns the button color selected by the user
//
// @pre none
// @post none
//
// @return this->chosenButtonColor
//
Fl_Color InitialSettingsWindow::getSelectedButtonColor()
{
    return this->chosenButtonColor;
}

/// Returns the boolean value for whether or not to load a saved puzzle
//
// @pre none
// @post none
//
// @return true if program should load the saved puzzle;
//      false otherwise
//
bool InitialSettingsWindow::getLoadSavedPuzzle()
{
    return this->loadSavedPuzzle;
}

/// Returns the background color selected by the user
//
// @pre none
// @post none
//
// @return this->chosenBackgroundColor
//
Fl_Color InitialSettingsWindow::getSelectedBackgroundColor()
{
    return this->chosenBackgroundColor;
}

/// Returns the difficulty setting selected by the user
//
// @pre none
// @post none
//
// @return this->chosenDifficulty
//
Difficulty InitialSettingsWindow::getSelectedDifficulty()
{
    return this->chosenDifficulty;
}

/// Returns the puzzle number selected by the user
//
// @pre none
// @post none
//
// @return this->chosenPuzzleNumber
//
int InitialSettingsWindow::getSelectedPuzzle()
{
    return this->chosenPuzzleNumber;
}

/// Returns the text color selected by the user
//
// @pre none
// @post none
//
// @return this->chosenTextColor
//
Fl_Color InitialSettingsWindow::getSelectedTextColor()
{
    return this->chosenTextColor;
}

/// Sets the boolean value for whether or not to load the saved puzzle
//
// @pre none
// @post this->loadSavedPuzzle EQUALS condition
//
// @param condition true if program should load the saved puzzle;
//      false otherwise
//
void InitialSettingsWindow::setLoadSavedPuzzle(bool condition)
{
    this->loadSavedPuzzle = condition;
}

/// Sets the saved button state
//
// @pre none
// @post this->lastSaveButton is activated if condition EQUALS true
//      otherwise, this->lastSaveButton is deactivated
//
// @param condition true if the button should be activated
//      false otherwise
//
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

/// Sets the button color and applies it to all buttons on the window
//
// @pre none
// @post this->chosenButtonColor EQUALS color
//
// @param color the color value selected by the user
//
void InitialSettingsWindow::setButtonColor(Fl_Color color)
{
    this->chosenButtonColor = color;
    this->setColorToAllButtons(color);
}

/// Sets the background color and applies it to the window
//
// @pre none
// @post this->chosenBackgroundColor EQUALS color
//
// @param color the color value selected by the user
//
void InitialSettingsWindow::setBackgroundColor(Fl_Color color)
{
    this->chosenBackgroundColor = color;
    this->color(color);
    this->redraw();
}

/// Sets the difficulty setting selected by the user
//
// @pre none
// @post this->chosenDifficulty EQUALS selection
//
// @param selection the difficulty setting selected by the user
//
void InitialSettingsWindow::setDifficulty(Difficulty selection)
{
    this->chosenDifficulty = selection;
}

/// Sets the puzzle number selected by the user
//
// @pre none
// @post this->loadSavedPuzzle EQUALS false
//      AND this->chosenPuzzleNumber EQUALS puzzleNumber
//
// @param puzzleNumber the puzzle number selected by the user
//
void InitialSettingsWindow::setSelectedPuzzle(int puzzleNumber)
{
    this->loadSavedPuzzle = false;
    this->chosenPuzzleNumber = puzzleNumber;
}

/// Sets the text color selected by the user
//
// @pre none
// @post this->chosenTextColor EQUALS color
//
// @param color the color selected by the user
//
void InitialSettingsWindow::setTextColor(Fl_Color color)
{
    this->chosenTextColor = color;
    this->setTextColorToAllButtons(color);
}

/// Applies the input color value to all the buttons in the window
//
// @pre none
// @post all buttons color (property) EQUALS color (param)
//
// @param color the color to apply to all buttons in the window
//
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

    this->redrawButtons();
}

/// Applys the text color to all buttons in the window
//
// @pre none
// @post all buttons labelcolor (property) EQUALS color (param)
//
// @param color the color to apply to all buttons labelcolor property
//
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

    this->redrawButtons();
}

void InitialSettingsWindow::drawAllButtons()
{
    this->lastSaveButton = new Fl_Button(25, 25, 200, 30, "Continue game");
    this->startButton = new Fl_Button(25, 65, 200, 30, "Start");
    this->chooseLevelButton = new Fl_Button(25, 105, 200, 30, "Select Puzzle");
    this->chooseDifficultyButton = new Fl_Button(25, 145, 200, 30, "Choose difficulty");
    this->chooseBackgroundColorButton = new Fl_Button(25, 185, 200, 30, "Choose background color");
    this->chooseButtonColorButton = new Fl_Button(25, 225, 200, 30, "Choose button color");
    this->chooseTextColorButton = new Fl_Button(25, 265, 200, 30, "Choose text color");
    this->closeButton = new Fl_Button(25, 305, 200, 30, "Close");
}

void InitialSettingsWindow::setCallbacks()
{
    this->startButton->callback(cbStart, this);
    this->closeButton->callback(cbClose, this);
    this->chooseButtonColorButton->callback(cbButtonColorButtonClick, this);
    this->chooseBackgroundColorButton->callback(cbBackgroundColorButtonClick, this);
    this->chooseDifficultyButton->callback(cbDifficultyButtonClick, this);
    this->lastSaveButton->callback(cbLoadSave, this);
    this->chooseLevelButton->callback(cbSelectPuzzle, this);
    this->chooseTextColorButton->callback(cbChooseTextColor, this);
    this->callback(InitialSettingsWindow::cbOnWindowClose, this);
}

void InitialSettingsWindow::setDefaultValues()
{
    this->chosenButtonColor = FL_DARK3;
    this->chosenTextColor = FL_WHITE;
    this->chosenDifficulty = Difficulty::EASY;
    this->chosenPuzzleNumber = 0;
    this->loadSavedPuzzle = false;
    this->value = 0;
}

void InitialSettingsWindow::setColorScheme()
{
    this->color(this->chosenBackgroundColor);
    this->setColorToAllButtons(this->chosenButtonColor);
    this->setTextColorToAllButtons(this->chosenTextColor);
}

void InitialSettingsWindow::redrawButtons()
{
    this->startButton->redraw();
    this->closeButton->redraw();
    this->chooseButtonColorButton->redraw();
    this->chooseBackgroundColorButton->redraw();
    this->chooseDifficultyButton->redraw();
    this->lastSaveButton->redraw();
    this->chooseLevelButton->redraw();
    this->chooseTextColorButton->redraw();
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

    if (colorWindow.getColor() != 0)
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

    if (colorWindow.getColor() != 0)
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

    if (colorWindow.getColor() != 0)
    {
        window->setTextColor(colorWindow.getColor());
    }
}

void InitialSettingsWindow::cbOnWindowClose(Fl_Widget *, void *data)
{
    auto *window = (InitialSettingsWindow*) data;
    window->closeHandler();
}

/// Deconstructs the window and frees up all memory allocated to the window
//
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
