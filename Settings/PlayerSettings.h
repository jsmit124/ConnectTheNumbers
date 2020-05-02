#ifndef PLAYERSETTINGS_H
#define PLAYERSETTINGS_H

#include "../Enum/Difficulty.h"

#include <Fl/Fl_Export.H>
#include <Fl/Fl.H>
using namespace std;

namespace settings
{

/// Hold settings for the player
//
class PlayerSettings
{

private:

    Difficulty lastSavedDifficulty;
    Difficulty chosenDifficulty;
    Fl_Color buttonColor;
    Fl_Color backgroundColor;
    Fl_Color textColor;

public:
    PlayerSettings();
    virtual ~PlayerSettings();

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

    void moveToNextDifficulty();
};

}

#endif // PLAYERSETTINGS_H
