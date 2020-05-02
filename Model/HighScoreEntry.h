#ifndef MOVIEPLAITER_HIGHSCOREENTRY_H
#define MOVIEPLAITER_HIGHSCOREENTRY_H

#include <string>

namespace model {

/**
 * Represents a high score entry.
 */
class HighScoreEntry
{
    public:
        HighScoreEntry(std::string name, int duration, int puzzle);

        const std::string &getName() const;

        int getDuration() const;

        int getPuzzle() const;

private:
        std::string name;
        const int duration;
        const int puzzle;
};

}


#endif //MOVIEPLAITER_HIGHSCOREENTRY_H
