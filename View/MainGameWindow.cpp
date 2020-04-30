#include "MainGameWindow.h"

namespace view
{

MainGameWindow::MainGameWindow(int width, int height, const char* title) : Fl_Window(width, height, title)
{
    begin();

    this->gameManager = new GameManager();

    this->grid = new PuzzleGrid (20, 0, this->gameManager);
    this->color(fl_darker(fl_darker(fl_darker(FL_DARK_BLUE))));

    this->addEvaluateButton();
    this->addResetButton();

    this->drawPuzzleNumberLabel();
    this->drawHighScoresLabel();

    end();
}

///Draws the puzzle number label
//
void MainGameWindow::drawPuzzleNumberLabel()
{
    string* labelText = new string("Puzzle Number: " + to_string(this->gameManager->getCurrentPuzzleNumber()) + "/" + to_string(this->gameManager->DEFAULT_PUZZLE_COUNT));

    this->puzzleNumberLabel = new Fl_Box(85, 380, 175, 30, labelText->c_str());
    this->puzzleNumberLabel->box(FL_UP_BOX);
    this->puzzleNumberLabel->labelsize(14);
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

/// Callback for the evaulate button click
//
void MainGameWindow::cbEvaluateButtonClicked(Fl_Widget* widget, void* data)
{
    MainGameWindow* window = (MainGameWindow*)data;
    bool evaluation = window->getGameManager()->evaluateCurrentPuzzle();
}

/// Callback for the reset button click
//
void MainGameWindow::cbResetButtonClicked(Fl_Widget* widget, void* data)
{
    cout << "Reset button clicked" << endl;
    //TODO call manager to reset the button values
}

GameManager* MainGameWindow::getGameManager()
{
    return this->gameManager;
}

MainGameWindow::~MainGameWindow()
{
    delete this->grid;
    delete this->gameManager;
}

}


