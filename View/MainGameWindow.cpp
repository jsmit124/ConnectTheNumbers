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

    this->drawPuzzleNumberLabel();
    this->drawHighScoresLabel();
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

    for (int i = 0; i < MAXIMUM_HIGH_SCORE_ENTRIES; i++)
    {
        auto *box = new Fl_Box(385, 50 + (i * 40), 175, 30, nullptr);
        box->labelcolor(FL_WHITE);
        this->highScoreLabels.push_back(box);
    }

    this->updateHighScoreLabels();
}

void MainGameWindow::updateHighScoreLabels()
{
    vector<HighScoreEntry*> entries = this->gameManager->getTopTenScoresByDuration();

    for (int i = 0; i < entries.size(); i++)
    {
        HighScoreEntry *entry = entries[i];
        Fl_Box *label = this->highScoreLabels[i];
        string formatted = entry->getName() + ", puzzle " + to_string(entry->getPuzzle()) + ", for " +
                formatDurationHoursSeconds(entry->getDuration());
        label->copy_label(formatted.c_str());
    }
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
    window->colorEvaluationPath();

    if (successfullySolved && !isLastPuzzle)
    {
        window->getGameManager()->recordGameCompletion("user");
        window->updateHighScoreLabels();
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

void MainGameWindow::cbOnWindowClose(Fl_Widget *, void *data)
{
    auto *window = (MainGameWindow*) data;

    // TODO move this to single save state function
    window->gameManager->saveCurrentPuzzle();
    window->gameManager->saveHighScores();
    window->gameManager->saveSettings();

    window->hide();
}

}


