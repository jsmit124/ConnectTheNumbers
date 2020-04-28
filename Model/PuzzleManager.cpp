#include "PuzzleManager.h"

namespace model
{

PuzzleManager::PuzzleManager()
{
    *this->puzzles = new Puzzle[PUZZLE_DEFAULT_COUNT];
}

PuzzleManager::~PuzzleManager()
{
    //dtor
}

}
