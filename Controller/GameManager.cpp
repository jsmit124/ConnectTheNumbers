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

void GameManager::moveToNextPuzzle()
{
    this->puzzleManager->moveToNextPuzzle();
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

void GameManager::saveCurrentPuzzle(const string& filename)
{
    Puzzle puzzle = this->puzzleManager->getCurrentPuzzle();
    this->writer.savePuzzleToFile(puzzle);
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

}
