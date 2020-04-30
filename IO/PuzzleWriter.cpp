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
/// Line 3 = the seconds spent solving the puzzle so far
//
// @precondition: none
// @postcondition: none
// @param puzzle: the puzzle to write out
//
void PuzzleWriter::savePuzzleToFile(Puzzle& puzzle)
{
    this->writePuzzleToFile(PUZZLES_DIRECTORY + SAVE_PUZZLE_FILENAME, puzzle);
}

void PuzzleWriter::writePuzzleToFile(const string& filename, Puzzle& puzzle)
{
    ofstream outFile(filename);
    vector<PuzzleNode> nodes = puzzle.getNodes();

    outFile << puzzle.getId() << endl;
    for (auto & node : nodes)
    {
        outFile << this->formatNode(node);
    }

    if (puzzle.getTimeSpent() > 0)
    {
        outFile << endl << puzzle.getTimeSpent() << endl;
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
