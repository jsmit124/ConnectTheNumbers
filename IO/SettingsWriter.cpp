#include "SettingsWriter.h"

namespace io
{

SettingsWriter::SettingsWriter() = default;
SettingsWriter::~SettingsWriter() = default;

/// Writes the settings from [settings] to the [filename]
//
// @post: filename.contents += settings
// @param filename: the name of the file
// @param settings: the settings to write from
void SettingsWriter::writeSettingsToFile(const string& filename, PlayerSettings& settings)
{
    ofstream outFile(filename);

    outFile << settings.getDifficulty() << endl;
    outFile << settings.getBackgroundColor() << endl;
    outFile << settings.getButtonColor() << endl;
    outFile << settings.getTextColor() << endl;

    outFile.close();
}

}
