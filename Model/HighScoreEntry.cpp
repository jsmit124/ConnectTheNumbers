#include "HighScoreEntry.h"

namespace model
{

HighScoreEntry::HighScoreEntry(std::string name, int duration, int puzzle): puzzle(puzzle), duration(duration)
{
    this->name = name;
}

const std::string &HighScoreEntry::getName() const {
    return this->name;
}

int HighScoreEntry::getDuration() const {
    return this->duration;
}

int HighScoreEntry::getPuzzle() const {
    return this->puzzle;
}

}
