#include "HighScoreManager.h"

namespace model {

HighScoreManager::HighScoreManager() {
    this->scores = new vector<HighScoreEntry>();
}

HighScoreManager::~HighScoreManager() {
    delete this->scores;
    this->scores = nullptr;
}

}