#include "HighScoreManager.h"

namespace model {

HighScoreManager::HighScoreManager() {
    this->scoresByPuzzle = new unordered_map<int, vector<HighScoreEntry*>*>();
}

HighScoreManager::~HighScoreManager() {
    delete this->scoresByPuzzle;
    this->scoresByPuzzle = nullptr;
}

void HighScoreManager::add(const std::string &name, int duration, int puzzle) {
    auto *entry = new HighScoreEntry(name, duration, puzzle);
    this->getOrCreatePuzzleScoreboard(puzzle)->push_back(entry);
}

vector<HighScoreEntry*>* HighScoreManager::getOrCreatePuzzleScoreboard(int puzzleId) {
    try {
        return this->scoresByPuzzle->at(puzzleId);
    } catch (out_of_range &e) {
        auto *scoresVector = new vector<HighScoreEntry*>();
        this->scoresByPuzzle->emplace(puzzleId, scoresVector);
        return scoresVector;
    }
}

}