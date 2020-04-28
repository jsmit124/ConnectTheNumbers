#ifndef PUZZLEWRITER_H
#define PUZZLEWRITER_H

#include "../Model/Puzzle.h"
using namespace model;

#include <string>
using namespace std;

namespace io
{

class PuzzleWriter
{
    public:
        PuzzleWriter();
        virtual ~PuzzleWriter();

        void writePuzzleToFile(const string& filename, const Puzzle puzzle);
};

}

#endif // PUZZLEWRITER_H
