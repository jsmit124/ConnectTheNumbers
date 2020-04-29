#ifndef MOVIEPLAITER_HIGHSCOREMANAGER_H
#define MOVIEPLAITER_HIGHSCOREMANAGER_H

#include <vector>
#include "./HighScoreEntry.h"

using namespace std;

namespace model {

/**
 * Keeps track of all potential high scores.
 */
class HighScoreManager
{
public:
    /**
     * Constructs a new HighScoreManager.
     */
    HighScoreManager();
    /**
     * Destroys this HighScoreManager.
     */
    ~HighScoreManager();
private:
    vector<HighScoreEntry> *scores;
};

}

#endif //MOVIEPLAITER_HIGHSCOREMANAGER_H
