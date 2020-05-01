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
    PuzzleGrid::PuzzleGrid(int x, int y, GameManager* manager, Fl_Color buttonBackgroundColor, Fl_Color buttonTextColor)
    {
        this->validNodeColor = new Fl_Color(FL_DARK_GREEN);
        this->defaultEvaluationTextColor = new Fl_Color(FL_WHITE);
        this->invalidNodeColor = new Fl_Color(FL_RED);
        this->defaultBackgroundColor = buttonBackgroundColor;
        this->defaultLabelColor = buttonTextColor;

        this->drawPuzzleGrid(x, y, manager, buttonBackgroundColor, buttonTextColor);
    }

    /// Draws the puzzle grid
    //
    // @param x the x-location to place the grid
    // @param y the y-location to place the grid
    //
    void PuzzleGrid::drawPuzzleGrid(int x, int y, GameManager* gameManager, Fl_Color buttonBackgroundColor, Fl_Color textColor)
    {
        this->gridGroup = new Fl_Group(x, y, PUZZLE_ROWS * BUTTON_WIDTH + BUTTON_PADDING,
                PUZZLE_COLS * BUTTON_HEIGHT + BUTTON_PADDING, nullptr);

        for (int row = 0; row < PUZZLE_ROWS; row++) {
            for (int col = 0; col < PUZZLE_COLS; col++) {
                int placedX = col * BUTTON_HEIGHT + BUTTON_PADDING;
                int placedY = row * BUTTON_WIDTH + BUTTON_PADDING;
                int index = row * PUZZLE_ROWS + col;

                PuzzleGridButton *button = new PuzzleGridButton(placedX, placedY, BUTTON_WIDTH, BUTTON_HEIGHT, index);
                button->callback(cbButtonSelected, gameManager);
                button->color(buttonBackgroundColor);
                button->labelcolor(textColor);

                this->gridButtons.push_back(button);
                this->updatePuzzleNode(index, gameManager);
            }
        }
        this->gridGroup->end();
    }

    void PuzzleGrid::updatePuzzleNode(int index, GameManager* gameManager)
    {
        PuzzleGridButton* button = this->gridButtons.at(index);
        int value = gameManager->getPuzzleNodeValue(index);
        bool isEditable = gameManager->isPuzzleNodeEditable(index);

        if (!isEditable)
        {
            button->deactivate();
        }
        else
        {
            button->activate();
        }

        if (value == 0)
        {
            button->copy_label("");
        }
        else
        {
            button->copy_label(to_string(value).c_str());
        }
    }

    void PuzzleGrid::resetBoard(GameManager* gameManager)
    {
        for (int i = 0; i < this->gridButtons.size(); i++)
        {
            this->updatePuzzleNode(i, gameManager);
        }
    }

    void PuzzleGrid::resetColors(GameManager* gameManager)
    {
        for (int i = 0; i < this->gridButtons.size(); i++)
        {
            this->gridButtons.at(i)->color(this->defaultBackgroundColor);
            this->gridButtons.at(i)->labelcolor(this->defaultLabelColor);
            this->gridButtons.at(i)->redraw();
        }
    }

    void PuzzleGrid::colorEvaluationPath(GameManager* gameManager)
    {
        int startIndex = gameManager->getCurrentPuzzleStartIndex();

        PuzzleGridButton* startButton = this->gridButtons.at(startIndex);
        startButton->setColors(this->validNodeColor, this->defaultEvaluationTextColor);

        this->evaluate(startIndex, gameManager);
    }

    void PuzzleGrid::evaluate(int prevIndex, GameManager* gameManager)
    {
        int nextIndex = gameManager->getNextNodeIndexOfCurrentPuzzle(prevIndex);
        PuzzleGridButton* prevButton = this->gridButtons.at(prevIndex);
        int buttonValue = stoi(prevButton->label());

        if (nextIndex > -1)
        {
            this->gridButtons.at(nextIndex)->setColors(this->validNodeColor, this->defaultEvaluationTextColor);
            this->evaluate(nextIndex, gameManager);
        }
        else if (buttonValue == this->gridButtons.size())
        {
            prevButton->setColors(this->validNodeColor, this->defaultEvaluationTextColor);
        }
        else
        {
            this->gridButtons.at(prevIndex)->setColors(this->invalidNodeColor, this->defaultEvaluationTextColor);
        }
    }

    /// Handles the button click callback event
    //
    void PuzzleGrid::cbButtonSelected(Fl_Widget* widget, void* data)
    {
        GameManager* manager = (GameManager*)data;
        ButtonValueWindow buttonValueEntry(1, 64);
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
