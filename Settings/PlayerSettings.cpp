#include "PlayerSettings.h"

namespace settings
{

/// Instantiates a new PlayerSettings object with default values
//
PlayerSettings::PlayerSettings()
{
    this->backgroundColor = fl_darker(fl_darker(FL_DARK_YELLOW));
    this->buttonColor = FL_DARK3;
    this->textColor = FL_WHITE;
}

PlayerSettings::~PlayerSettings()
{
    //dtor
}

/// Sets the desired button color
//
// @param color the color to be set as the button color
//
void PlayerSettings::setButtonColor(Fl_Color color)
{
    this->buttonColor = color;
}

void PlayerSettings::setTextColor(Fl_Color color)
{
    this->textColor = color;
}

/// Sets the desired background color
//
// @param color the color to be set as the background color
//
void PlayerSettings::setBackgroundColor(Fl_Color color)
{
    this->backgroundColor = color;
}

void PlayerSettings::setDifficulty(Difficulty selection)
{
    this->chosenDifficulty = selection;
}

void PlayerSettings::setLastSavedDifficulty(Difficulty difficulty)
{
    this->lastSavedDifficulty = difficulty;
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

Fl_Color PlayerSettings::getTextColor()
{
    return this->textColor;
}

Difficulty PlayerSettings::getDifficulty()
{
    return this->chosenDifficulty;
}

Difficulty PlayerSettings::getLastSavedDifficulty()
{
    return this->lastSavedDifficulty;
}

void PlayerSettings::moveToNextDifficulty()
{
    switch (this->chosenDifficulty)
    {
        case EASY:
            this->chosenDifficulty = MEDIUM;
            break;
        case MEDIUM:
            this->chosenDifficulty = HARD;
            break;
        case HARD:
            this->chosenDifficulty = EASY;
    }
}

}
