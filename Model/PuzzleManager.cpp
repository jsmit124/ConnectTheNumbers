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
    puzzle.setTimeSpent(0);
    this->getCurrentPuzzle().setTimeSpent(0);

    this->currentPuzzleIndex = puzzle.getId() - 1;
    this->puzzles.at(this->currentPuzzleIndex) = puzzle;
}

/// Adds a [puzzle] to the puzzle collection
//
// @precondition: none
// @postcondition: this->puzzles.size()++
//
void PuzzleManager::add(const Puzzle puzzle)
{
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

/// Returns the current puzzle number (+1 for vector offset)
//
// @precondition: none
// @postcondition: none
// @return the current puzzle number
//
int PuzzleManager::getCurrentPuzzleNumber()
{
    return this->currentPuzzleIndex + 1;
}

/// TODO
//
bool PuzzleManager::evaluateCurrentPuzzle()
{
    int currentIndex = this->currentPuzzleIndex;
    return this->puzzles.at(currentIndex).evaluate();
}

bool PuzzleManager::isLastPuzzle()
{
    return this->getCurrentPuzzleNumber() == this->puzzles.size();
}

}
