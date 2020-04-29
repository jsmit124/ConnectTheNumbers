//
// Created by andrew on 4/28/20.
//

#ifndef MOVIEPLAITER_PUZZLEGRID_H
#define MOVIEPLAITER_PUZZLEGRID_H


#include <FL/Fl_Button.H>
#include <FL/Fl_Group.H>
#include <string>

#define PUZZLE_ROWS 8
#define PUZZLE_COLS 8

#define BUTTON_WIDTH 40
#define BUTTON_HEIGHT 40
#define BUTTON_PADDING 10

using namespace std;

namespace view {

    /// A puzzle grid widget whose labels can be arbitrarily set and react to click events.
    //
    class PuzzleGrid {
    public:
        /**
         * Creates a puzzle grid widget.
         * @param x the x-location to place the widget
         * @param y the y-location to place the widget
         */
        PuzzleGrid(int x, int y);

        /**
         * Destroys the widget, freeing all the child buttons and the grid.
         */
        ~PuzzleGrid();
    private:
        Fl_Group *gridGroup;
    };
}


#endif //MOVIEPLAITER_PUZZLEGRID_H
