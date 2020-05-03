#include "HighScoreEntry.h"

namespace model
{

/// Constructs a high score entry.
// @param name the name of the person achieving the high score
// @param duration the duration in which the person solved the puzzle
// @param puzzle the puzzle on which the high score was achieved on
// @post this->getName() == name && this->getDuration() == duration && this->getPuzzle() == puzzle
HighScoreEntry::HighScoreEntry(std::string name, int duration, int puzzle): puzzle(puzzle), duration(duration)
{
    this->name = name;
}

/// Returns the name associated with this high score entry.
// @return the name
const std::string &HighScoreEntry::getName() const
{
    return this->name;
}

/// Returns the duration associated with this high score entry.
// @return the duration
int HighScoreEntry::getDuration() const
{
    return this->duration;
}

/// Returns the puzzle associated with this high score entry.
// @return the puzzle
int HighScoreEntry::getPuzzle() const
{
    return this->puzzle;
}

}
