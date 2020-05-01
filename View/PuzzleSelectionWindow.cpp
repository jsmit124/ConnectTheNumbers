#include "PuzzleSelectionWindow.h"

#include <iostream>
using namespace std;

PuzzleSelectionWindow::PuzzleSelectionWindow() : Fl_Window(220, 90, "Puzzle Selection")
{
    this->puzzleSelectionChoice = new Fl_Choice(0, 0, 100, 30, "Puzzle Number");
    this->okButton = new Fl_Button(0, 0, 70, 30, "OK");
    this->cancelButton = new Fl_Button(0, 0, 70, 30, "Cancel");

    this->okButton->callback(cbOk, this);
    this->cancelButton->callback(cbCancel, this);

    this->setCancelButtonLocation(120, 50);
    this->setOkButtonLocation(40, 50);
    this->setPuzzleSelectionLocation(115, 5);

    this->addSelectionOptions();

    this->puzzleSelectionValue = 0;
}

void PuzzleSelectionWindow::addSelectionOptions()
{
    for (int i = 1; i <= 12; i++)
    {
        this->puzzleSelectionChoice->add(("Puzzle " + to_string(i)).c_str());
    }
}

int PuzzleSelectionWindow::getPuzzleSelectionValue()
{
    return this->puzzleSelectionValue;
}

void PuzzleSelectionWindow::setPuzzleSelectionValue(int puzzleNumber)
{
    this->puzzleSelectionValue = puzzleNumber;
}

void PuzzleSelectionWindow::setPuzzleSelectionLocation(int x, int y)
{
    this->puzzleSelectionChoice->position(x, y);
}

void PuzzleSelectionWindow::setOkButtonLocation(int x, int y)
{
    this->okButton->position(x, y);
}

void PuzzleSelectionWindow::setCancelButtonLocation(int x, int y)
{
    this->cancelButton->position(x, y);
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

PuzzleSelectionWindow::~PuzzleSelectionWindow()
{
    delete this->okButton;
    delete this->cancelButton;
    delete this->puzzleSelectionChoice;
}
