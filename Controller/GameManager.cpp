#include "GameManager.h"

namespace controller
{

/// The GameManager constructor
//
// @precondition: none
// @postcondition: none
//
GameManager::GameManager()
{
    this->puzzleManager = new PuzzleManager(MAX_PUZZLE_COUNT);
    this->highScoreManager = new HighScoreManager();
    this->playerSettings = new PlayerSettings();

    this->doesSavedFileExist = checkFileExists(SAVED_PUZZLE_PATH);
    this->isGamePaused = false;

    this->readPreviousSettings();
    this->initialize();
}

/// The GameManager destructor
//
// @postcondition: none
//
GameManager::~GameManager()
{
    delete this->puzzleManager;
    delete this->highScoreManager;
}

void GameManager::initialize()
{
    this->loadPuzzles();
    this->loadHighScores();
}

void GameManager::readPreviousSettings()
{
    if (checkFileExists(SAVED_SETTINGS_PATH))
    {
        *this->playerSettings = this->settingsReader.readSettingsFile(SAVED_SETTINGS_PATH);
    }
}

void GameManager::saveSettings()
{
    this->settingsWriter.writeSettingsToFile(SAVED_SETTINGS_PATH, *this->playerSettings);
}

PlayerSettings* GameManager::getSettings()
{
    return this->playerSettings;
}

bool GameManager::getDoesSavedFileExist()
{
    return this->doesSavedFileExist;
}

int GameManager::getTotalPuzzlesCount()
{
    return this->playerSettings->getDifficulty();
}

void GameManager::setDifficulty(Difficulty difficulty)
{
    this->playerSettings->setDifficulty(difficulty);
}

bool GameManager::isLastPuzzle()
{
    return this->puzzleManager->isLastPuzzle(this->playerSettings->getDifficulty());
}

bool GameManager::isFinalPuzzle()
{
    bool test = this->puzzleManager->isFinalPuzzle();
    return test;
}

void GameManager::moveToPuzzle(int puzzleId)
{
    if (puzzleId > this->playerSettings->getDifficulty())
    {
        this->playerSettings->setDifficulty(Difficulty::HARD);
    }

    Puzzle puzzle = this->puzzleReader.readPuzzleNumber(puzzleId);
    this->puzzleManager->setCurrentPuzzle(puzzle);
}

void GameManager::moveToNextPuzzle()
{
    if (this->puzzleManager->getCurrentPuzzleId() == this->playerSettings->getDifficulty())
    {
        this->playerSettings->moveToNextDifficulty();
    }

    this->puzzleManager->moveToNextPuzzle();
}

void GameManager::resetCurrentPuzzle()
{
    Puzzle newPuzzle = this->puzzleReader.readPuzzleNumber(this->puzzleManager->getCurrentPuzzleId());
    this->puzzleManager->setCurrentPuzzle(newPuzzle);
}

void GameManager::loadPuzzles()
{
    vector<Puzzle> puzzles = this->puzzleReader.readAllPuzzles(MAX_PUZZLE_COUNT);
    vector<Puzzle> solvedPuzzles = this->puzzleReader.readAllSolvedPuzzles(MAX_PUZZLE_COUNT);

    for (int i = 0; i < puzzles.size(); i++)
    {
        this->puzzleManager->add(puzzles.at(i), solvedPuzzles.at(i));
    }
}

int GameManager::getCurrentEndNodeIndex()
{
    return this->puzzleManager->getCurrentValidEndNodeIndex();
}

bool GameManager::foundFirstNode()
{
    return this->puzzleManager->getCurrentPuzzle().foundFirstNode();
}

void GameManager::loadSavedPuzzle()
{
    if (checkFileExists(SAVED_PUZZLE_PATH))
    {
        Puzzle puzzle = this->puzzleReader.readSavedPuzzle();
        this->puzzleManager->setCurrentPuzzle(puzzle);
    }
}

void GameManager::saveCurrentPuzzle()
{
    Puzzle puzzle = this->puzzleManager->getCurrentPuzzle();
    this->puzzleWriter.savePuzzleToFile(puzzle);
}

/// Called whenever the game timer loop fires.
/// \post this->getTimeSpentOnPuzzle() increments by 1
void GameManager::onTimerTick()
{
    if (!this->isGamePaused)
    {
        this->puzzleManager->getCurrentPuzzle().incrementTimeSpent();
    }
}

/// Increases the timer by 30 seconds. This is used to penalize those who try to get a hint.
///
/// @precondition none
/// @postcondition this->getTimeSpentOnPuzzle() == @prev + 30
void GameManager::increaseTimeBy30()
{
    if (!this->isGamePaused)
    {
        this->puzzleManager->getCurrentPuzzle().incrementTimeBy(TIME_INCREASE);
    }
}

//// Returns whether or not the game is paused.
///
/// @return whether or not the game is paused
bool GameManager::getIsGamePaused()
{
    return this->isGamePaused;
}

//// Sets whether or not the game is paused.
///
/// @param condition whether or not the game is paused
/// @post this->getIsGamePaused() == condition
void GameManager::setIsGamePaused(bool condition)
{
    this->isGamePaused = condition;
}

int GameManager::getCurrentPuzzleNumber()
{
    return this->puzzleManager->getCurrentPuzzleId();
}

int GameManager::getPuzzleNodeValue(int index)
{
    return this->puzzleManager->getCurrentPuzzle().getPuzzleNodeValue(index);
}

int GameManager::getNextNodeIndexOfCurrentPuzzle(int prevIndex)
{
    return this->puzzleManager->getNextNodeIndexOfCurrentPuzzle(prevIndex);
}

int GameManager::getCurrentPuzzleStartIndex()
{
    return this->puzzleManager->getCurrentPuzzle().getStartLocation();
}

bool GameManager::isPuzzleNodeEditable(int index)
{
    return this->puzzleManager->getCurrentPuzzle().isPuzzleNodeEditable(index);
}

int GameManager::getCurrentPuzzleSolvedNodeValue(int index)
{
    return this->puzzleManager->getCurrentPuzzleSolvedNodeValue(index);
}

int GameManager::getCurrentPuzzleSolvedNextNodeIndex(int prevIndex)
{
    return this->puzzleManager->getNextNodeOfSolvablePuzzle(prevIndex);
}

void GameManager::setPuzzleNodeValue(int value, int index)
{
    this->puzzleManager->getCurrentPuzzle().replace(value, index);
}

/// Evaluates the current puzzle and ensures that all rows are correctly filled in.
///
/// \return true if the puzzle was solved, false otherwise
bool GameManager::evaluateCurrentPuzzle()
{
    return this->puzzleManager->evaluateCurrentPuzzle();
}

/// Returns how much time the user has spent solving this puzzle.
///
/// \return the time the user has spent solving this puzzle
int GameManager::getTimeSpentOnPuzzle() const
{
    return this->puzzleManager->getCurrentPuzzle().getTimeSpent();
}

/// Returns the top ten scores by duration, ascending.
///
/// \return the top ten scores by duration
vector<HighScoreEntry *> GameManager::getTopTenScoresByDuration()
{
    return this->highScoreManager->getTopTenByDuration();
}

/// Returns the top ten scores by puzzle, in a two-level sort that sorts by puzzle and then duration.
///
/// \return the top ten scores by puzzle
vector<HighScoreEntry *> GameManager::getTopTenScoresByPuzzle()
{
    return this->highScoreManager->getTopTenByPuzzle();
}

/// Records that the game has been completed by a certain user and enters it into the scoreboard.
///
/// \param name the name of the player
/// \post Attempt is recorded in the scoreboard.
void GameManager::recordGameCompletion(const string& name)
{
    this->highScoreManager->add(name, this->puzzleManager->getCurrentPuzzle().getTimeSpent(),
            this->puzzleManager->getCurrentPuzzleId());
}

void GameManager::loadHighScores()
{
    if (checkFileExists(SAVED_SCOREBOARD_PATH))
    {
        HighScoreReader scoreReader;
        scoreReader.loadScores(this->highScoreManager, SAVED_SCOREBOARD_PATH);
    }
}

/// Saves all the high scores to disk.
///
/// @post The scoreboard will be saved to disk.
void GameManager::saveHighScores()
{
    HighScoreWriter scoreWriter;
    scoreWriter.writeHighScores(this->highScoreManager, SAVED_SCOREBOARD_PATH);
}

/// Clears all the high scores.
///
/// @post The high scoreboard shall be empty.
void GameManager::clearHighScores()
{
    this->highScoreManager->clear();
}

}
