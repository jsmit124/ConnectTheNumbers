#ifndef PUZZLENODE_H
#define PUZZLENODE_H

namespace model
{

/// Holds functionality for a single Puzzle node
//
class PuzzleNode
{
    private:
        unsigned int value;
        bool isEditable;

    public:
        PuzzleNode();
        virtual ~PuzzleNode();

        unsigned int getValue();
        bool getIsEditable();

        void setValue(unsigned int valueToSet);
        void setIsEditable(bool condition);
};

}

#endif // PUZZLENODE_H
