#include "Puzzle.h"

namespace model
{

/// Constructor for a Puzzle
//
// @precondition: none
// @postcondition: this->nodes.size() == 0
//
Puzzle::Puzzle()
{
}

/// Puzzle destructor
//
// @postcondition: this->nodes.size() == 0
//                 this->nodes == nullptr
//
Puzzle::~Puzzle()
{
}

/// Returns the puzzle id
//
// @precondition: none
// @postcondition: none
// @return the puzzle id
//
int Puzzle::getId()
{
    return this->id;
}

int Puzzle::getPuzzleNodeValue(int index)
{
    return this->nodes.at(index).getValue();
}

bool Puzzle::isPuzzleNodeEditable(int index)
{
    return this->nodes.at(index).getIsEditable();
}

/// Returns the collection of nodes in the puzzle
//
// @precondition: none
// @postcondition: none
// @return the collection of nodes
//
vector<PuzzleNode>& Puzzle::getNodes()
{
    return this->nodes;
}

/// Returns the puzzles start location
//
// @precondition: none
// @postcondition: none
// @return value of puzzles start location
//
PuzzleNode Puzzle::getStartNode()
{
    return this->nodes.at(this->startLocation);
}

/// Sets the puzzle id to [id]
//
// @precondition: none
// @postcondition: this->id = id
// @param id: the id to set
//
void Puzzle::setId(int id)
{
    this->id = id;
}

/// Sets the start location of the puzzle
//
// @precondition: none
// @postcondition: this->startLocation = location
//
void Puzzle::setStartLocation(int location)
{
    this->startLocation = location;
}

/// Adds a [node] to the end of the puzzle
//
// @precondition: none
// @postcondition: this->nodes.size()++
// @param node: the node to add
//
void Puzzle::add(PuzzleNode node)
{
    this->nodes.push_back(node);
}

/// Replaces the value of the node at the specific [index]
//
// @precondition: none
// @postcondition: this->nodes[index].getValue() == value
// @param value: the value
// @param index: the index to set the value to
//
void Puzzle::replace(int value, int index)
{
    PuzzleNode& node = this->nodes.at(index);
    node.setValue(value);
}

bool Puzzle::evaluate()
{
    return this->evaluateNode(this->startLocation);
}

bool Puzzle::evaluateNode(int index)
{
    int value = this->nodes.at(index).getValue();
    vector<PuzzleNode> surroundingNodes = this->getSurroundingNodes(index);
    bool isValid = false;

    if (value == this->nodes.size())
    {
        return true;
    }

    for (auto currNode : surroundingNodes)
    {
        int currValue = currNode.getValue();
        if ((currValue - 1) == value)
        {
            isValid = this->evaluateNode(currNode.getId());
            break;
        }
    }

    return isValid;
}

vector<PuzzleNode> Puzzle::getSurroundingNodes(int index)
{
    vector<PuzzleNode> nodes;
    int maximum = this->nodes.size();
    int minimum = 0;

    bool onLeftSide = this->isOnLeftSide(index);
    bool onRightSide = this->isOnRightSide(index);

    if (index < maximum && !onRightSide)
    {
        PuzzleNode node = this->nodes.at(index + 1);
        nodes.push_back(node);
    }
    if (index > minimum && !onLeftSide)
    {
        PuzzleNode node = this->nodes.at(index - 1);
        nodes.push_back(node);
    }
    if ((index - 8) > minimum)
    {
        PuzzleNode node = this->nodes.at(index - 8);
        nodes.push_back(node);
    }
    if ((index + 8) < maximum)
    {
        PuzzleNode node = this->nodes.at(index + 8);
        nodes.push_back(node);
    }

    return nodes;
}

bool Puzzle::isOnLeftSide(int index)
{
    return (index % 8) == 0;
}

bool Puzzle::isOnRightSide(int index)
{
    return (((index + 1) % 8) == 0);
}

}


