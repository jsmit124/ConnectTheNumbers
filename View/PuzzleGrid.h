#ifndef MOVIEPLAITER_PUZZLEGRID_H
#define MOVIEPLAITER_PUZZLEGRID_H

#include <FL/Fl_Button.H>
#include <Fl/Fl.H>
#include <Fl/Fl_Box.H>
#include <FL/Fl_Group.H>
#include <Fl/Fl_Window.H>
#include <Fl/Fl_Export.H>
#include <string>

#define PUZZLE_ROWS 8
#define PUZZLE_COLS 8

#define BUTTON_WIDTH 40
#define BUTTON_HEIGHT 40
#define BUTTON_PADDING 10

#include "../Controller/GameManager.h"
using namespace controller;

#include "ButtonValueWindow.h"
#include "PuzzleGridButton.h"
using namespace view;

#include <vector>
#include <iostream>
using namespace std;

namespace view {

    /// A puzzle grid widget whose labels can be arbitrarily set and react to click events.
    //
    class PuzzleGrid {
    public:
        PuzzleGrid(int x, int y, GameManager* gameManager);
        ~PuzzleGrid();

        void resetBoard(GameManager* gameManager);

    private:
        Fl_Group *gridGroup;
        vector<PuzzleGridButton*> gridButtons;

        void drawPuzzleGrid(int, int, GameManager*);
        static void cbButtonSelected(Fl_Widget*, void*);
    };
}


#endif //MOVIEPLAITER_PUZZLEGRID_H
