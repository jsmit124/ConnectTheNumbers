#ifndef PUZZLEREADER_H
#define PUZZLEREADER_H

#include "../Model/Puzzle.h"
using namespace model;

#include <string>
using namespace std;

namespace io
{

class PuzzleReader
{
    public:
        PuzzleReader();
        virtual ~PuzzleReader();

        Puzzle readPuzzleFromFile(const string& filename);
};

}

#endif // PUZZLEREADER_H
