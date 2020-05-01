#ifndef SETTINGSWRITER_H
#define SETTINGSWRITER_H

#include "../Settings/PlayerSettings.h"
using namespace settings;

#include <string>
#include <fstream>
#include <iostream>
using namespace std;

namespace io
{

class SettingsWriter
{
    private:

    public:
        SettingsWriter();
        virtual ~SettingsWriter();

        void writeSettingsToFile(const string& filename, PlayerSettings& settings);
};

}

#endif // SETTINGSWRITER_H
