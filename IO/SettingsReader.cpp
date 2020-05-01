#include "SettingsReader.h"

namespace io
{

SettingsReader::SettingsReader()
{
    //ctor
}

SettingsReader::~SettingsReader()
{
    //dtor
}

PlayerSettings SettingsReader::readSettingsFile(const string& filename)
{
    ifstream inFile(filename);

    if (!inFile.good())
    {
        throw FileErrorException();
    }

    PlayerSettings settings;
    SettingsReaderState state = DIFFICULTY;
    string line;

    while (getline(inFile, line))
    {
        switch (state)
        {
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

    return settings;
}

}
