#include "HighScoreWriter.h"

namespace io
{

HighScoreWriter::HighScoreWriter() = default;
HighScoreWriter::~HighScoreWriter() = default;

/// Writes the highscores to [fileName]
//
// @pre: none
// @post: fileName.contents += scores
// @param manager: the manager to get scores from
// @param fileName: name of file to write to
void HighScoreWriter::writeHighScores(HighScoreManager *manager, const string &fileName)
{
    ofstream stream(fileName);
    vector<HighScoreEntry*>* entries = manager->getScores();
    for (auto & entry : *entries)
    {
        this->writeScore(&stream, entry);
    }

    stream.flush();
    stream.close();
}

void HighScoreWriter::writeScore(ofstream *stream, HighScoreEntry *entry)
{
    *stream << entry->getName() << "," << entry->getDuration() << "," << entry->getPuzzle() << endl;
}

}
