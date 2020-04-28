#ifndef PUZZLE_H
#define PUZZLE_H

#include "PuzzleNode.h"

#include <vector>
using namespace std;

namespace model
{

/// Holds functionality for managing a collection of PuzzleNodes
//
class Puzzle
{
    private:
        vector<PuzzleNode>* nodes;

    public:
        Puzzle();
        virtual ~Puzzle();

        void add(const PuzzleNode& node);
        void replace(unsigned int value, int index);
};

}

#endif // PUZZLE_H
