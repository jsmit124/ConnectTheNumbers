#ifndef PLAYERSETTINGS_H
#define PLAYERSETTINGS_H

#include "../Enum/Difficulty.h"

#include <Fl/Fl_Export.H>
#include <Fl/Fl.H>
#include <string>
using namespace std;

namespace settings
{

/// Hold settings for the player
//
class PlayerSettings
{

private:
    string DEFAULT_USERNAME = "plzGiveMeA";

    Difficulty lastSavedDifficulty;
    Difficulty chosenDifficulty;
    Fl_Color buttonColor;
    Fl_Color backgroundColor;
    Fl_Color textColor;
    string username;

public:
    PlayerSettings();
    virtual ~PlayerSettings();

    void setUsername(const string& username);
    void setButtonColor(Fl_Color color);
    void setTextColor(Fl_Color color);
    void setBackgroundColor(Fl_Color color);
    void setDifficulty(Difficulty selection);
    void setLastSavedDifficulty(Difficulty difficulty);

    Fl_Color getButtonColor();
    Fl_Color getBackgroundColor();
    Difficulty getDifficulty();
    Difficulty getLastSavedDifficulty();
    Fl_Color getTextColor();
    string getUsername();

    void moveToNextDifficulty();
};

}

#endif // PLAYERSETTINGS_H
