#include "PuzzleSelectionWindow.h"

#include <iostream>
using namespace std;

namespace view
{

/// Instantiates a new PuzzleSelectionWindow window
//
// @pre none
// @post this->puzzleSelectionValue EQUALS 0
//
PuzzleSelectionWindow::PuzzleSelectionWindow() : Fl_Window(220, 90, "Puzzle Selection")
{
    this->addButtonsToWindow();
    this->setCallbacksForButtons();

    this->addSelectionOptions();

    this->puzzleSelectionValue = 0;
}

/// Returns the puzzle selection value selected by the user
//
// @pre none
// @post none
//
// @return this->puzzleSelectionValue
//
int PuzzleSelectionWindow::getPuzzleSelectionValue()
{
    return this->puzzleSelectionValue;
}

/// Sets the puzzleSelectionValue to the puzzleNumber
//
// @pre none
// @post this->puzzleSelectionValue EQUALS puzzleNumber
//
// @param puzzleNumber the puzzle number selected by the user
//
void PuzzleSelectionWindow::setPuzzleSelectionValue(int puzzleNumber)
{
    this->puzzleSelectionValue = puzzleNumber;
}

void PuzzleSelectionWindow::addButtonsToWindow()
{
    this->puzzleSelectionChoice = new Fl_Choice(115, 5, 100, 30, "Puzzle Number");
    this->okButton = new Fl_Button(40, 50, 70, 30, "OK");
    this->cancelButton = new Fl_Button(120, 50, 70, 30, "Cancel");
}

void PuzzleSelectionWindow::setCallbacksForButtons()
{
    this->okButton->callback(cbOk, this);
    this->cancelButton->callback(cbCancel, this);
}

void PuzzleSelectionWindow::addSelectionOptions()
{
    for (int i = 1; i <= 12; i++)
    {
        this->puzzleSelectionChoice->add(("Puzzle " + to_string(i)).c_str());
    }
}

void PuzzleSelectionWindow::cbOk(Fl_Widget* widget, void* data)
{
    PuzzleSelectionWindow* window = (PuzzleSelectionWindow*)data;
    window->okHandler();
}

void PuzzleSelectionWindow::cbCancel(Fl_Widget* widget, void* data)
{
    PuzzleSelectionWindow* window = (PuzzleSelectionWindow*)data;
    window->cancelHandler();
}

void PuzzleSelectionWindow::okHandler()
{
    if (puzzleSelectionChoice->value() >= 0)
    {
        this->puzzleSelectionValue = this->puzzleSelectionChoice->value() + 1;
        this->hide();
    }
    else
    {
        fl_message("Please select a puzzle.");
    }
}

void PuzzleSelectionWindow::cancelHandler()
{
    this->hide();
}

/// Destructs the window and free up all memory allocated to it
//
PuzzleSelectionWindow::~PuzzleSelectionWindow()
{
    delete this->okButton;
    delete this->cancelButton;
    delete this->puzzleSelectionChoice;
}

}
