#ifndef MOVIEPLAITER_PUZZLEGRID_H
#define MOVIEPLAITER_PUZZLEGRID_H

#include <FL/Fl_Button.H>
#include <Fl/Fl.H>
#include <Fl/Fl_Box.H>
#include <FL/Fl_Group.H>
#include <Fl/Fl_Window.H>
#include <string>

#define PUZZLE_ROWS 8
#define PUZZLE_COLS 8

#define BUTTON_WIDTH 40
#define BUTTON_HEIGHT 40
#define BUTTON_PADDING 10

#include "GameManager.h"
using namespace controller;

#include "ButtonValueWindow.h"
using namespace view;

#include <iostream>
using namespace std;

namespace view {

    /// A puzzle grid widget whose labels can be arbitrarily set and react to click events.
    //
    class PuzzleGrid {
    public:
        PuzzleGrid(int x, int y);
        ~PuzzleGrid();
        GameManager getGameManager();

    private:
        Fl_Group *gridGroup;
        static void cbButtonSelected(Fl_Widget*, void*);
        GameManager gameManager;

    };
}


#endif //MOVIEPLAITER_PUZZLEGRID_H
