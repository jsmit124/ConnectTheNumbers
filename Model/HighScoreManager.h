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
    void add(std::string name, int duration, int puzzle);

    /**
     * Gets the top 10 entries on the high score table, sorted by duration in
     * ascending order.
     * @return the 10 entries in ascending duration
     */
    vector<HighScoreEntry*> getTopTenByDuration();

    /**
     * Gets the top 10 entries on the high score, sorted by puzzle and then
     * duration in a two-level sort in ascending order.
     * @return the 10 entries in ascending order by puzzle and then duration
     */
    vector<HighScoreEntry*> getTopTenByPuzzle();

    /**
     * Clears the scoreboard completely.
     */
    void clear();

    /**
     * Gets all scores directly. This is used to save all high scores to disk.
     * @return all scores in this HighScoreManager
     */
    vector<HighScoreEntry *> *getScores() const;

private:
    vector<HighScoreEntry*> *scores;

    void clearAndDeleteAllScores();
};

}

#endif //MOVIEPLAITER_HIGHSCOREMANAGER_H
