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
#include "../Enum/Difficulty.h"
#include "../Settings/PlayerSettings.h"
#include "../IO/SettingsReader.h"
#include "../IO/SettingsWriter.h"

using namespace settings;
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
    const string SAVED_SCOREBOARD_PATH = "Storage/high_scores.csv";
    const string SAVED_SETTINGS_PATH = "Storage/prev_settings";
    const int MAX_PUZZLE_COUNT = 12;
    const int TIME_INCREASE = 30;

    private:
        PuzzleManager* puzzleManager;
        HighScoreManager* highScoreManager;
        PuzzleReader puzzleReader;
        PuzzleWriter puzzleWriter;
        SettingsWriter settingsWriter;
        SettingsReader settingsReader;
        PlayerSettings* playerSettings;

        void readPreviousSettings();
        bool doesSavedFileExist;
        bool isGamePaused;

    public:
        GameManager();
        virtual ~GameManager();

        void increaseTimeBy30();
        bool getIsGamePaused();
        void setIsGamePaused(bool condition);
        void saveSettings();
        PlayerSettings* getSettings();
        int getTotalPuzzlesCount();
        void setDifficulty(Difficulty difficulty);
        bool getDoesSavedFileExist();
        int getCurrentEndNodeIndex();
        int getNextNodeIndexOfCurrentPuzzle(int prevIndex);
        int getCurrentPuzzleSolvedNextNodeIndex(int prevIndex);
        int getCurrentPuzzleSolvedNodeValue(int index);
        int getCurrentPuzzleStartIndex();
        bool isLastPuzzle();
        bool isFinalPuzzle();
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
        vector<HighScoreEntry*> getTopTenScoresByPuzzle();
        void recordGameCompletion(const string& name);
        void saveHighScores();

        void onTimerTick();

        void loadHighScores();

        int getTimeSpentOnPuzzle() const;

        void moveToPuzzle(int puzzleId);

        void clearHighScores();
};

}

#endif // GAMEMANAGER_H
