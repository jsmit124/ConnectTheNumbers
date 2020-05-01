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

#include <unistd.h>
#include <stdlib.h>
#include <thread>
#include <chrono>
#include <vector>
#include <iostream>
using namespace std;

namespace view {

    /// A puzzle grid widget whose labels can be arbitrarily set and react to click events.
    //
    class PuzzleGrid {
    public:
        PuzzleGrid(int x, int y, GameManager* gameManager, Fl_Color, Fl_Color);
        ~PuzzleGrid();

        void resetColors(GameManager* gameManager);
        void resetBoard(GameManager* gameManager);
        void colorEvaluationPath(GameManager* gameManager);

    private:
        Fl_Group *gridGroup;
        vector<PuzzleGridButton*> gridButtons;

        Fl_Color* validNodeColor;
        Fl_Color* invalidNodeColor;
        Fl_Color* defaultEvaluationTextColor;
        Fl_Color defaultBackgroundColor;
        Fl_Color defaultLabelColor;

        void updatePuzzleNode(int index, GameManager* gameManager);
        void evaluate(int prevIndex, GameManager* gameManager);
        void drawPuzzleGrid(int, int, GameManager*, Fl_Color, Fl_Color);
        static void cbButtonSelected(Fl_Widget*, void*);
    };
}


#endif //MOVIEPLAITER_PUZZLEGRID_H
