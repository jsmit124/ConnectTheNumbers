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

/// Functionality to read settings
//
class SettingsReader
{

    enum SettingsReaderState
    {
        USERNAME = 0,
        DIFFICULTY = 1,
        BACKGROUND_COLOR = 2,
        BUTTON_COLOR = 3,
        TEXT_COLOR = 4
    };

private:
    void setState(SettingsReaderState& state, PlayerSettings& settings, string& line);

public:
    SettingsReader();
    virtual ~SettingsReader();

    PlayerSettings readSettingsFile(const string& filename);
};

}

#endif // SETTINGSREADER_H
