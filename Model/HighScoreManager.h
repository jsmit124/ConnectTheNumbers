#ifndef MOVIEPLAITER_HIGHSCOREMANAGER_H
#define MOVIEPLAITER_HIGHSCOREMANAGER_H

#include <algorithm>
#include <unordered_map>
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

    /**
     * Attempts to add a score to the high score board.
     * @param name the name of the player
     * @param duration the duration the player achieved
     * @param puzzle the puzzle the player solved
     */
    void add(const std::string& name, int duration, int puzzle);
private:
    vector<HighScoreEntry*>* getOrCreatePuzzleScoreboard(int puzzleId);

    unordered_map<int, vector<HighScoreEntry*>*> *scoresByPuzzle;
};

}

#endif //MOVIEPLAITER_HIGHSCOREMANAGER_H
