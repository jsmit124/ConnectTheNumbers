#include "PuzzleManager.h"

namespace model
{

/// Puzzle Manager constructor
//
// @precondition: none
// @postcondition: this->puzzles.size() == 0
//                 this->currentPuzzleIndex == 0
//
PuzzleManager::PuzzleManager(int puzzleCount)
{
    this->puzzles.reserve(puzzleCount);
    this->currentPuzzleIndex = 0;
}

/// Puzzle manager destructor
//
PuzzleManager::~PuzzleManager()
{
}

/// Sets the puzzle as the current puzzle and replaces the previous puzzle
/// at the location based on its puzzle ID.
//
// @precondition: none
// @postcondition: this->currentPuzzleIndex = puzzle.getId() - 1
//                 this->puzzles[index] = puzzle
// @param puzzle: puzzle to set
//
void PuzzleManager::setCurrentPuzzle(Puzzle puzzle)
{
    this->currentPuzzleIndex = puzzle.getId() - 1;
    this->puzzles.at(this->currentPuzzleIndex) = puzzle;
}

/// Adds a [puzzle] to the puzzle collection
//
// @precondition: none
// @postcondition: this->puzzles.size()++
//
void PuzzleManager::add(Puzzle puzzle, Puzzle solvedPuzzle)
{
    this->solvedPuzzles.push_back(solvedPuzzle);
    this->puzzles.push_back(puzzle);
}

/// Increments the current puzzle index by one
//
// @precondition: none
// @postcondition: this->currentPuzzleIndex++
//
void PuzzleManager::moveToNextPuzzle()
{
    this->getCurrentPuzzle().setTimeSpent(0);
    this->currentPuzzleIndex++;
}

/// Returns the current puzzle
//
// @precondition: none
// @postcondition: none
// @return the current puzzle
Puzzle& PuzzleManager::getCurrentPuzzle()
{
    return this->puzzles.at(this->currentPuzzleIndex);
}

int PuzzleManager::getCurrentPuzzleSolvedNodeValue(int index)
{
    return this->solvedPuzzles.at(this->currentPuzzleIndex).getPuzzleNodeValue(index);
}

int PuzzleManager::getNextNodeOfSolvablePuzzle(int index)
{
    Puzzle puzzle = this->solvedPuzzles.at(this->currentPuzzleIndex);
    return puzzle.getNextNodeIndex(index);
}

/// Returns the current puzzle id (+1 for vector offset)
//
// @precondition: none
// @postcondition: none
// @return the current puzzle number
//
int PuzzleManager::getCurrentPuzzleId()
{
    return this->currentPuzzleIndex + 1;
}

int PuzzleManager::getCurrentValidEndNodeIndex()
{
    int endIndex = this->getCurrentPuzzle().getCurrentEndNodeIndex();
    int currentValue = this->getCurrentPuzzle().getPuzzleNodeValue(endIndex);
    int solvedPuzzleValue = this->solvedPuzzles.at(this->currentPuzzleIndex).getPuzzleNodeValue(endIndex);

    if (currentValue != solvedPuzzleValue)
    {
        int solvedPuzzleIndex = this->solvedPuzzles.at(this->currentPuzzleIndex).getStartLocation();
        return solvedPuzzleIndex;
    }
    return endIndex;
}

int PuzzleManager::getNextNodeIndexOfCurrentPuzzle(int prevIndex)
{
    return this->getCurrentPuzzle().getNextNodeIndex(prevIndex);
}

/// TODO
//
bool PuzzleManager::evaluateCurrentPuzzle()
{
    int currentIndex = this->currentPuzzleIndex;
    return this->puzzles.at(currentIndex).evaluate();
}

bool PuzzleManager::isFinalPuzzle()
{
    return this->getCurrentPuzzleId() == this->puzzles.size();
}

bool PuzzleManager::isLastPuzzle(Difficulty difficulty)
{
    return this->getCurrentPuzzleId() >= difficulty;
}

}
