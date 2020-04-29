#include "HighScoreEntry.h"

namespace model
{

HighScoreEntry::HighScoreEntry(const std::string &name, int duration, int puzzle) : name(name), duration(duration),
    puzzle(puzzle)
{

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