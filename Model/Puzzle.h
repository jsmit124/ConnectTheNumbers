#ifndef PUZZLE_H
#define PUZZLE_H

#include "PuzzleNode.h"

namespace model
{

class Puzzle
{
    const int PUZZLE_DEFAULT_SIZE = 64;

    private:
        PuzzleNode* nodes[];

    public:
        Puzzle();
        virtual ~Puzzle();
};

}

#endif // PUZZLE_H
