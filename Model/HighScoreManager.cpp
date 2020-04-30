#include "HighScoreManager.h"

namespace model {

HighScoreManager::HighScoreManager() {
    this->scores = new vector<HighScoreEntry*>();
}

HighScoreManager::~HighScoreManager() {
    this->clearAndDeleteAllScores();
    delete this->scores;
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

void HighScoreManager::clearAndDeleteAllScores()
{
    for (const auto &entry : *this->scores)
    {
        delete entry;
    }

    this->scores->clear();
}

void HighScoreManager::clear()
{
    this->clearAndDeleteAllScores();
}

vector<HighScoreEntry *> *HighScoreManager::getScores() const {
    return this->scores;
}

}