#include "MainGameWindow.h"

namespace view
{

MainGameWindow::MainGameWindow(int width, int height, const char* title) : Fl_Window(width, height, title)
{
    begin();

    this->gameManager = new GameManager();

    this->puzzleGrid = new PuzzleGrid (20, 0, this->gameManager);
    this->color(fl_darker(fl_darker(fl_darker(FL_DARK_BLUE))));

    this->addEvaluateButton();
    this->addResetButton();

    this->drawPuzzleNumberLabel();
    this->drawHighScoresLabel();
    this->drawTimerLabel();

    this->startGameTimer();

    end();
}

///Draws the puzzle number label
//
void MainGameWindow::drawPuzzleNumberLabel()
{
    string* labelText = this->getPuzzleNumberOutput();

    this->puzzleNumberLabel = new Fl_Box(85, 380, 175, 30, labelText->c_str());
    this->puzzleNumberLabel->box(FL_UP_BOX);
    this->puzzleNumberLabel->labelsize(14);
}

string* MainGameWindow::getPuzzleNumberOutput()
{
    // TODO can maybe move this to view formatter class
    string* labelText = new string("Puzzle Number: " + to_string(this->gameManager->getCurrentPuzzleNumber()) + "/" + to_string(this->gameManager->DEFAULT_PUZZLE_COUNT));
    return labelText;
}

void MainGameWindow::refreshBoard()
{
    string* labelText = this->getPuzzleNumberOutput();
    this->puzzleNumberLabel->label(labelText->c_str());

    this->puzzleGrid->resetBoard(this->gameManager);
}

///Adds the submit button to the screen
//
void MainGameWindow::addEvaluateButton()
{
    this->evaluateButton = new Fl_Button(221, 340, 110, 30, "EVALUATE");
    this->evaluateButton->callback(cbEvaluateButtonClicked, this);
}

///Adds the reset button to the screen
//
void MainGameWindow::addResetButton()
{
    this->resetButton = new Fl_Button(10, 340, 110, 30, "RESET");
    this->resetButton->callback(cbResetButtonClicked, this);
}

///Draws the high scores label
//
void MainGameWindow::drawHighScoresLabel()
{
    this->highScoresLabel = new Fl_Box(385, 10, 175, 30, "HIGH SCORES");
    this->highScoresLabel->box(FL_UP_BOX);
    this->highScoresLabel->labelsize(16);
}

/// Adds the timer label to the window.
void MainGameWindow::drawTimerLabel()
{
    this->gameTimerLabel = new Fl_Box(385, 300, 175, 30, nullptr);
    this->gameTimerLabel->box(FL_UP_BOX);
    this->gameTimerLabel->labelsize(16);
    this->refreshTimerLabel();
}

/// Callback for the evaulate button click
//
void MainGameWindow::cbEvaluateButtonClicked(Fl_Widget* widget, void* data)
{
    MainGameWindow* window = (MainGameWindow*)data;
    bool successfullySolved = window->getGameManager()->evaluateCurrentPuzzle();
    bool isLastPuzzle = window->getGameManager()->isLastPuzzle();

    if (successfullySolved && !isLastPuzzle)
    {
        window->getGameManager()->moveToNextPuzzle();
        window->refreshBoard();
    }
    else if (successfullySolved && isLastPuzzle)
    {
        fl_message("You have mastered all the puzzles... Congrats!");
    }
    else
    {
        fl_message("Uh oh.. the board is not correct. Try again!");
    }
}

/// Callback for the reset button click
//
void MainGameWindow::cbResetButtonClicked(Fl_Widget* widget, void* data)
{
    MainGameWindow* window = (MainGameWindow*)data;
    window->getGameManager()->resetCurrentPuzzle();
    window->refreshBoard();
}

GameManager* MainGameWindow::getGameManager()
{
    return this->gameManager;
}

MainGameWindow::~MainGameWindow()
{
    delete this->puzzleGrid;
    delete this->gameManager;
}

void MainGameWindow::startGameTimer()
{
    Fl::add_timeout(1.0, MainGameWindow::onTimerTick, this);
}

void MainGameWindow::onTimerTick(void *data)
{
    auto *window = (MainGameWindow*) data;
    window->gameManager->onTimerTick();
    window->refreshTimerLabel();

    Fl::repeat_timeout(1.0, MainGameWindow::onTimerTick, window);
}

void MainGameWindow::refreshTimerLabel()
{
    string formattedTimeSpent = "Time: " + formatDurationHoursSeconds(this->gameManager->getTimeSpentOnPuzzle());
    this->gameTimerLabel->copy_label(formattedTimeSpent.c_str());
}

}


