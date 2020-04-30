#include "HighScoreManager.h"

namespace model {

HighScoreManager::HighScoreManager() {
    this->scores = new vector<HighScoreEntry*>();
}

HighScoreManager::~HighScoreManager() {
    delete this->scores;
    this->scores = nullptr;
}

void HighScoreManager::add(const std::string &name, int duration, int puzzle) {
    auto *entry = new HighScoreEntry(name, duration, puzzle);
    this->scores->push_back(entry);
}

vector<HighScoreEntry *> HighScoreManager::getTopTenByDuration() {
    vector<HighScoreEntry*> entriesCopy(*this->scores);
    sort(entriesCopy.begin(), entriesCopy.end(), [](HighScoreEntry *first, HighScoreEntry *second) {
        return first->getDuration() < second->getDuration();
    });
    entriesCopy.erase(entriesCopy.cbegin() + MAXIMUM_HIGH_SCORE_ENTRIES, entriesCopy.cend());
    return entriesCopy;
}

}