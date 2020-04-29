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
void Puzzle::replace(unsigned int value, int index)
{
    PuzzleNode node = this->nodes.at(index);
    node.setValue(value);
}

}


