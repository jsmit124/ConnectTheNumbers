//
// Created by andrew on 4/28/20.
//

#include "PuzzleGrid.h"

namespace view {
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
            }
        }

        this->gridGroup->end();
    }

    PuzzleGrid::~PuzzleGrid() {
        delete this->gridGroup;
    }
}