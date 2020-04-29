#ifndef PUZZLEWRITER_H
#define PUZZLEWRITER_H

#include "../Model/Puzzle.h"
#include "../Model/PuzzleNode.h"
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

    public:
        PuzzleWriter();
        virtual ~PuzzleWriter();

        void writePuzzleToFile(const string& filename, Puzzle& puzzle);
        const string formatNode(PuzzleNode& node);
};

}

#endif // PUZZLEWRITER_H
