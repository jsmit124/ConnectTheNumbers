#ifndef PLAYERSETTINGS_H
#define PLAYERSETTINGS_H

#include "../Enum/Difficulty.h"

#include <Fl/Fl_Export.H>
#include <Fl/Fl.H>
using namespace std;

namespace settings
{

class PlayerSettings
{
    public:
        PlayerSettings();
        virtual ~PlayerSettings();

        void setButtonColor(Fl_Color color);
        void setBackgroundColor(Fl_Color color);
        void setDifficulty(Difficulty selection);

        Fl_Color getButtonColor();
        Fl_Color getBackgroundColor();
        Difficulty getDifficulty();

    private:
        Difficulty chosenDifficulty;
        Fl_Color buttonColor;
        Fl_Color backgroundColor;
};

}

#endif // PLAYERSETTINGS_H
