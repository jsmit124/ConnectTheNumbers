#include "HighScoreReader.h"

#include <utility>

namespace io
{

    HighScoreReader::HighScoreReader() = default;

    HighScoreReader::~HighScoreReader() = default;

    void HighScoreReader::loadScores(HighScoreManager *target, const string &fileName)
    {
        ifstream stream(fileName);
        if (!stream.good())
        {
            throw FileErrorException();
        }

        string line;
        while (getline(stream, line))
        {
            this->readAndAddEntry(target, line);
        }
    }

    void HighScoreReader::readAndAddEntry(HighScoreManager *scoreboard, string line) {
        vector<string> nodes = split(std::move(line), ",");
        if (nodes.size() != 3) {
            throw FileErrorException();
        }

        auto name = nodes[0];
        int duration = toInt(nodes[1], "unable to convert duration into integer");
        int puzzleId = toInt(nodes[2], "unable to convert puzzle ID into integer");
        scoreboard->add(name, duration, puzzleId);
    }
}