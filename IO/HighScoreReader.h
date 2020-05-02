#ifndef MOVIEPLAITER_HIGHSCOREREADER_H
#define MOVIEPLAITER_HIGHSCOREREADER_H

#include "../Model/HighScoreEntry.h"
#include "../Model/HighScoreManager.h"
#include <Exceptions.h>
#include "../Utils/Utils.h"

#include <string>
#include <fstream>
#include <iostream>

using namespace std;
using namespace model;

namespace io
{

/// Reads in the high scores
//
class HighScoreReader
{

public:
    HighScoreReader();
    virtual ~HighScoreReader();

    void loadScores(HighScoreManager *target, const string &fileName);

private:
    void readAndAddEntry(HighScoreManager *scoreboard, string line);

};
}

#endif //MOVIEPLAITER_HIGHSCOREREADER_H
