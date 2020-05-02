#include "PuzzleGridButton.h"

namespace view
{

/// Instantiates a new PuzzleGridButton
//
// @pre none
// @post this->ID EQUALS inputID
//
// @param x the x location for the button
// @param y the y location for the button
// @param width the width of the button
// @param height the height of the button
// @param inputID the ID of the button
//
PuzzleGridButton::PuzzleGridButton(int x, int y, int width, int height, int inputID) : Fl_Button(x, y, width, height)
{
    this->ID = inputID;
}

/// Returns the ID of the puzzle button
//
// @pre none
// @post none
//
// @return this->ID
//
int PuzzleGridButton::getID()
{
    return this->ID;
}

/// Sets the colors of the button
//
// @pre none
// @post this->labelcolor EQUALS label AND this->color EQUALS background
//
// @param background the background color to be set
// @param label the label color to be set
//
void PuzzleGridButton::setColors(Fl_Color* background, Fl_Color* label)
{
    this->labelcolor(*label);
    this->color(*background);
    this->redraw();
}

/// Destructs the PuzzleGridButton and frees memory allocated to it
//
PuzzleGridButton::~PuzzleGridButton()
{
}

}
