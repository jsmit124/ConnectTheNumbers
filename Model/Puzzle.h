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
        int id;
        int startLocation;
        vector<PuzzleNode>* nodes;

    public:
        Puzzle();
        virtual ~Puzzle();

        PuzzleNode getStartNode();
        vector<PuzzleNode>& getNodes();
        int getId();

        void setId(int id);
        void setStartLocation(int location);
        void add(const PuzzleNode& node);
        void replace(unsigned int value, int index);
};

}

#endif // PUZZLE_H
