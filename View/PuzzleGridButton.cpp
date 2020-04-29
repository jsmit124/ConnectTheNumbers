#include "PuzzleGridButton.h"

namespace view
{

PuzzleGridButton::PuzzleGridButton(int x, int y, int width, int height, int inputID) : Fl_Button(x, y, width, height)
{
    this->ID = inputID;
}

int PuzzleGridButton::getID()
{
    return this->ID;
}

PuzzleGridButton::~PuzzleGridButton()
{

}

}
