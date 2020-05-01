#include "MainGameWindow.h"

namespace view
{

MainGameWindow::MainGameWindow(int width, int height, const char* title) : Fl_Window(width, height, title)
{
    this->gameManager = new GameManager();
    this->initialize();

    begin();

    PlayerSettings* settings = this->gameManager->getSettings();
    this->puzzleGrid = new PuzzleGrid (20, 0, this->gameManager, settings->getButtonColor(), settings->getTextColor());
    this->color(settings->getBackgroundColor());

    this->addEvaluateButton();
    this->addResetButton();
    this->addPauseButton();
    this->addViewHighScoresButton();

    this->drawPuzzleNumberLabel();
    this->drawTimerLabel();

    this->startGameTimer();
    this->callback(MainGameWindow::cbOnWindowClose, this);

    end();
}

/// Initializes the game and gives player opportunity to adjust settings
//
void MainGameWindow::initialize()
{
    PlayerSettings* settings = this->gameManager->getSettings();
    this->settingsWindow = new InitialSettingsWindow();

    this->settingsWindow->setColorToAllButtons(settings->getButtonColor());
    this->settingsWindow->setBackgroundColor(settings->getBackgroundColor());
    this->settingsWindow->setTextColorToAllButtons(settings->getTextColor());

    this->settingsWindow->set_modal();
    this->settingsWindow->show();
    this->settingsWindow->setSavedButtonState(this->gameManager->getDoesSavedFileExist());

    while (this->settingsWindow->shown())
    {
        Fl::wait();
    }

    settings->setButtonColor(this->settingsWindow->getSelectedButtonColor());
    settings->setBackgroundColor(this->settingsWindow->getSelectedBackgroundColor());
    settings->setDifficulty(this->settingsWindow->getSelectedDifficulty());
    settings->setTextColor(this->settingsWindow->getSelectedTextColor());

    this->gameManager->setDifficulty(settings->getDifficulty());

    if (this->settingsWindow->getLoadSavedPuzzle())
    {
        this->gameManager->setDifficulty(settings->getLastSavedDifficulty());
        this->gameManager->loadSavedPuzzle();
    }
    else if (this->settingsWindow->getSelectedPuzzle() > 0)
    {
        this->gameManager->moveToPuzzle(this->settingsWindow->getSelectedPuzzle());
    }
}

///Draws the puzzle number label
//
void MainGameWindow::drawPuzzleNumberLabel()
{
    string labelText = this->getPuzzleNumberOutput();

    this->puzzleNumberLabel = new Fl_Box(85, 380, 175, 30, nullptr);
    this->puzzleNumberLabel->copy_label(labelText.c_str());
    this->puzzleNumberLabel->box(FL_UP_BOX);
    this->puzzleNumberLabel->labelsize(14);
}

string MainGameWindow::getPuzzleNumberOutput()
{
    // TODO can maybe move this to view formatter class
    return "Puzzle Number: " + to_string(this->gameManager->getCurrentPuzzleNumber()) +
        "/" + to_string(this->gameManager->getTotalPuzzlesCount());
}

void MainGameWindow::refreshBoard()
{
    string labelText = this->getPuzzleNumberOutput();
    this->puzzleNumberLabel->copy_label(labelText.c_str());

    this->puzzleGrid->resetBoard(this->gameManager);
    this->puzzleGrid->resetColors(this->gameManager);
}

void MainGameWindow::refreshColors()
{
    this->puzzleGrid->resetColors(this->gameManager);
}

///Adds the submit button to the screen
//
void MainGameWindow::addEvaluateButton()
{
    this->evaluateButton = new Fl_Button(221, 340, 110, 30, "EVALUATE");
    this->evaluateButton->callback(cbEvaluateButtonClicked, this);
}

void MainGameWindow::addPauseButton()
{
    this->pauseButton = new Fl_Button(300, 380, 40, 40, "@||");
    this->pausePuzzleOverlay = new Fl_Box(20, 20, 300, 300, "This is not the puzzle you are looking for...");
    this->pausePuzzleOverlay->hide();
    this->pausePuzzleOverlay->color(this->gameManager->getSettings()->getButtonColor());
    this->pausePuzzleOverlay->box(FL_UP_BOX);
    this->pauseButton->callback(cbPauseButtonClicked, this);
}

///Adds the reset button to the screen
//
void MainGameWindow::addResetButton()
{
    this->resetButton = new Fl_Button(10, 340, 110, 30, "RESET");
    this->resetButton->callback(cbResetButtonClicked, this);
}

void MainGameWindow::addViewHighScoresButton()
{
    this->viewHighScoresButton = new Fl_Button(420, 350, 110, 30, "HIGH SCORES");
    this->viewHighScoresButton->callback(cbViewHighScoresClicked, this);
}

/// Adds the timer label to the window.
void MainGameWindow::drawTimerLabel()
{
    this->gameTimerLabel = new Fl_Box(385, 385, 175, 30, nullptr);
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
    window->colorEvaluationPath();

    if (successfullySolved && !isLastPuzzle)
    {
        window->getGameManager()->recordGameCompletion("user");
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
        window->refreshColors();
    }
}

void MainGameWindow::colorEvaluationPath()
{
    this->puzzleGrid->colorEvaluationPath(this->gameManager);
}

/// Callback for the reset button click
//
void MainGameWindow::cbResetButtonClicked(Fl_Widget* widget, void* data)
{
    MainGameWindow* window = (MainGameWindow*)data;
    window->getGameManager()->resetCurrentPuzzle();
    window->refreshBoard();
    window->refreshTimerLabel();
}

void MainGameWindow::cbViewHighScoresClicked(Fl_Widget* widget, void* data)
{
    MainGameWindow* window = (MainGameWindow*)data;
    HighScoresWindow highScoresWindow(window->gameManager);
    highScoresWindow.show();

    while (highScoresWindow.shown())
    {
        Fl::wait();
    }
}

void MainGameWindow::cbPauseButtonClicked(Fl_Widget* widget, void* data)
{
    MainGameWindow* window = (MainGameWindow*)data;
    bool isGamePaused = window->gameManager->getIsGamePaused();

    if (isGamePaused)
    {
        window->startGame();
    }
    else
    {
        window->stopGame();
    }
}

void MainGameWindow::stopGame()
{
    this->pauseButton->label("@>");
    this->pausePuzzleOverlay->show();
    this->gameManager->setIsGamePaused(true);
    this->resetButton->deactivate();
    this->evaluateButton->deactivate();
}

void MainGameWindow::startGame()
{
    this->pauseButton->label("@||");
    this->pausePuzzleOverlay->hide();
    this->gameManager->setIsGamePaused(false);
    this->resetButton->activate();
    this->evaluateButton->activate();
}

GameManager* MainGameWindow::getGameManager()
{
    return this->gameManager;
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

void MainGameWindow::cbOnWindowClose(Fl_Widget *, void *data)
{
    auto *window = (MainGameWindow*) data;

    window->gameManager->saveCurrentPuzzle();
    window->gameManager->saveHighScores();
    window->gameManager->saveSettings();

    window->hide();
}

MainGameWindow::~MainGameWindow()
{
    delete this->puzzleGrid;
    delete this->gameManager;
}

}


