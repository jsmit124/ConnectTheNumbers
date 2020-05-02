#include "Puzzle.h"

namespace model
{

/// Constructor for a Puzzle
//
// @precondition: none
// @postcondition: this->nodes.size() == 0 && this->timeSpent == 0
//
Puzzle::Puzzle()
{
    this->timeSpent = 0;
    this->startLocation = -1;
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

/// Returns the puzzle node value based on [index]
//
// @param index: index to get value from
// @return the node value at index
int Puzzle::getPuzzleNodeValue(int index)
{
    return this->nodes.at(index).getValue();
}

/// Returns if the puzzle node at [index] is editable
//
// @param index: the index to check
// @return true if the node is editable
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

    if (value == 1)
    {
        this->startLocation = index;
    }

    node.setValue(value);
}

/// Returns the start location.
// @return the start location
int Puzzle::getStartLocation()
{
    return this->startLocation;
}

/// Function to start recursive call to evaluate each node starting
/// at this->startLocation. Returns true if evaluated correctly.
// @return true if passes evaluation; otherwise false
bool Puzzle::evaluate()
{
    return this->evaluateNode(this->startLocation);
}

/// Recursive function to evaluate node.
/// Calls itself if next index contains valid value (1 greater than prev)
// @return true if evaluation of node is good; otherwise false
bool Puzzle::evaluateNode(int index)
{
    int value = this->nodes.at(index).getValue();
    bool isValid = false;

    if (value == this->nodes.size())
    {
        return true;
    }

    int nextIndex = this->getNextNodeIndex(index);

    if (nextIndex > -1)
    {
        isValid = this->evaluateNode(this->nodes.at(nextIndex).getId());
    }

    return isValid;
}

/// Returns the current node index based on [prevIndex]
// @param prevIndex: the prev index
// @return the next node index based on prevIndex
int Puzzle::getNextNodeIndex(int prevIndex)
{
    int nextNodeIndex = -1;

    int maximum = this->nodes.size();
    int minimum = 0;

    bool onLeftSide = this->isOnLeftSide(prevIndex);
    bool onRightSide = this->isOnRightSide(prevIndex);

    if (prevIndex < maximum && !onRightSide)
    {
        int rightIndex = prevIndex + 1;
        this->checkIfNextNode(prevIndex, rightIndex, nextNodeIndex);
    }
    if (prevIndex > minimum && !onLeftSide)
    {
        int leftIndex = prevIndex - 1;
        this->checkIfNextNode(prevIndex, leftIndex, nextNodeIndex);
    }
    if ((prevIndex - PUZZLE_WIDTH) >= minimum)
    {
        int topIndex = prevIndex - PUZZLE_WIDTH;
        this->checkIfNextNode(prevIndex, topIndex, nextNodeIndex);
    }
    if ((prevIndex + PUZZLE_WIDTH) < maximum)
    {
        int bottomIndex = prevIndex + PUZZLE_WIDTH;
        this->checkIfNextNode(prevIndex, bottomIndex, nextNodeIndex);
    }

    return nextNodeIndex;
}

/// Returns if the first node has been found (node w/ value of 1)
//
// @return true if first node is found; otherwise false
bool Puzzle::foundFirstNode()
{
    if (this->startLocation < 0)
    {
        return false;
    }
    return this->nodes.at(this->startLocation).getValue() == 1;
}

/// Returns the current end node index (node last in guessed path)
// @return the last node in the guessed path index
int Puzzle::getCurrentEndNodeIndex()
{
    int currIndex = this->startLocation;
    bool foundEnd = false;
    int nextIndex = -1;

    while (!foundEnd)
    {
        if (currIndex > -1)
        {
            nextIndex = this->getNextNodeIndex(currIndex);
        }

        if (nextIndex < 0)
        {
            foundEnd = true;
        }
        else
        {
            currIndex = nextIndex;
        }
    }

    return currIndex;
}

/// Returns the time spent solving puzzle
// @return the time spent
int Puzzle::getTimeSpent() const
{
    return this->timeSpent;
}

/// Sets the time spent to [timeSpent]
// @param timeSpent: the time spent on puzzle
// @post: this->timeSpent = timeSpent
void Puzzle::setTimeSpent(int timeSpent)
{
    this->timeSpent = timeSpent;
}

/// Increments the time by [timeIncrease]
// @param timeIncrease: increase time by timeIncrease
// @post: increments the time by [timeIncrease]
void Puzzle::incrementTimeBy(int timeIncrease)
{
    this->timeSpent += timeIncrease;
}

/// Increments timeSpent by one
// @post: this->timeSpent++
void Puzzle::incrementTimeSpent()
{
    this->timeSpent++;
}

void Puzzle::checkIfNextNode(int prevIndex, int nextIndex, int& nextNodeIndex)
{
    bool isValid = this->isNextNodeValid(prevIndex, nextIndex);

    if (isValid)
    {
        nextNodeIndex = nextIndex;
    }
}

bool Puzzle::isNextNodeValid(int prevIndex, int nextIndex)
{
    int prevValue = this->nodes.at(prevIndex).getValue();
    int nextValue = this->nodes.at(nextIndex).getValue();

    return (nextValue - 1) == prevValue;
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


