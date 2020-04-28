#include "Puzzle.h"

namespace model
{

Puzzle::Puzzle()
{
    *this->nodes = new PuzzleNode[PUZZLE_DEFAULT_SIZE];
}

Puzzle::~Puzzle()
{
    //dtor
}

}


