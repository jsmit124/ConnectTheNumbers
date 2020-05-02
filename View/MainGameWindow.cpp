#include "MainGameWindow.h"

namespace view
{

MainGameWindow::MainGameWindow(int width, int height, const char* title) : Fl_Window(width, height, title)
{
    this->gameManager = new GameManager();
    this->initialize();

    begin();

    PlayerSettings* settings = this->gameManager->getSettings();
    this->puzzleGrid = new PuzzleGrid(20, 50, this->gameManager);
    this->color(settings->getBackgroundColor());

    // TODO refactor to be setup buttons
    this->peekButton = new Fl_Button(100, 515, 60, 40, "?");
    this->peekButton->labelsize(28);
    this->peekButton->labelfont(FL_SCREEN_BOLD);
    this->peekButton->callback(cbPeekButtonClicked, this);

    this->addEvaluateButton();
    this->addResetButton();
    this->addPauseButton();
    this->addViewHighScoresButton();

    this->drawPuzzleNumberLabel();
    this->drawTimerLabel();

    this->startGameTimer();
    this->callback(MainGameWindow::cbOnWindowClose, this);

    this->highScoresWindow = new HighScoresWindow(this->gameManager);

    end();
}

/// Initializes the game and gives player opportunity to adjust settings
//
void MainGameWindow::initialize()
{
    PlayerSettings* settings = this->gameManager->getSettings();
    this->settingsWindow = new InitialSettingsWindow();

    this->settingsWindow->setColorToAllButtons(settings->getButtonColor());
    this->settingsWindow->setTextColorToAllButtons(settings->getTextColor());
    this->settingsWindow->setBackgroundColor(settings->getBackgroundColor());
    this->settingsWindow->setButtonColor(settings->getButtonColor());
    this->settingsWindow->setTextColor(settings->getTextColor());

    this->settingsWindow->set_modal();
    this->settingsWindow->show();
    this->settingsWindow->setSavedButtonState(this->gameManager->getDoesSavedFileExist());

    while (this->settingsWindow->shown())
    {
        Fl::wait();
    }

    settings->setButtonColor(this->settingsWindow->getSelectedButtonColor());
    settings->setTextColor(this->settingsWindow->getSelectedTextColor());
    settings->setBackgroundColor(this->settingsWindow->getSelectedBackgroundColor());
    settings->setDifficulty(this->settingsWindow->getSelectedDifficulty());

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

    this->puzzleNumberLabel = new Fl_Box(30, 10, 145, 40, nullptr);
    this->puzzleNumberLabel->copy_label(labelText.c_str());
    this->puzzleNumberLabel->box(FL_UP_BOX);
    this->puzzleNumberLabel->labelsize(18);
}

string MainGameWindow::getPuzzleNumberOutput()
{
    // TODO can maybe move this to view formatter class
    return "Puzzle: " + to_string(this->gameManager->getCurrentPuzzleNumber()) +
        "/" + to_string(this->gameManager->getTotalPuzzlesCount());
}

void MainGameWindow::refreshBoard()
{
    string labelText = this->getPuzzleNumberOutput();
    this->puzzleNumberLabel->copy_label(labelText.c_str());

    this->gameManager->setIsGamePaused(false);
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
    this->evaluateButton = new Fl_Button(175, 515, 150, 40, "EVALUATE");
    this->evaluateButton->labelsize(18);
    this->evaluateButton->callback(cbEvaluateButtonClicked, this);
}

void MainGameWindow::addPauseButton()
{
    this->pauseButton = new Fl_Button(430, 10, 40, 40, "@||");
    this->pausePuzzleOverlay = new Fl_Box(30, 60, 440, 440, "This is not the puzzle\n you are looking for...");
    this->pauseButton->labelsize(18);
    this->pauseButton->labelfont(FL_SCREEN_BOLD);
    this->pausePuzzleOverlay->hide();
    this->pausePuzzleOverlay->labelsize(25);
    this->pausePuzzleOverlay->labelcolor(this->gameManager->getSettings()->getTextColor());
    this->pausePuzzleOverlay->color(this->gameManager->getSettings()->getButtonColor());
    this->pausePuzzleOverlay->box(FL_UP_BOX);
    this->pauseButton->callback(cbPauseButtonClicked, this);
}

///Adds the reset button to the screen
//
void MainGameWindow::addResetButton()
{
    this->resetButton = new Fl_Button(30, 515, 60, 40, "↺");
    this->resetButton->labelfont(FL_SCREEN_BOLD);
    this->resetButton->labelsize(30);
    this->resetButton->callback(cbResetButtonClicked, this);
}

void MainGameWindow::addViewHighScoresButton()
{
    this->viewHighScoresButton = new Fl_Button(340, 515, 130, 40, "HIGH SCORES");
    this->viewHighScoresButton->labelsize(16);
    this->viewHighScoresButton->callback(cbViewHighScoresClicked, this);
}

/// Adds the timer label to the window.
void MainGameWindow::drawTimerLabel()
{
    this->gameTimerLabel = new Fl_Box(200, 10, 205, 40, nullptr);
    this->gameTimerLabel->box(FL_UP_BOX);
    this->gameTimerLabel->labelsize(18);
    this->refreshTimerLabel();
}

/// Callback for the evaulate button click
//
void MainGameWindow::cbEvaluateButtonClicked(Fl_Widget* widget, void* data)
{
    // REFACTOR THIS Nolan<--
    MainGameWindow* window = (MainGameWindow*)data;
    bool successfullySolved = window->getGameManager()->evaluateCurrentPuzzle();
    bool isLastPuzzleOfDifficulty = window->getGameManager()->isLastPuzzle();
    int isFinalPuzzleOfGame = window->getGameManager()->isFinalPuzzle();
    int currentRound = window->getGameManager()->getCurrentPuzzleNumber();
    window->colorEvaluationPath();
    Messenger messenger;

    if (successfullySolved)
    {
        window->handleGameFinished();
        window->getGameManager()->recordGameCompletion("user");
        messenger.showPuzzleEndMessage(window->getGameManager()->getTimeSpentOnPuzzle());

        if (isFinalPuzzleOfGame)
        {
            window->showFinalRoundWindow();
        }
        else if (!isLastPuzzleOfDifficulty)
        {
            window->getGameManager()->moveToNextPuzzle();
            window->refreshBoard();
        }
        else
        {
            window->showRoundEndWindow();
        }
    }
    else
    {
        fl_message("Uh oh.. the board is not correct. Try again!");
    }
}

void MainGameWindow::showFinalRoundWindow()
{
    switch (fl_choice("Do you want to restart the game?", "Yes", "No", 0))
    {
        case 0:
            this->gameManager->resetGame();
            this->startGame();
            this->refreshBoard();
            break;
        case 1:
            break;
    }
}

void MainGameWindow::showRoundEndWindow()
{
    switch (fl_choice("Do you want to keep going?", "Yes", "No", 0))
    {
        case 0:
            this->gameManager->moveToNextPuzzle();
            this->startGame();
            this->refreshBoard();
            break;
        case 1:
            break;
    }
}

void MainGameWindow::colorEvaluationPath()
{
    this->puzzleGrid->colorEvaluationPath(this->gameManager);
}

void MainGameWindow::colorPeekPath()
{
    this->puzzleGrid->colorPeekPath(this->gameManager);
}

void MainGameWindow::cbPeekButtonClicked(Fl_Widget *widget, void *data)
{
    MainGameWindow* window = (MainGameWindow*)data;

    if (window->gameManager->foundFirstNode())
    {
        window->colorPeekPath();
        window->gameManager->increaseTimeBy30();
        window->refreshTimerLabel();
        fl_message("Fine.. here is a hint.\n+30 seconds");

        window->refreshColors();
        window->refreshBoard();
    }
    else
    {
        fl_message("You need to find '1' on the puzzle first.");
    }
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

HighScoresWindow* MainGameWindow::getHighScoresWindow()
{
    return this->highScoresWindow;
}

void MainGameWindow::cbViewHighScoresClicked(Fl_Widget* widget, void* data)
{
    MainGameWindow* window = (MainGameWindow*)data;
    HighScoresWindow* highScoresWindow = window->getHighScoresWindow();
    highScoresWindow->refreshTableData();
    highScoresWindow->show();

    while (highScoresWindow->shown())
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
        window->handlePause();
    }
}

void MainGameWindow::stopGame()
{
    this->gameManager->setIsGamePaused(true);
    this->peekButton->deactivate();
    this->resetButton->deactivate();
    this->evaluateButton->deactivate();
    this->puzzleGrid->deactivate();
}

void MainGameWindow::handleGameFinished()
{
    this->stopGame();
    this->pauseButton->deactivate();
}

void MainGameWindow::handlePause()
{
    this->pauseButton->label("@>");
    this->pausePuzzleOverlay->show();
    this->stopGame();
}

void MainGameWindow::startGame()
{
    this->pauseButton->label("@||");
    this->puzzleGrid->activate();
    this->pausePuzzleOverlay->hide();
    this->gameManager->setIsGamePaused(false);
    this->peekButton->activate();
    this->resetButton->activate();
    this->evaluateButton->activate();
    this->pauseButton->activate();
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

    window->getHighScoresWindow()->hide();
    window->hide();
}

MainGameWindow::~MainGameWindow()
{
    delete this->puzzleGrid;
    delete this->gameManager;
}

}


