#ifndef PUZZLEWRITER_H
#define PUZZLEWRITER_H

#include "../Model/Puzzle.h"
#include "../Model/PuzzleNode.h"
#include "./PuzzleReader.h"

using namespace model;

#include <string>
#include <fstream>
#include <iostream>
using namespace std;

namespace io
{

/// Holds functionality to write a puzzle to a file
//
class PuzzleWriter
{
    const string EDITABLE_INDICATOR = "x";
    const string DELIMETER = ",";
    const string SAVE_PUZZLE_FILENAME = "puzzle_saved";

    private:
        const string formatNode(PuzzleNode& node);
        void writePuzzleToFile(const string& filename, Puzzle& puzzle, int timeSpent);

    public:
        PuzzleWriter();
        virtual ~PuzzleWriter();

        void savePuzzleToFile(Puzzle& puzzle, int timeSpent);
};

}

#endif // PUZZLEWRITER_H
