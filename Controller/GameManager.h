#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "../IO/PuzzleReader.h"
#include "../IO/PuzzleWriter.h"
using namespace io;

#include "../Model/PuzzleManager.h"
using namespace model;

#include "../Utils/Utils.h"

#include <string>
using namespace std;

namespace controller
{

/// Manages the current Game state
//
class GameManager
{
    const string SAVED_PUZZLE_PATH = "Puzzles/puzzle_saved";
    const int DEFAULT_PUZZLE_COUNT = 12;

    private:
        PuzzleManager* puzzleManager;
        PuzzleReader reader;
        PuzzleWriter writer;

    public:
        GameManager();
        virtual ~GameManager();

        int getPuzzleNodeValue(int index);
        bool isPuzzleNodeEditable(int index);
        void initialize();
        void setPuzzleNodeValue(int value, int index);
        int getCurrentPuzzleNumber();
        void loadPuzzles();
        void loadSavedPuzzle();
        void saveCurrentPuzzle(const string& filename);
};

}

#endif // GAMEMANAGER_H
