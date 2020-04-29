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
        /**
         * Constructs a high score entry.
         * @param name the name of the person achieving the high score
         * @param duration the duration in which the person solved the puzzle
         * @param puzzle the puzzle on which the high score was achieved on
         */
        HighScoreEntry(const std::string &name, int duration, int puzzle);

        /**
         * Returns the name associated with this high score entry.
         * @return the name
         */
        const std::string &getName() const;

        /**
         * Returns the duration associated with this high score entry.
         * @return the duration
         */
        int getDuration() const;

        const int getPuzzle() const;

private:
        const std::string &name;
        const int duration;
        const int puzzle;
};

}


#endif //MOVIEPLAITER_HIGHSCOREENTRY_H
