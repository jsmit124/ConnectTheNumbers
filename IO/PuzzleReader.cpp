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
/// Line 1 = id
/// Line 2 = list of puzzle nodes separated by [DELIMETER]
//
// @precondition: none
// @postcondition: none
// @param filename: the name of the file containing the puzzle
// @return the puzzle read from the file
//
Puzzle PuzzleReader::readPuzzleFromFile(const string& filename)
{
    ifstream inFile(filename);

    if (!inFile.good())
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

Puzzle PuzzleReader::readSavedPuzzle()
{
    string filePath = PUZZLES_DIRECTORY + PUZZLE_INDICATOR + SAVED_PUZZLE;
    return this->readPuzzleFromFile(filePath);
}

vector<Puzzle> PuzzleReader::readAllPuzzles(int puzzleCount)
{
    vector<Puzzle> puzzles;
    puzzles.reserve(puzzleCount);

    for (int i = 1; i <= puzzleCount; i++)
    {
        string filePath = PUZZLES_DIRECTORY + PUZZLE_INDICATOR + to_string(i);
        Puzzle puzzle = this->readPuzzleFromFile(filePath);
        puzzles.push_back(puzzle);
    }

    return puzzles;
}

void PuzzleReader::loadPuzzleNodes(Puzzle& puzzle, string& line)
{
    vector<string> nodes = split(line, DELIMETER);

    for (int i = 0; i < nodes.size(); i++)
    {
        PuzzleNode node = this->formatPuzzleNode(nodes[i]);
        node.setId(i);
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
