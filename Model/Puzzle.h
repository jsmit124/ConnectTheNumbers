#ifndef PUZZLE_H
#define PUZZLE_H

#include "PuzzleNode.h"

#include <vector>
using namespace std;

#define PUZZLE_WIDTH 8

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

    bool evaluateNode(int index);
    bool isOnRightSide(int index);
    bool isOnLeftSide(int index);
    bool isNextNodeValid(int prevIndex, int nextIndex);

    void checkIfNextNode(int prevIndex, int nextIndex, int& nextNodeIndex);

public:
    Puzzle();
    virtual ~Puzzle();

    PuzzleNode getStartNode();
    vector<PuzzleNode>& getNodes();
    int getId();

    int getNextNodeIndex(int prevIndex);
    int getCurrentEndNodeIndex();
    int getPuzzleNodeValue(int index);
    int getStartLocation();

    void setId(int id);
    void setStartLocation(int location);

    void add(PuzzleNode node);
    void replace(int value, int index);

    int getTimeSpent() const;
    void setTimeSpent(int timeSpent);
    void incrementTimeSpent();
    void incrementTimeBy(int timeIncrease);

    bool evaluate();
    bool foundFirstNode();
    bool isPuzzleNodeEditable(int index);
};

}

#endif // PUZZLE_H
