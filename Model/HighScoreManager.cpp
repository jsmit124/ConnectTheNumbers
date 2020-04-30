#include "HighScoreManager.h"

#include <utility>

namespace model {

HighScoreManager::HighScoreManager() {
    this->scores = new vector<HighScoreEntry*>();
}

HighScoreManager::~HighScoreManager() {
    delete this->scores;
    this->scores = nullptr;
}

void HighScoreManager::add(std::string name, int duration, int puzzle) {
    auto *entry = new HighScoreEntry(name, duration, puzzle);
    this->scores->push_back(entry);
}

vector<HighScoreEntry *> HighScoreManager::getTopTenByDuration() {
    vector<HighScoreEntry*> entriesCopy(*this->scores);
    sort(entriesCopy.begin(), entriesCopy.end(), [](HighScoreEntry *first, HighScoreEntry *second) {
        return first->getDuration() < second->getDuration();
    });
    entriesCopy.resize(min(entriesCopy.size(), (vector<HighScoreEntry*>::size_type) MAXIMUM_HIGH_SCORE_ENTRIES));
    return entriesCopy;
}

void HighScoreManager::clear() {
    delete this->scores;
    this->scores = new vector<HighScoreEntry*>();
}

vector<HighScoreEntry *> *HighScoreManager::getScores() const {
    return this->scores;
}

}