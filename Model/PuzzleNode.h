#ifndef PUZZLENODE_H
#define PUZZLENODE_H

namespace model
{

/// Holds functionality for a single Puzzle node
//
class PuzzleNode
{

private:
    int id;
    int value;
    bool isEditable;

public:
    PuzzleNode();
    virtual ~PuzzleNode();

    int getId();
    int getValue();
    bool getIsEditable();

    void setId(int idToSet);
    void setValue(int valueToSet);
    void setIsEditable(bool condition);
};

}

#endif // PUZZLENODE_H
