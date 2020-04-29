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
}

/// The GameManager destructor
//
// @postcondition: none
//
GameManager::~GameManager()
{
    delete this->puzzleManager;
    this->puzzleManager = nullptr;
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

}
