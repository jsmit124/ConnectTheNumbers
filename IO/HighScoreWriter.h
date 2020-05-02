#ifndef MOVIEPLAITER_HIGHSCOREWRITER_H
#define MOVIEPLAITER_HIGHSCOREWRITER_H

#include "../Model/HighScoreEntry.h"
#include "../Model/HighScoreManager.h"

#include <string>
#include <fstream>
#include <iostream>

using namespace std;
using namespace model;

namespace io
{

/// Handles writing scores to a file
//
class HighScoreWriter
{

private:
    void writeScore(ofstream *stream, HighScoreEntry* entry);

public:
    HighScoreWriter();
    virtual ~HighScoreWriter();

    void writeHighScores(HighScoreManager *manager, const string& fileName);
};

}

#endif //MOVIEPLAITER_HIGHSCOREWRITER_H
