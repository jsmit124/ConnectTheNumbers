#include "SettingsReader.h"

namespace io
{

SettingsReader::SettingsReader() = default;
SettingsReader::~SettingsReader() = default;

/// Reads the settings from the [filename] and returns them
//
// @param filename: the name of the file
// @return the settings read from file
// @throws FileErrorException if file doesn't exist
PlayerSettings SettingsReader::readSettingsFile(const string& filename)
{
    ifstream inFile(filename);

    if (!inFile.good())
    {
        throw FileErrorException();
    }

    PlayerSettings settings;
    SettingsReaderState state = USERNAME;
    string line;

    while (getline(inFile, line))
    {
        this->setState(state,settings,line);
    }

    return settings;
}

void SettingsReader::setState(SettingsReaderState& state, PlayerSettings& settings, string& line)
{
    switch (state)
    {
    case USERNAME:
        settings.setUsername(line);
        state = DIFFICULTY;
        break;
    case DIFFICULTY:
        settings.setLastSavedDifficulty(static_cast<Difficulty>(stoi(line)));
        state = BACKGROUND_COLOR;
        break;
    case BACKGROUND_COLOR:
        settings.setBackgroundColor(static_cast<Fl_Color>(stoi(line)));
        state = BUTTON_COLOR;
        break;
    case BUTTON_COLOR:
        settings.setButtonColor(static_cast<Fl_Color>(stoi(line)));
        state = TEXT_COLOR;
        break;
    case TEXT_COLOR:
        settings.setTextColor(static_cast<Fl_Color>(stoi(line)));
        break;
    }
}

}
