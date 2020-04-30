//
// @author Andrew, Justin, Nolan
//

#include "./PuzzleGrid.h"

namespace view {

    /// Creates a puzzle grid widget.
    //
    // @param x the x-location to place the widget
    // @param y the y-location to place the widget
    //
    PuzzleGrid::PuzzleGrid(int x, int y, GameManager* manager)
    {
        this->drawPuzzleGrid(x, y, manager);
    }

    /// Draws the puzzle grid
    //
    // @param x the x-location to place the grid
    // @param y the y-location to place the grid
    //
    void PuzzleGrid::drawPuzzleGrid(int x, int y, GameManager* gameManager)
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

                int value = gameManager->getPuzzleNodeValue(index);
                bool isEditable = gameManager->isPuzzleNodeEditable(index);

                button->copy_label(to_string(value).c_str());
                button->callback(cbButtonSelected, gameManager);

                if (!isEditable)
                {
                    button->deactivate();
                }

                button->color(*buttonBackgroundColor);
                button->labelcolor(*white);
                button->damage(1);

                this->gridButtons.push_back(button);
            }
        }
        this->gridGroup->end();
    }

    void PuzzleGrid::resetBoard(GameManager* gameManager)
    {
        for (int i = 0; i < this->gridButtons.size(); i++)
        {
            int value = gameManager->getPuzzleNodeValue(i);
            bool isEditable = gameManager->isPuzzleNodeEditable(i);
            auto* currButton = this->gridButtons.at(i);

            // TODO duplicate code - refactor
            currButton->copy_label(to_string(value).c_str());

            if (!isEditable)
            {
                currButton->deactivate();
            }
        }
    }

    /// Handles the button click callback event
    //
    void PuzzleGrid::cbButtonSelected(Fl_Widget* widget, void* data)
    {
        GameManager* manager = (GameManager*)data;
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
            manager->setPuzzleNodeValue(buttonValueEntry.getValue(), currButton->getID());
            widget->copy_label(to_string(buttonValueEntry.getValue()).c_str());
        }
    }

    /// Destroys the widget, freeing all the child buttons and the grid.
    //
    PuzzleGrid::~PuzzleGrid()
    {
        delete this->gridGroup;
    }
}
