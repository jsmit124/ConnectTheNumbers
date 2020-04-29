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
using namespace std;

namespace io
{

/// Holds functionality to read puzzles from files
//
class PuzzleReader
{
    const string EDITABLE_INDICATOR = "x";
    const string DELIMETER = ",";
    const int PUZZLE_START_LOCATION = 1;

    private:
        void loadPuzzleNodes(Puzzle& puzzle, string& line);
        const PuzzleNode formatPuzzleNode(string nodeString);

    public:
        PuzzleReader();
        virtual ~PuzzleReader();

        const Puzzle readPuzzleFromFile(const string& filename);
};

}

#endif // PUZZLEREADER_H
