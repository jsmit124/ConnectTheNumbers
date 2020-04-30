#include "HighScoreWriter.h"

namespace io
{

HighScoreWriter::HighScoreWriter() = default;

HighScoreWriter::~HighScoreWriter() = default;

void HighScoreWriter::writeHighScores(HighScoreManager *manager, const string &fileName)
{
    ofstream stream(fileName);
    vector<HighScoreEntry*>* entries = manager->getScores();
    for (auto & entry : *entries)
    {
        this->writeScore(&stream, entry);
    }
}

void HighScoreWriter::writeScore(ofstream *stream, HighScoreEntry *entry)
{
    *stream << entry->getName() << "," << entry->getDuration() << "," << entry->getPuzzle() << endl;
}

}