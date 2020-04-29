#include "HighScoreEntry.h"

namespace model
{

HighScoreEntry::HighScoreEntry(const std::string &name, int score) : name(name), score(score) {

}

const std::string &HighScoreEntry::getName() const {
    return name;
}

int HighScoreEntry::getScore() const {
    return score;
}

}