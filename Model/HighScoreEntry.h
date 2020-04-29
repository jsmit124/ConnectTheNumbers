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
         * @param score the score they achieved
         */
        HighScoreEntry(const std::string &name, int score);

        /**
         * Returns the name associated with this high score entry.
         * @return the name
         */
        const std::string &getName() const;

        /**
         * Returns the score associated with this high score entry.
         * @return the score
         */
        int getScore() const;
    private:
        const std::string &name;
        const int score;
};

}


#endif //MOVIEPLAITER_HIGHSCOREENTRY_H
