#ifndef PUZZLEMANAGER_H
#define PUZZLEMANAGER_H

#include "Puzzle.h"

namespace model
{

class PuzzleManager
{
    const int PUZZLE_DEFAULT_COUNT = 4;

    private:
        Puzzle* puzzles[];

    public:
        PuzzleManager();
        virtual ~PuzzleManager();
};

}

#endif // PUZZLEMANAGER_H
