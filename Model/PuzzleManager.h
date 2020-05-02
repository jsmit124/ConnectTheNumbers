#ifndef PUZZLEMANAGER_H
#define PUZZLEMANAGER_H

#include "Puzzle.h"

#include "../Enum/Difficulty.h"

#include <vector>
#include <iostream>
using namespace std;

namespace model
{

/// Holds functionality for managing a collection of Puzzles
//
class PuzzleManager
{
    private:
        int currentPuzzleIndex;
        vector<Puzzle> puzzles;

    public:
        PuzzleManager(int);
        virtual ~PuzzleManager();

        int getNextNodeIndexOfCurrentPuzzle(int prevIndex);
        void setCurrentPuzzle(Puzzle puzzle);
        void add(const Puzzle puzzle);
        void moveToNextPuzzle();
        Puzzle& getCurrentPuzzle();
        int getCurrentPuzzleId();
        bool isFinalPuzzle();
        bool evaluateCurrentPuzzle();
        bool isLastPuzzle(Difficulty difficulty);
};

}

#endif // PUZZLEMANAGER_H
