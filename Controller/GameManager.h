#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "../IO/HighScoreReader.h"
#include "../IO/HighScoreWriter.h"
#include "../IO/PuzzleReader.h"
#include "../IO/PuzzleWriter.h"
#include "../Model/PuzzleManager.h"
#include "../Model/HighScoreManager.h"
#include "../Utils/Utils.h"
#include <string>

using namespace model;
using namespace std;
using namespace io;

namespace controller
{

/// Manages the current Game state
//
class GameManager
{
    const string SAVED_PUZZLE_PATH = "Puzzles/puzzle_saved";
    const string SAVED_SCOREBOARD_PATH = "high_scores.csv";

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
        void saveCurrentPuzzle();
        vector<HighScoreEntry*> getTopTenScoresByDuration();
        void recordGameCompletion(const string& name);
        void saveHighScores();

        const int DEFAULT_PUZZLE_COUNT = 2;

        void onTimerTick();

        void loadHighScores();

        int getTimeSpentOnPuzzle() const;
};

}

#endif // GAMEMANAGER_H
