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
    delete this->playerSettings;
    delete this->puzzleManager;
    delete this->highScoreManager;
}

  /// ///////// ///
 ///  GETTERS  ///
/// ///////// ///

/// Returns the top ten scores by duration, ascending.
//
// @return the top ten scores by duration
vector<HighScoreEntry *> GameManager::getTopTenScoresByDuration()
{
    return this->highScoreManager->getTopTenByDuration();
}

/// Returns the top ten scores by puzzle, in a two-level sort that sorts by puzzle and then duration.
//
// @return the top ten scores by puzzle
vector<HighScoreEntry *> GameManager::getTopTenScoresByPuzzle()
{
    return this->highScoreManager->getTopTenByPuzzle();
}

/// Evaluates the current puzzle and ensures that all rows are correctly filled in.
//
// @return true if the puzzle was solved, false otherwise
bool GameManager::evaluateCurrentPuzzle()
{
    return this->puzzleManager->evaluateCurrentPuzzle();
}

/// Returns if the saved file exists (needed to toggle load save)
//
// @return true if the saved file exist; otherwise false
bool GameManager::getDoesSavedFileExist()
{
    return this->doesSavedFileExist;
}

/// Returns if this is the final puzzle
//
// @return if the current puzzle is the final
bool GameManager::isFinalPuzzle()
{
    return this->puzzleManager->isFinalPuzzle();
}

/// Returns whether or not the game is paused.
//
// @return whether or not the game is paused
bool GameManager::getIsGamePaused()
{
    return this->isGamePaused;
}

/// Returns if is last puzzle of the current difficulty
//
// @return true if is last puzzle of difficulty; otherwise false
bool GameManager::isLastPuzzle()
{
    return this->puzzleManager->isLastPuzzle(this->playerSettings->getDifficulty());
}

/// Returns whether the first node has been found yet
//
// @return whether the first node has been found
bool GameManager::foundFirstNode()
{
    return this->puzzleManager->getCurrentPuzzle().foundFirstNode();
}

/// Returns if the puzzle node at [index] is editable
//
// @pre: none
// @post: none
// @param index: the index of node
// @return returns if the puzzle node is editable
bool GameManager::isPuzzleNodeEditable(int index)
{
    return this->puzzleManager->getCurrentPuzzle().isPuzzleNodeEditable(index);
}

/// Returns the puzzle node value at [index]
//
// @pre: none
// @post: none
// @param index: the index to get value from
// @return the puzzle node value at [index]
int GameManager::getPuzzleNodeValue(int index)
{
    return this->puzzleManager->getCurrentPuzzle().getPuzzleNodeValue(index);
}

/// Returns the total puzzle count
//
// @return the total puzzle count
int GameManager::getTotalPuzzlesCount()
{
    return this->playerSettings->getDifficulty();
}

/// Returns the current puzzle #
//
// @pre: none
// @post: none
// @return the current puzzle #
int GameManager::getCurrentPuzzleNumber()
{
    return this->puzzleManager->getCurrentPuzzleId();
}

/// Returns how much time the user has spent solving this puzzle.
//
// @return the time the user has spent solving this puzzle
int GameManager::getTimeSpentOnPuzzle() const
{
    return this->puzzleManager->getCurrentPuzzle().getTimeSpent();
}

/// Returns the current end node index (needed for evaluation)
//
// @return the current end node index
int GameManager::getCurrentEndNodeIndex()
{
    return this->puzzleManager->getCurrentValidEndNodeIndex();
}

/// Gets the next node index of current puzzle
//
// @pre: none
// @post: none
// @param prevIndex: the prev index
// @return the next node index of current puzzle
int GameManager::getNextNodeIndexOfCurrentPuzzle(int prevIndex)
{
    return this->puzzleManager->getNextNodeIndexOfCurrentPuzzle(prevIndex);
}

/// Returns the current puzzle start index
//
// @pre: none
// @post: none
// @return the current puzzle start index
int GameManager::getCurrentPuzzleStartIndex()
{
    return this->puzzleManager->getCurrentPuzzle().getStartLocation();
}

/// Gets current puzzle solved node value at [index]
//
// @param index: the index of node
// @pre: none
// @post: none
// @return the current puzzle solved node value
int GameManager::getCurrentPuzzleSolvedNodeValue(int index)
{
    return this->puzzleManager->getCurrentPuzzleSolvedNodeValue(index);
}

/// Gets the current puzzles solved next node index.
//
// @param prevIndex: the prev index
// @pre: none
// @return current puzzles solved next node index.
int GameManager::getCurrentPuzzleSolvedNextNodeIndex(int prevIndex)
{
    return this->puzzleManager->getNextNodeOfSolvablePuzzle(prevIndex);
}

/// Returns the settings
//
// @return the current settings
PlayerSettings* GameManager::getSettings()
{
    return this->playerSettings;
}

  /// ///////// ///
 ///  SETTERS  ///
/// ///////// ///

/// Sets whether or not the game is paused.
//
// @param condition whether or not the game is paused
// @post this->getIsGamePaused() == condition
void GameManager::setIsGamePaused(bool condition)
{
    this->isGamePaused = condition;
}

/// Sets the difficulty to [difficulty]
//
// @post: settings->getDifficulty = difficulty
// @param difficulty: the difficulty to set
void GameManager::setDifficulty(Difficulty difficulty)
{
    this->playerSettings->setDifficulty(difficulty);
}

/// Moves to the specified [puzzleId]
//
// @pre: none
// @post: currentPuzzle() == puzzleId
// @param puzzleId: the id to change to
void GameManager::moveToPuzzle(int puzzleId)
{
    if (puzzleId > this->playerSettings->getDifficulty())
    {
        this->playerSettings->setDifficulty(Difficulty::HARD);
    }

    Puzzle puzzle = this->puzzleReader.readPuzzleNumber(puzzleId);
    this->puzzleManager->setCurrentPuzzle(puzzle);
}

/// Resets the game to puzzle 1 and resets all puzzles to original values.
//
// @pre: none
// @post: this->puzzleManager() == new puzzles
void GameManager::resetGame()
{
    vector<Puzzle> puzzles = this->puzzleReader.readAllPuzzles(MAX_PUZZLE_COUNT);

    for (int i = 0; i < puzzles.size(); i++)
    {
        this->puzzleManager->setPuzzleAt(puzzles.at(i), i);
    }

    this->puzzleManager->resetCurrentPuzzleIndex();
}

/// Sets the puzzle node value to [value]
//
// @param value: value to set
// @param index: index of node
// @pre: none
// @post: none
void GameManager::setPuzzleNodeValue(int value, int index)
{
    this->puzzleManager->getCurrentPuzzle().replace(value, index);
}

/// Resets the current puzzle
//
// @pre: none
// @post: the current puzzle is reloaded and set
void GameManager::resetCurrentPuzzle()
{
    Puzzle newPuzzle = this->puzzleReader.readPuzzleNumber(this->puzzleManager->getCurrentPuzzleId());
    this->puzzleManager->setCurrentPuzzle(newPuzzle);
}

  /// ///////// ///
 ///  ACTIONS  ///
/// ///////// ///

/// Increases the timer by 30 seconds. This is used to penalize those who try to get a hint.
//
// @precondition none
// @postcondition this->getTimeSpentOnPuzzle() == @prev + 30
void GameManager::increaseTimeBy30()
{
    if (!this->isGamePaused)
    {
        this->puzzleManager->getCurrentPuzzle().incrementTimeBy(TIME_INCREASE);
    }
}

/// Saves the current settings to a file
//
// @post: saves the current settings to a file
void GameManager::saveSettings()
{
    this->settingsWriter.writeSettingsToFile(SAVED_SETTINGS_PATH, *this->playerSettings);
}

/// Called whenever the game timer loop fires.
//
// @post this->getTimeSpentOnPuzzle() increments by 1
void GameManager::onTimerTick()
{
    if (!this->isGamePaused)
    {
        this->puzzleManager->getCurrentPuzzle().incrementTimeSpent();
    }
}

/// Records that the game has been completed by a certain user and enters it into the scoreboard.
//
// @postcondition: Attempt is recorded in the scoreboard.
// @param name: the name of the player
void GameManager::recordGameCompletion(const string& name)
{
    this->highScoreManager->add(name, this->puzzleManager->getCurrentPuzzle().getTimeSpent(),
            this->puzzleManager->getCurrentPuzzleId());
}

/// Moves to the next puzzle in the collection
//
// @pre: none
// @post: this->puzzleManager()->getCurrentPuzzleId()++
void GameManager::moveToNextPuzzle()
{
    if (this->puzzleManager->getCurrentPuzzleId() == this->playerSettings->getDifficulty())
    {
        this->playerSettings->moveToNextDifficulty();
    }

    this->puzzleManager->moveToNextPuzzle();
}

/// Loads the puzzle prev saved and sets it as the current
//
// @pre: none
// @post: this->puzzleManager->getCurrentPuzzle() == read puzzle
void GameManager::loadSavedPuzzle()
{
    if (checkFileExists(SAVED_PUZZLE_PATH))
    {
        Puzzle puzzle = this->puzzleReader.readSavedPuzzle();
        this->puzzleManager->setCurrentPuzzle(puzzle);
    }
}

/// Loads all the puzzles (solved/unsolved) and adds them to puzzle manager.
//
// @pre: none
// @post: the->puzzleManager = all puzzles
void GameManager::loadPuzzles()
{
    vector<Puzzle> puzzles = this->puzzleReader.readAllPuzzles(MAX_PUZZLE_COUNT);
    vector<Puzzle> solvedPuzzles = this->puzzleReader.readAllSolvedPuzzles(MAX_PUZZLE_COUNT);

    for (int i = 0; i < puzzles.size(); i++)
    {
        this->puzzleManager->add(puzzles.at(i), solvedPuzzles.at(i));
    }
}

/// Saves all the high scores to disk.
//
// @post: The scoreboard will be saved to disk.
void GameManager::saveHighScores()
{
    HighScoreWriter scoreWriter;
    scoreWriter.writeHighScores(this->highScoreManager, SAVED_SCOREBOARD_PATH);
}

/// Saves the current puzzle to a file
//
// @pre: none
// @post: none
void GameManager::saveCurrentPuzzle()
{
    Puzzle puzzle = this->puzzleManager->getCurrentPuzzle();
    this->puzzleWriter.savePuzzleToFile(puzzle);
}

  /// //////////////// ///
 ///  PRIVATE HELPERS ///
/// //////////////// ///

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

void GameManager::loadHighScores()
{
    if (checkFileExists(SAVED_SCOREBOARD_PATH))
    {
        HighScoreReader scoreReader;
        scoreReader.loadScores(this->highScoreManager, SAVED_SCOREBOARD_PATH);
    }
}

}
