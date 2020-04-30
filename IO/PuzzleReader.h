#ifndef PUZZLEREADER_H
#define PUZZLEREADER_H

#include "../Model/Puzzle.h"
using namespace model;

#include "../Utils/Utils.h"
#include "../Utils/Exceptions.h"

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>

#define PUZZLES_DIRECTORY "Puzzles/"

using namespace std;

namespace io
{

enum PuzzleReaderState
{
    ID = 0,
    NODES = 1,
    DURATION = 2
};

/// Holds functionality to read puzzles from files
//
class PuzzleReader
{
    const string PUZZLE_INDICATOR = "puzzle_";
    const string SAVED_PUZZLE = "saved";
    const string EDITABLE_INDICATOR = "x";
    const string DELIMETER = ",";
    const int PUZZLE_START_LOCATION = 1;

    private:
        void loadPuzzleNodes(Puzzle& puzzle, string& line);
        const PuzzleNode formatPuzzleNode(string nodeString);
        Puzzle readPuzzleFromFile(const string& filename);

    public:
        PuzzleReader();
        virtual ~PuzzleReader();

        Puzzle readPuzzleNumber(int puzzleNumber);
        Puzzle readSavedPuzzle();
        vector<Puzzle> readAllPuzzles(int puzzleCount);
};

}

#endif // PUZZLEREADER_H
