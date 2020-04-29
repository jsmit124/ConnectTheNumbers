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
                int number = row * PUZZLE_ROWS + col + 1;

                auto *button = new Fl_Button(placedX, placedY, BUTTON_WIDTH, BUTTON_HEIGHT, "");
                button->copy_label(to_string(number).c_str());
                button->callback(cbButtonSelected, this);
                button->deactivate();
            }
        }
        this->gridGroup->end();

//    string labelText = strcat("Puzzle Number: ", "TODO");
//    int labelLength = labelText.length();
//    char char_array[labelLength + 1];
//    strcpy(char_array, labelText.c_str());
    Fl_Box* puzzleNumberLabel = new Fl_Box(15, 350, 150, 25, "Puzzle Number: "); // TODO add puzzle number here!!
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
            cout << "Value entered: " << buttonValueEntry.getValue() << endl;
            window->getGameManager().setValue(buttonValueEntry.getValue(), 1); // 1 needs to be an actual index
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
