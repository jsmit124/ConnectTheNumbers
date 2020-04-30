#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "../IO/PuzzleReader.h"
#include "../IO/PuzzleWriter.h"
using namespace io;

#include "../Model/PuzzleManager.h"
#include "../Model/HighScoreManager.h"
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

    private:
        PuzzleManager* puzzleManager;
        HighScoreManager* highScoreManager;
        PuzzleReader reader;
        PuzzleWriter writer;

    public:
        GameManager();
        virtual ~GameManager();

        bool isLastPuzzle();
        void resetCurrentPuzzle();
        void moveToNextPuzzle();
        bool evaluateCurrentPuzzle();
        int getPuzzleNodeValue(int index);
        bool isPuzzleNodeEditable(int index);
        void initialize();
        void setPuzzleNodeValue(int value, int index);
        int getCurrentPuzzleNumber();
        void loadPuzzles();
        void loadSavedPuzzle();
        void saveCurrentPuzzle(const string& filename);
        const int DEFAULT_PUZZLE_COUNT = 2;
};

}

#endif // GAMEMANAGER_H
