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
    vector<Puzzle> solvedPuzzles;

public:
    PuzzleManager(int);
    virtual ~PuzzleManager();

    Puzzle& getCurrentPuzzle();

    int getCurrentValidEndNodeIndex();
    int getNextNodeIndexOfCurrentPuzzle(int prevIndex);
    int getNextNodeOfSolvablePuzzle(int prevIndex);
    int getCurrentPuzzleSolvedNodeValue(int index);
    int getCurrentPuzzleId();

    void setCurrentPuzzle(Puzzle puzzle);
    void setPuzzleAt(Puzzle puzzle, int index);

    bool isFinalPuzzle();
    bool evaluateCurrentPuzzle();
    bool isLastPuzzle(Difficulty difficulty);

    void add(Puzzle puzzle, Puzzle solvedPuzzle);
    void moveToNextPuzzle();
    void resetCurrentPuzzleIndex();
};

}

#endif // PUZZLEMANAGER_H
