#ifndef PUZZLEMANAGER_H
#define PUZZLEMANAGER_H

#include "Puzzle.h"

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
        PuzzleManager(int puzzleCount);
        virtual ~PuzzleManager();

        void setCurrentPuzzle(Puzzle puzzle);
        void add(const Puzzle puzzle);
        void moveToNextPuzzle();
        Puzzle getCurrentPuzzle();
        int getCurrentPuzzleNumber();
        bool evaluateCurrentPuzzle();
};

}

#endif // PUZZLEMANAGER_H
