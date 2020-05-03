#ifndef MOVIEPLAITER_HIGHSCOREMANAGER_H
#define MOVIEPLAITER_HIGHSCOREMANAGER_H

#include <algorithm>
#include <vector>
#include "./HighScoreEntry.h"

#define MAXIMUM_HIGH_SCORE_ENTRIES 10

using namespace std;

namespace model
{

/**
 * Keeps track of all potential high scores.
 */
class HighScoreManager
{

public:

    HighScoreManager();
    ~HighScoreManager();

    void add(std::string name, int duration, int puzzle);
    vector<HighScoreEntry*> getTopTenByDuration();
    vector<HighScoreEntry*> getTopTenByPuzzle();
    void clear();
    vector<HighScoreEntry *> *getScores() const;

private:
    vector<HighScoreEntry*> *scores;

    void clearAndDeleteAllScores();
};

}

#endif //MOVIEPLAITER_HIGHSCOREMANAGER_H
