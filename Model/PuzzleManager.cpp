#include "PuzzleManager.h"

namespace model
{

/// Puzzle Manager constructor
//
// @precondition: none
// @postcondition: this->puzzles.size() == 0
//                 this->currentPuzzleIndex == 0
//
PuzzleManager::PuzzleManager()
{
    this->puzzles = new vector<Puzzle>();
    this->currentPuzzleIndex = 0;
}

/// Puzzle manager destructor
//
// @postcondition: this->puzzles.size() == 0
//                 this->puzzles == nullptr
//
PuzzleManager::~PuzzleManager()
{
    delete this->puzzles;
    this->puzzles = nullptr;
}

/// Adds a [puzzle] to the puzzle collection
//
// @precondition: none
// @postcondition: this->puzzles.size()++
//
void PuzzleManager::add(const Puzzle& puzzle)
{
    this->puzzles->push_back(puzzle);
}

/// Increments the current puzzle index by one
//
// @precondition: none
// @postcondition: this->currentPuzzleIndex++
//
void PuzzleManager::moveToNextPuzzle()
{
    this->currentPuzzleIndex++;
}

/// Returns the current puzzle
//
// @precondition: none
// @postcondition: none
// @return the current puzzle
Puzzle PuzzleManager::getCurrentPuzzle()
{
    return this->puzzles->at(this->currentPuzzleIndex);
}

}
