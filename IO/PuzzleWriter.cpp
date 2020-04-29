#include "PuzzleWriter.h"

namespace io
{

/// Puzzle Writer constructor
//
PuzzleWriter::PuzzleWriter()
{
}

/// Puzzle Writer destructor
//
PuzzleWriter::~PuzzleWriter()
{
}

/// Writes the [puzzle] to the specified [SAVE_PUZZLE_FILENAME] in a specific format
/// Line 1 = id
/// Line 2 = list of puzzle nodes separated by [DELIMETER]
//
// @precondition: none
// @postcondition: none
// @param puzzle: the puzzle to write out
//
void PuzzleWriter::savePuzzleToFile(Puzzle& puzzle)
{
    this->writePuzzleToFile(SAVE_PUZZLE_FILENAME, puzzle);
}

void PuzzleWriter::writePuzzleToFile(const string& filename, Puzzle& puzzle)
{
    ofstream outFile(filename);
    vector<PuzzleNode> nodes = puzzle.getNodes();

    outFile << puzzle.getId() << endl;
    for (int i = 0; i < nodes.size(); i++)
    {
        outFile << this->formatNode(nodes[i]);
    }

    outFile.close();
}

const string PuzzleWriter::formatNode(PuzzleNode& node)
{
    string formattedNode = to_string(node.getValue());

    if (node.getIsEditable())
    {
        formattedNode += EDITABLE_INDICATOR;
    }

    return formattedNode + DELIMETER;
}

}
