#ifndef SETTINGSREADER_H
#define SETTINGSREADER_H

#include "../Settings/PlayerSettings.h"
using namespace settings;

#include <iostream>
#include <fstream>
#include <string>
#include <Fl/Fl_Export.H>
#include <Fl/Fl.H>
using namespace std;

#include "Exceptions.h"

namespace io
{

class SettingsReader
{

    enum SettingsReaderState
    {
        DIFFICULTY = 0,
        BACKGROUND_COLOR = 1,
        BUTTON_COLOR = 2,
        TEXT_COLOR = 3
    };

    public:
        SettingsReader();
        virtual ~SettingsReader();

        PlayerSettings readSettingsFile(const string& filename);
};

}

#endif // SETTINGSREADER_H
