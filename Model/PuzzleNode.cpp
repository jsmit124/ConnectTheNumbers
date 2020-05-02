#include "PuzzleNode.h"

namespace model
{

/// Puzzle node constructor
//
// @precondition: none
// @postcondition: this->value = 0
//                this->isEditable = false
//
PuzzleNode::PuzzleNode()
{
    this->value = 0;
    this->isEditable = false;
}

/// Puzzle node destructor
//
// @postcondition: none
//
PuzzleNode::~PuzzleNode()
{
}

/// Returns the value
//
// @precondition: none
// @postcondition: none
// @return the value
//
int PuzzleNode::getValue()
{
    return this->value;
}

/// Returns if the node isEditable
//
// @precondition: none
// @postcondition: none
// @return true if editable; otherwise false
//
bool PuzzleNode::getIsEditable()
{
    return this->isEditable;
}

/// Sets the node value to [valueToSet]
//
// @precondition: none
// @postcondition: this->value = valueToSet
// @param valueToSet: the value to set
//
void PuzzleNode::setValue(int valueToSet)
{
    this->value = valueToSet;
}

/// Sets isEditable to [condition]
//
// @precondition: none
// @postcondition: this->isEditable = condition
// @param condition: the condition
//
void PuzzleNode::setIsEditable(bool condition)
{
    this->isEditable = condition;
}

/// Sets the id of current node
// @param idToSet: the id to set to
// @post: this->id = idToSet
void PuzzleNode::setId(int idToSet)
{
    this->id = idToSet;
}

/// Returns the id
// @return the id
int PuzzleNode::getId()
{
    return this->id;
}

}


