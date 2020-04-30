#include "PlayerSettings.h"

namespace settings
{

/// Instantiates a new PlayerSettings object with default values
//
// @pre this->buttonColor = FL_DARK3
//      AND this->backgroundColor = FL_DARK_BLUE
//      AND this->chosenDifficulty = Difficulty::EASY
PlayerSettings::PlayerSettings()
{
    this->backgroundColor = FL_DARK_BLUE;
    this->buttonColor = FL_DARK3;
    this->chosenDifficulty = Difficulty::EASY;
}

PlayerSettings::~PlayerSettings()
{
        //ctor
}

/// Sets the desired button color
//
// @param color the color to be set as the button color
//
void PlayerSettings::setButtonColor(Fl_Color color)
{
    this->buttonColor = color;
}

/// Sets the desired background color
//
// @param color the color to be set as the background color
//
void PlayerSettings::setBackgroundColor(Fl_Color color)
{
    this->backgroundColor = color;
}

/// Returns the Fl_Color chosen to be the button color
//
//  @return this->buttonColor
//
Fl_Color PlayerSettings::getButtonColor()
{
    return this->buttonColor;
}

/// Returns the Fl_Color chosen to be the background color
//
// @return this->backgroundColor
//
Fl_Color PlayerSettings::getBackgroundColor()
{
    return this->backgroundColor;
}

}
