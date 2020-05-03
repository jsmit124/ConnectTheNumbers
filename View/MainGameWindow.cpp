#include "MainGameWindow.h"

namespace view
{

/// MainGameWindow Constructor. Sets up and starts initial window
/// w/ preloaded settings. Set up controls post-initial window.
//
// @param width: the width of the window
// @param height: the height of the window
// @param title: the title of top bar
// @post fltk controls loaded
//       controller created
//       display showing
MainGameWindow::MainGameWindow(int width, int height, const char* title) : Fl_Window(width, height, title)
{
    this->gameManager = new GameManager();
    this->initializeSettingsWindow();
    this->initializeSettings();

    begin();

    this->puzzleGrid = new PuzzleGrid(20, 50, this->gameManager);
    this->setupMainWindowControls();
    this->highScoresWindow = new HighScoresWindow(this->gameManager);

    end();
}

  /// ///////// ///
 ///  GETTERS  ///
/// ////////  ///

/// Returns the pointer to highScoresWindow
// @return pointer to highScoresWindow
HighScoresWindow* MainGameWindow::getHighScoresWindow()
{
    return this->highScoresWindow;
}

/// Formats the simple output for the puzzle #:
/// ex: Puzzle: 3/12
// @return string of formatted output for puzzle #
string MainGameWindow::formatPuzzleNumberOutput()
{
    return "Puzzle: " + to_string(this->gameManager->getCurrentPuzzleNumber()) +
           "/" + to_string(this->gameManager->getTotalPuzzlesCount());
}

  /// ///////////// ///
 ///  GAME EVENTS  ///
/// ///////////// ///

/// Displays a prompt indicating question to continue playing
// @post: if yes; move to next puzzle & update board
void MainGameWindow::showRoundEndWindow()
{
    switch (fl_choice("Do you want to keep going?", "Yes", "No", 0))
    {
        case 0:
            this->startGame();
            this->gameManager->moveToNextPuzzle();
            this->refreshBoard();
            break;

    }
}

/// Displays a prompt indicating question to restart game
// @post: if yes; set to round 1 & update board
void MainGameWindow::showFinalRoundWindow()
{
    switch (fl_choice("Do you want to restart the game?", "Yes", "No", 0))
    {
        case 0:
            this->startGame();
            this->gameManager->resetGame();
            this->refreshBoard();
            break;
        case 1:
            break;
    }
}

/// Starts the game back up from a paused inactive state
// @pre: none
// @post: all buttons activate
//        overlay hidden
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

/// Deactivates all buttons for a paused game state
// @post: all buttons deactivate
//        paused state = true
void MainGameWindow::stopGame()
{
    this->gameManager->setIsGamePaused(true);
    this->peekButton->deactivate();
    this->resetButton->deactivate();
    this->evaluateButton->deactivate();
    this->puzzleGrid->deactivate();
}

/// Refreshes the timer label
// @post: gameTimerLabel updated
void MainGameWindow::refreshTimerLabel()
{
    string formattedTimeSpent = "Time: " + formatDurationHoursSeconds(this->gameManager->getTimeSpentOnPuzzle());
    this->gameTimerLabel->copy_label(formattedTimeSpent.c_str());
}

/// Refreshes the board back to original game state.
// @post: puzzleGrid refreshed
//        labels refreshed
void MainGameWindow::refreshBoard()
{
    string labelText = this->formatPuzzleNumberOutput();
    this->puzzleNumberLabel->copy_label(labelText.c_str());

    this->puzzleGrid->activate();
    this->gameManager->setIsGamePaused(false);
    this->puzzleGrid->resetBoard(this->gameManager);
    this->puzzleGrid->resetColors();
}

/// Refreshes the colors of the puzzle
// @post: puzzle refreshed
void MainGameWindow::refreshColors()
{
    this->puzzleGrid->resetColors();
}

/// Adds the timer label to the window.
void MainGameWindow::drawTimerLabel()
{
    this->gameTimerLabel = new Fl_Box(200, 10, 205, 40, nullptr);
    this->gameTimerLabel->box(FL_UP_BOX);
    this->gameTimerLabel->labelsize(18);
    this->refreshTimerLabel();
}

///Draws the puzzle number label
void MainGameWindow::drawPuzzleNumberLabel()
{
    string labelText = this->formatPuzzleNumberOutput();

    this->puzzleNumberLabel = new Fl_Box(30, 10, 145, 40, nullptr);
    this->puzzleNumberLabel->copy_label(labelText.c_str());
    this->puzzleNumberLabel->box(FL_UP_BOX);
    this->puzzleNumberLabel->labelsize(18);
}

/// Colors the current puzzle evaluation path
void MainGameWindow::colorEvaluationPath()
{
    this->puzzleGrid->colorEvaluationPath(this->gameManager);
}

/// Colors the current puzzle peek path (next uneditable note from curr spot)
void MainGameWindow::colorPeekPath()
{
    this->puzzleGrid->colorPeekPath(this->gameManager);
}

/// Events required for on Pause button click event
void MainGameWindow::handlePause()
{
    this->pauseButton->label("@>");
    this->pausePuzzleOverlay->show();
    this->pausePuzzleOverlay->redraw();
    this->stopGame();
}

/// Events required for on Game Finished event
void MainGameWindow::handleGameFinished()
{
    this->stopGame();
    this->pauseButton->deactivate();
}

/// Handles events fired during a valid evaluation
void MainGameWindow::handleEvaluateCorrectly()
{
    this->handleGameFinished();
    this->gameManager->recordGameCompletion("user");

    Messenger messenger;
    messenger.showPuzzleEndMessage(this->gameManager->getTimeSpentOnPuzzle());

    bool isFinalPuzzleOfGame = this->gameManager->isFinalPuzzle();
    bool isLastPuzzleOfDifficulty = this->gameManager->isLastPuzzle();

    if (isFinalPuzzleOfGame)
    {
        this->showFinalRoundWindow();
    }
    else if (!isLastPuzzleOfDifficulty)
    {
        this->gameManager->moveToNextPuzzle();
        this->refreshBoard();
    }
    else
    {
        this->showRoundEndWindow();
    }
}

  /// /////////// ///
 ///  CALLBACKS  ///
/// /////////// ///

/// Callback for peek button click event
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

/// Callback for the evaulate button click
void MainGameWindow::cbEvaluateButtonClicked(Fl_Widget* widget, void* data)
{
    MainGameWindow* window = (MainGameWindow*)data;
    bool successfullySolved = window->gameManager->evaluateCurrentPuzzle();
    window->colorEvaluationPath();

    if (successfullySolved)
    {
        window->handleEvaluateCorrectly();
    }
    else
    {
        fl_message("Uh oh.. the board is not correct. Try again!");
        window->refreshBoard();
    }
}

/// Callback for Main Game Window close event
void MainGameWindow::cbOnWindowClose(Fl_Widget *, void *data)
{
    auto *window = (MainGameWindow*) data;

    window->gameManager->saveCurrentPuzzle();
    window->gameManager->saveHighScores();
    window->gameManager->saveSettings();

    window->getHighScoresWindow()->hide();
    window->hide();
}

/// Callback for the reset button click
void MainGameWindow::cbResetButtonClicked(Fl_Widget* widget, void* data)
{
    MainGameWindow* window = (MainGameWindow*)data;
    window->gameManager->resetCurrentPuzzle();
    window->refreshBoard();
    window->refreshTimerLabel();
}

/// Callback for pause button click event
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

/// Callback for high scores button click event
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

  /// //////// ///
 ///  EVENTS  ///
/// //////// ///

/// Starts the game timer and sets the tick frequency.
void MainGameWindow::startGameTimer()
{
    Fl::add_timeout(1.0, MainGameWindow::onTimerTick, this);
}

/// Event for each tick of puzzle timer.
void MainGameWindow::onTimerTick(void *data)
{
    auto *window = (MainGameWindow*) data;
    window->gameManager->onTimerTick();
    window->refreshTimerLabel();

    Fl::repeat_timeout(1.0, MainGameWindow::onTimerTick, window);
}

/// ////////////////// ///
///  PRIVATE HELPERS   ///
/// ////////////////// ///

/// Draws peek button on view and sets up functionality
void MainGameWindow::addPeekButton()
{
    this->peekButton = new Fl_Button(100, 515, 60, 40, "?");
    this->peekButton->labelsize(28);
    this->peekButton->labelfont(FL_SCREEN_BOLD);
    this->peekButton->callback(cbPeekButtonClicked, this);
}

/// Draws evaluation button on view and sets up functionality
void MainGameWindow::addEvaluateButton()
{
    this->evaluateButton = new Fl_Button(175, 515, 150, 40, "EVALUATE");
    this->evaluateButton->labelsize(18);
    this->evaluateButton->callback(cbEvaluateButtonClicked, this);
}

/// Draws pause button on view and sets up functionality
void MainGameWindow::addPauseButton()
{
    this->pauseButton = new Fl_Button(430, 10, 40, 40, "@||");
    this->pauseButton->labelsize(18);
    this->pauseButton->labelfont(FL_SCREEN_BOLD);
    this->pauseButton->callback(cbPauseButtonClicked, this);
}

/// Draws the puzzle box overlay and sets up functionality
void MainGameWindow::addPuzzleOverlayBox()
{
    this->pausePuzzleOverlay = new Fl_Box(30, 60, 440, 440, "This is not the puzzle\n you are looking for...");
    this->pausePuzzleOverlay->hide();
    this->pausePuzzleOverlay->labelsize(25);
    this->pausePuzzleOverlay->labelcolor(this->gameManager->getSettings()->getTextColor());
    this->pausePuzzleOverlay->color(this->gameManager->getSettings()->getButtonColor());
    this->pausePuzzleOverlay->box(FL_UP_BOX);
}

/// Draws reset button on view and sets up functionality
void MainGameWindow::addResetButton()
{
    this->resetButton = new Fl_Button(30, 515, 60, 40, "↺");
    this->resetButton->labelfont(FL_SCREEN_BOLD);
    this->resetButton->labelsize(30);
    this->resetButton->callback(cbResetButtonClicked, this);
}

/// Draws high score button on view and sets up functionality
void MainGameWindow::addViewHighScoresButton()
{
    this->viewHighScoresButton = new Fl_Button(340, 515, 130, 40, "HIGH SCORES");
    this->viewHighScoresButton->labelsize(16);
    this->viewHighScoresButton->callback(cbViewHighScoresClicked, this);
}

/// Sets up the opening initial window (prev settings) and displays
void MainGameWindow::initializeSettingsWindow()
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
}

/// Sets up settings post-initial window.
/// Loads puzzles accordingly
void MainGameWindow::initializeSettings()
{
    PlayerSettings* settings = this->gameManager->getSettings();

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

/// Sets up the FLTK user controls on the Main Game Window.
void MainGameWindow::setupMainWindowControls()
{
    PlayerSettings* settings = this->gameManager->getSettings();

    this->color(settings->getBackgroundColor());

    this->addPeekButton();
    this->addEvaluateButton();
    this->addResetButton();
    this->addPauseButton();
    this->addViewHighScoresButton();

    this->drawPuzzleNumberLabel();
    this->drawTimerLabel();

    this->startGameTimer();
    this->callback(MainGameWindow::cbOnWindowClose, this);

    this->addPuzzleOverlayBox();
}

/// Main Game Window destructor.
MainGameWindow::~MainGameWindow()
{
    delete this->settingsWindow;
    delete this->highScoresWindow;
    delete this->puzzleGrid;
    delete this->gameManager;

    delete this->highScoresLabel;
    delete this->evaluateButton;
    delete this->pauseButton;
    delete this->resetButton;
    delete this->peekButton;
    delete this->viewHighScoresButton;
    delete this->pausePuzzleOverlay;
    delete this->puzzleNumberLabel;
    delete this->gameTimerLabel;
}

}
