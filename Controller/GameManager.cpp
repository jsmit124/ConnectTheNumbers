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
    this->puzzleManager = new PuzzleManager(DEFAULT_PUZZLE_COUNT);
    this->highScoreManager = new HighScoreManager();
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
}

bool GameManager::isLastPuzzle()
{
    return this->puzzleManager->isLastPuzzle();
}

void GameManager::moveToNextPuzzle()
{
    this->puzzleManager->moveToNextPuzzle();
}

void GameManager::resetCurrentPuzzle()
{
    Puzzle puzzle = this->reader.readPuzzleNumber(this->puzzleManager->getCurrentPuzzleNumber());
    this->puzzleManager->setCurrentPuzzle(puzzle);
    this->timeSpentOnPuzzle = 0;
}

void GameManager::loadPuzzles()
{
    vector<Puzzle> puzzles = this->reader.readAllPuzzles(DEFAULT_PUZZLE_COUNT);
    for (auto currPuzzle : puzzles)
    {
        this->puzzleManager->add(currPuzzle);
    }
}

void GameManager::loadSavedPuzzle()
{
    if (checkFileExists(SAVED_PUZZLE_PATH))
    {
        Puzzle puzzle = this->reader.readSavedPuzzle();
        this->puzzleManager->setCurrentPuzzle(puzzle);
    }
}

void GameManager::saveCurrentPuzzle()
{
    Puzzle puzzle = this->puzzleManager->getCurrentPuzzle();
    this->writer.savePuzzleToFile(puzzle, this->timeSpentOnPuzzle);
}

void GameManager::onTimerTick()
{
    this->timeSpentOnPuzzle++;
}

int GameManager::getCurrentPuzzleNumber()
{
    return this->puzzleManager->getCurrentPuzzleNumber();
}

int GameManager::getPuzzleNodeValue(int index)
{
    return this->puzzleManager->getCurrentPuzzle().getPuzzleNodeValue(index);
}

bool GameManager::isPuzzleNodeEditable(int index)
{
    return this->puzzleManager->getCurrentPuzzle().isPuzzleNodeEditable(index);
}

void GameManager::setPuzzleNodeValue(int value, int index)
{
    this->puzzleManager->getCurrentPuzzle().replace(value, index);
}

bool GameManager::evaluateCurrentPuzzle()
{
    return this->puzzleManager->evaluateCurrentPuzzle();
}

int GameManager::getTimeSpentOnPuzzle() const
{
    return this->timeSpentOnPuzzle;
}

vector<HighScoreEntry *> GameManager::getTopTenScoresByDuration()
{
    return this->highScoreManager->getTopTenByDuration();
}

void GameManager::recordGameCompletion(const string& name)
{
    this->highScoreManager->add(name, this->timeSpentOnPuzzle, this->puzzleManager->getCurrentPuzzleNumber());
}

}
