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
    this->username = DEFAULT_USERNAME;
}

PlayerSettings::~PlayerSettings() = default;

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

/// Sets the difficulty to this->chosenDifficulty
// @param selection: the difficulty to set to
// @post: this->chosenDifficulty = selection
void PlayerSettings::setDifficulty(Difficulty selection)
{
    this->chosenDifficulty = selection;
}

/// Sets the last saved difficulty
// @param difficulty: to set to
// @post: this->lastSavedDifficulty = difficulty
void PlayerSettings::setLastSavedDifficulty(Difficulty difficulty)
{
    this->lastSavedDifficulty = difficulty;
}

/// Sets the username to [username]
// @post: this->username = username
// @param username: username to set
void PlayerSettings::setUsername(const string& username)
{
    this->username = username;
}

/// Gets the username to [username]
// @return the username
string PlayerSettings::getUsername()
{
    return this->username;
}

/// Returns the Fl_Color chosen to be the button color
//
//  @return this->buttonColor
Fl_Color PlayerSettings::getButtonColor()
{
    return this->buttonColor;
}

/// Returns the Fl_Color chosen to be the background color
//
// @return this->backgroundColor
Fl_Color PlayerSettings::getBackgroundColor()
{
    return this->backgroundColor;
}

/// Returns the text color
// @return the text color
Fl_Color PlayerSettings::getTextColor()
{
    return this->textColor;
}

/// Returns the chosen difficulty
// @return the chosen difficulty
Difficulty PlayerSettings::getDifficulty()
{
    return this->chosenDifficulty;
}

/// Returns the last saved difficulty
// @return the last saved difficulty
Difficulty PlayerSettings::getLastSavedDifficulty()
{
    return this->lastSavedDifficulty;
}

/// Moves to the next available difficulty
// @post EASY -> MEDIUM -> HARD
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
