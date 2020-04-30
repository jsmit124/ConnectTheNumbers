//
// @author Andrew, Justin, Nolan
//

#include "PuzzleGrid.h"

namespace view {

    /// Creates a puzzle grid widget.
    //
    // @param x the x-location to place the widget
    // @param y the y-location to place the widget
    //
    PuzzleGrid::PuzzleGrid(int x, int y) {
        this->drawPuzzleGrid(x, y);
        this->drawPuzzleNumberLabel();
        this->addEvaluateButton();
        this->drawHighScoresLabel();
    }

    /// Draws the puzzle grid
    //
    // @param x the x-location to place the grid
    // @param y the y-location to place the grid
    //
    void PuzzleGrid::drawPuzzleGrid(int x, int y)
    {
        Fl_Color* buttonBackgroundColor = new Fl_Color(FL_DARK3);
        Fl_Color* white = new Fl_Color(FL_WHITE);

        this->gridGroup = new Fl_Group(x, y, PUZZLE_ROWS * BUTTON_WIDTH + BUTTON_PADDING,
                PUZZLE_COLS * BUTTON_HEIGHT + BUTTON_PADDING, nullptr);

        for (int row = 0; row < PUZZLE_ROWS; row++) {
            for (int col = 0; col < PUZZLE_COLS; col++) {
                int placedX = col * BUTTON_HEIGHT + BUTTON_PADDING;
                int placedY = row * BUTTON_WIDTH + BUTTON_PADDING;
                int index = row * PUZZLE_ROWS + col;

                auto *button = new PuzzleGridButton(placedX, placedY, BUTTON_WIDTH, BUTTON_HEIGHT, index);

                int value = this->gameManager.getPuzzleNodeValue(index);
                bool isEditable = this->gameManager.isPuzzleNodeEditable(index);

                button->copy_label(to_string(value).c_str());
                button->callback(cbButtonSelected, this);

                if (!isEditable)
                {
                    button->deactivate();
                }

                button->color(*buttonBackgroundColor);
                button->labelcolor(*white);
                button->damage(1);
            }
        }
        this->gridGroup->end();
    }

    ///Draws the puzzle number label
    //
    void PuzzleGrid::drawPuzzleNumberLabel()
    {
        string* labelText = new string("Puzzle Number: " + to_string(this->gameManager.getCurrentPuzzleNumber()) + "/" + to_string(this->gameManager.DEFAULT_PUZZLE_COUNT));

        Fl_Box* puzzleNumberLabel = new Fl_Box(10, 340, 175, 30, labelText->c_str());
        puzzleNumberLabel->box(FL_UP_BOX);
        puzzleNumberLabel->labelsize(14);
    }

    ///Adds the submit button to the screen
    //
    void PuzzleGrid::addEvaluateButton()
    {
        auto* submitButton = new Fl_Button(221, 340, 110, 30, "EVALUATE");
        submitButton->callback(cbEvaluateButtonClicked, this);
    }

    ///Draws the high scores label
    //
    void PuzzleGrid::drawHighScoresLabel()
    {
        Fl_Box* highScoresLabel = new Fl_Box(385, 10, 175, 30, "HIGH SCORES");
        highScoresLabel->box(FL_UP_BOX);
        highScoresLabel->labelsize(16);
    }

    /// Handles the button click callback event
    //
    void PuzzleGrid::cbButtonSelected(Fl_Widget* widget, void* data)
    {
        PuzzleGrid* window = (PuzzleGrid*)data;
        ButtonValueWindow buttonValueEntry;
        buttonValueEntry.set_modal();
        buttonValueEntry.show();

        while (buttonValueEntry.shown())
        {
            Fl::wait();
        }

        if (buttonValueEntry.getValue() != 0)
        {
            auto * currButton = (PuzzleGridButton*)widget;
            window->getGameManager().setPuzzleNodeValue(buttonValueEntry.getValue(), currButton->getID());
            widget->copy_label(to_string(buttonValueEntry.getValue()).c_str());
        }
    }

    /// Callback for the evaulate button click
    //
    void PuzzleGrid::cbEvaluateButtonClicked(Fl_Widget* widget, void* data)
    {
        cout << "Evaulate button clicked" << endl;
        //TODO call manager to evaluate button
    }

    /// Destroys the widget, freeing all the child buttons and the grid.
    //
    PuzzleGrid::~PuzzleGrid() {
        delete this->gridGroup;
    }

    GameManager PuzzleGrid::getGameManager()
    {
        return this->gameManager;
    }
}
