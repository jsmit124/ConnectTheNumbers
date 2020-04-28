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
    this->nodes = new vector<PuzzleNode>();
}

/// Puzzle destructor
//
// @postcondition: this->nodes.size() == 0
//                 this->nodes == nullptr
//
Puzzle::~Puzzle()
{
    delete this->nodes;
    this->nodes = nullptr;
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
void Puzzle::add(const PuzzleNode& node)
{
    this->nodes->push_back(node);
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
    PuzzleNode node = this->nodes->at(index);
    node.setValue(value);
}

}


