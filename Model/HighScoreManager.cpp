#include "HighScoreManager.h"

namespace model {

HighScoreManager::HighScoreManager() = default;

HighScoreManager::~HighScoreManager() = default;

void HighScoreManager::add(const std::string &name, int duration, int puzzle) {
    HighScoreEntry entry(name, duration, puzzle);
    this->scores.push_back(entry);
}

vector<HighScoreEntry> HighScoreManager::getTopTenByDuration() {
    vector<HighScoreEntry> entriesCopy(this->scores);
    sort(entriesCopy.begin(), entriesCopy.end(), [](HighScoreEntry *first, HighScoreEntry *second) {
        return first->getDuration() < second->getDuration();
    });
    entriesCopy.erase(entriesCopy.cbegin() + MAXIMUM_HIGH_SCORE_ENTRIES, entriesCopy.cend());
    return entriesCopy;
}

void HighScoreManager::clear() {
    this->scores.erase(this->scores.cbegin(), this->scores.cend());
}

}