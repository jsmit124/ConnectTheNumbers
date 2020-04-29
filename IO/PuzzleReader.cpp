#include "PuzzleReader.h"

namespace io
{

/// Puzzle Reader constructor
//
PuzzleReader::PuzzleReader()
{
}

/// Puzzle Reader destructor
//
PuzzleReader::~PuzzleReader()
{
}

/// Reads the formatted puzzle from the specified [filename]
//
// @precondition: none
// @postcondition: none
// @param filename: the name of the file containing the puzzle
// @return the puzzle read from the file
//
const Puzzle PuzzleReader::readPuzzleFromFile(const string& filename)
{
    ifstream inFile;
    inFile.open(filename);

    if (!inFile)
    {
        throw FileErrorException();
    }

    Puzzle puzzle;
    bool readId = false;
    string line;

    while (getline(inFile, line))
    {
        if (!readId)
        {
            puzzle.setId(stoi(line));
            readId = true;
        }
        else
        {
            this->loadPuzzleNodes(puzzle, line);
        }
    }

    return puzzle;
}

void PuzzleReader::loadPuzzleNodes(Puzzle& puzzle, string& line)
{
    vector<string> nodes = split(line, DELIMETER);

    for (int i = 0; i < nodes.size(); i++)
    {
        PuzzleNode node = this->formatPuzzleNode(nodes[i]);
        puzzle.add(node);

        if (node.getValue() == PUZZLE_START_LOCATION)
        {
            puzzle.setStartLocation(i);
        }
    }
}

const PuzzleNode PuzzleReader::formatPuzzleNode(string nodeString)
{
    PuzzleNode node;
    int editableValIndex = nodeString.find(EDITABLE_INDICATOR);
    bool isEditable = editableValIndex > -1;

    node.setIsEditable(isEditable);
    node.setValue(stoi(filterNumbers(nodeString)));
    return node;
}

}
