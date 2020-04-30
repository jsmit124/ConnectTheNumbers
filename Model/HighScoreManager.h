#ifndef MOVIEPLAITER_HIGHSCOREMANAGER_H
#define MOVIEPLAITER_HIGHSCOREMANAGER_H

#include <algorithm>
#include <vector>
#include "./HighScoreEntry.h"

#define MAXIMUM_HIGH_SCORE_ENTRIES 10

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

    /**
     * Attempts to add a score to the high score board.
     * @param name the name of the player
     * @param duration the duration the player achieved
     * @param puzzle the puzzle the player solved
     */
    void add(const std::string& name, int duration, int puzzle);

    /**
     * Gets the top 10 entries on the high score, sorted by duration in
     * ascending order.
     * @return the 10 entries in ascending duration
     */
    vector<HighScoreEntry> getTopTenByDuration();

    /**
     * Clears the scoreboard completely.
     */
    void clear();
private:
    vector<HighScoreEntry> scores;
};

}

#endif //MOVIEPLAITER_HIGHSCOREMANAGER_H
