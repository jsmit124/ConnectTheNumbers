#include "PuzzleReader.h"

namespace io
{

PuzzleReader::PuzzleReader() = default;
PuzzleReader::~PuzzleReader() = default;

/// Reads the formatted puzzle from the specified [filename]
/// Line 1 = id
/// Line 2 = list of puzzle nodes separated by [DELIMETER]
/// Line 3 (saved) = prev duration
//
// @precondition: none
// @postcondition: none
// @param filename: the name of the file containing the puzzle
// @return the puzzle read from the file
// @throws FileErrorException if file doesn't exist
Puzzle PuzzleReader::readPuzzleFromFile(const string& filename)
{
    ifstream inFile(filename);

    if (!inFile.good())
    {
        throw FileErrorException();
    }

    Puzzle puzzle;
    PuzzleReaderState state = ID;
    string line;

    while (getline(inFile, line))
    {
        switch (state)
        {
        case ID:
            puzzle.setId(stoi(line));
            state = NODES;
            break;
        case NODES:
            this->loadPuzzleNodes(puzzle, line);
            state = DURATION;
            break;
        case DURATION:
            puzzle.setTimeSpent(stoi(line));
            break;
        }
    }

    return puzzle;
}

/// Reads the puzzle based on the specific [puzzleNumber]
//
// @param puzzleNumber: the puzzle number to get
// @return puzzle of the specified puzzlenumber
Puzzle PuzzleReader::readPuzzleNumber(int puzzleNumber)
{
    string filePath = PUZZLES_DIRECTORY + PUZZLE_INDICATOR + to_string(puzzleNumber);
    return this->readPuzzleFromFile(filePath);
}

/// Returns the saved puzzle
//
// @return the saved puzzle
Puzzle PuzzleReader::readSavedPuzzle()
{
    string filePath = PUZZLES_DIRECTORY + PUZZLE_INDICATOR + SAVED_PUZZLE;
    return this->readPuzzleFromFile(filePath);
}

/// Reads all solved puzzles up to count [puzzleCount] and adds them to list
//
// @pre: none
// @post: none
// @param puzzleCount: the # of puzzles to read
// @return the list of solved puzzles
vector<Puzzle> PuzzleReader::readAllSolvedPuzzles(int puzzleCount)
{
    vector<Puzzle> puzzles;
    puzzles.reserve(puzzleCount);

    for (int i = 1; i <= puzzleCount; i++)
    {
        string filePath = PUZZLES_DIRECTORY + PUZZLE_INDICATOR + to_string(i) + SOLVED_INDICATOR;
        puzzles.push_back(this->readPuzzleFromFile(filePath));
    }

    return puzzles;
}

/// Reads all (unsolved) puzzles up to count [puzzleCount] and adds them to list
//
// @pre: none
// @post: none
// @param puzzleCount: the total puzzle count
// @return the list of unsolved puzzles
vector<Puzzle> PuzzleReader::readAllPuzzles(int puzzleCount)
{
    vector<Puzzle> puzzles;
    puzzles.reserve(puzzleCount);

    for (int i = 1; i <= puzzleCount; i++)
    {
        puzzles.push_back(this->readPuzzleNumber(i));
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
