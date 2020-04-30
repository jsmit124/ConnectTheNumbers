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
        vector<PuzzleNode> nodes;
        int timeSpent;

        vector<PuzzleNode> getSurroundingNodes(int index);
        bool evaluateNode(int index);

        bool isOnRightSide(int index);
        bool isOnLeftSide(int index);

    public:
        Puzzle();
        virtual ~Puzzle();

        PuzzleNode getStartNode();
        vector<PuzzleNode>& getNodes();
        int getId();

        int getPuzzleNodeValue(int index);
        bool isPuzzleNodeEditable(int index);
        void setId(int id);
        void setStartLocation(int location);
        void add(PuzzleNode node);
        void replace(int value, int index);

        int getTimeSpent() const;

        void setTimeSpent(int timeSpent);
        void incrementTimeSpent();

        bool evaluate();
};

}

#endif // PUZZLE_H
