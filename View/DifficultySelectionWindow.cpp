#include "DifficultySelectionWindow.h"

namespace view
{

DifficultySelectionWindow::DifficultySelectionWindow() : Fl_Window(220, 90, "Difficulty Selection")
{
    this->difficultyChoice = new Fl_Choice(115, 5, 100, 30, "Difficulty");
    this->okButton = new Fl_Button(40, 50, 70, 30, "OK");
    this->cancelButton = new Fl_Button(120, 50, 70, 30, "Cancel");

    this->okButton->callback(cbOk, this);
    this->cancelButton->callback(cbCancel, this);

    this->addDifficultyOptions();

    this->difficultyValue = Difficulty::EASY;
}

void DifficultySelectionWindow::addDifficultyOptions()
{
    this->difficultyChoice->add("Easy");
    this->difficultyChoice->add("Medium");
    this->difficultyChoice->add("Hard");
}

Difficulty DifficultySelectionWindow::getDifficultyValue()
{
    return this->difficultyValue;
}

void DifficultySelectionWindow::setDifficultyValue(Difficulty selection)
{
    this->difficultyValue = selection;
}

void DifficultySelectionWindow::cbOk(Fl_Widget* widget, void* data)
{
    DifficultySelectionWindow* window = (DifficultySelectionWindow*)data;
    window->okHandler();
}

void DifficultySelectionWindow::cbCancel(Fl_Widget* widget, void* data)
{
    DifficultySelectionWindow* window = (DifficultySelectionWindow*)data;
    window->cancelHandler();
}

void DifficultySelectionWindow::okHandler()
{
    if (difficultyChoice->value() == 0)
    {
        this->difficultyValue = Difficulty::EASY;
        this->hide();
    }
    else if (difficultyChoice->value() == 1)
    {
        this->difficultyValue = Difficulty::MEDIUM;
        this->hide();
    }
    else if (difficultyChoice->value() == 2)
    {
        this->difficultyValue = Difficulty::HARD;
        this->hide();
    }
    else
    {
        fl_message("Please select a difficulty.");
    }
}

void DifficultySelectionWindow::cancelHandler()
{
    this->hide();
}

DifficultySelectionWindow::~DifficultySelectionWindow()
{
    delete this->okButton;
    delete this->cancelButton;
    delete this->difficultyChoice;
}

}
