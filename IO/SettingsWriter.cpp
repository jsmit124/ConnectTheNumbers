#include "SettingsWriter.h"

namespace io
{

SettingsWriter::SettingsWriter()
{
}

SettingsWriter::~SettingsWriter()
{
}

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
