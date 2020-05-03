#include "HighScoreManager.h"

namespace model
{

/// Constructs a new HighScoreManager.
//
HighScoreManager::HighScoreManager()
{
    this->scores = new vector<HighScoreEntry*>();
}

/// Destroys this HighScoreManager.
//
HighScoreManager::~HighScoreManager()
{
    this->clearAndDeleteAllScores();
    delete this->scores;
}

/// Attempts to add a score to the high score board.
//
// @param name the name of the player
// @param duration the duration the player achieved
// @param puzzle the puzzle the player solved
void HighScoreManager::add(std::string name, int duration, int puzzle)
{
    auto *entry = new HighScoreEntry(name, duration, puzzle);
    this->scores->push_back(entry);
}

/// Gets the top 10 entries on the high score table, sorted by duration in
/// ascending order.
// @return the 10 entries in ascending duration
vector<HighScoreEntry *> HighScoreManager::getTopTenByDuration()
{
    vector<HighScoreEntry*> entriesCopy(*this->scores);
    sort(entriesCopy.begin(), entriesCopy.end(), [](HighScoreEntry *first, HighScoreEntry *second)
    {
        return first->getDuration() < second->getDuration();
    });
    entriesCopy.resize(min(entriesCopy.size(), (vector<HighScoreEntry*>::size_type) MAXIMUM_HIGH_SCORE_ENTRIES));
    return entriesCopy;
}

/// Gets the top 10 entries on the high score, sorted by puzzle and then
/// duration in a two-level sort in ascending order.
// @return the 10 entries in ascending order by puzzle and then duration
vector<HighScoreEntry *> HighScoreManager::getTopTenByPuzzle()
{
    vector<HighScoreEntry*> entriesCopy(*this->scores);
    sort(entriesCopy.begin(), entriesCopy.end(), [](HighScoreEntry *first, HighScoreEntry *second)
    {
        if (first->getPuzzle() != second->getPuzzle())
        {
            return first->getPuzzle() < second->getPuzzle();
        }
        return first->getDuration() < second->getDuration();
    });
    entriesCopy.resize(min(entriesCopy.size(), (vector<HighScoreEntry*>::size_type) MAXIMUM_HIGH_SCORE_ENTRIES));
    return entriesCopy;
}

/// Clears the scoreboard completely.
//
void HighScoreManager::clear()
{
    this->clearAndDeleteAllScores();
}


/// Gets all scores directly. This is used to save all high scores to disk.
// @return all scores in this HighScoreManager
vector<HighScoreEntry *> *HighScoreManager::getScores() const
{
    return this->scores;
}

void HighScoreManager::clearAndDeleteAllScores()
{
    for (const auto &entry : *this->scores)
    {
        delete entry;
    }

    this->scores->clear();
}

}
