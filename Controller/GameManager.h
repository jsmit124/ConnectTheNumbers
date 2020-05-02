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
    /// Members
    //
    PuzzleManager* puzzleManager;
    HighScoreManager* highScoreManager;
    PuzzleReader puzzleReader;
    PuzzleWriter puzzleWriter;
    SettingsWriter settingsWriter;
    SettingsReader settingsReader;
    PlayerSettings* playerSettings;

    /// Private Helpers
    //
    void readPreviousSettings();
    void initialize();
    void loadPuzzles();
    void loadHighScores();
    bool doesSavedFileExist;
    bool isGamePaused;

public:
    GameManager();
    virtual ~GameManager();

    /// Getters
    //
    bool getIsGamePaused();
    bool getDoesSavedFileExist();
    bool foundFirstNode();
    bool isLastPuzzle();
    bool isFinalPuzzle();
    bool isPuzzleNodeEditable(int index);
    int getTimeSpentOnPuzzle() const;
    bool evaluateCurrentPuzzle();

    int getTotalPuzzlesCount();
    int getCurrentEndNodeIndex();
    int getNextNodeIndexOfCurrentPuzzle(int prevIndex);
    int getCurrentPuzzleSolvedNextNodeIndex(int prevIndex);
    int getCurrentPuzzleSolvedNodeValue(int index);
    int getCurrentPuzzleStartIndex();
    int getPuzzleNodeValue(int index);
    int getCurrentPuzzleNumber();
    PlayerSettings* getSettings();

    vector<HighScoreEntry*> getTopTenScoresByDuration();
    vector<HighScoreEntry*> getTopTenScoresByPuzzle();

    /// Setters
    //
    void setIsGamePaused(bool condition);
    void setDifficulty(Difficulty difficulty);
    void setPuzzleNodeValue(int value, int index);

    /// Actions
    //
    void resetGame();
    void saveSettings();

    void resetCurrentPuzzle();
    void moveToNextPuzzle();
    void loadSavedPuzzle();
    void saveCurrentPuzzle();
    void moveToPuzzle(int puzzleId);

    void recordGameCompletion(const string& name);
    void increaseTimeBy30();
    void saveHighScores();
    void clearHighScores();
    void onTimerTick();
};

}

#endif // GAMEMANAGER_H
