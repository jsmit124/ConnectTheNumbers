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

            }
        }
        this->gridGroup->end();

        string* labelText = new string("Puzzle Number: " + to_string(this->gameManager.getCurrentPuzzleNumber()));

        Fl_Box* puzzleNumberLabel = new Fl_Box(15, 350, 150, 25, labelText->c_str());
        puzzleNumberLabel->box(FL_UP_BOX);
        puzzleNumberLabel->labelsize(14);
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
