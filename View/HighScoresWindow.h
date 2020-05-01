//
// Created by andrew on 5/1/20.
//

#ifndef MOVIEPLAITER_HIGHSCORESWINDOW_H
#define MOVIEPLAITER_HIGHSCORESWINDOW_H

#include <Fl/Fl_Button.H>
#include <Fl/Fl_Window.H>

#include "../Controller/GameManager.h"
#include "./HighScoreboardTable.h"

using namespace controller;
using namespace model;

namespace view {
    class HighScoresWindow : public Fl_Window {
    public:
        explicit HighScoresWindow(GameManager *manager);
        virtual ~HighScoresWindow();
    private:
        GameManager *manager;
        Fl_Button *clearButton;
        HighScoreboardTable *table;

        static void cbClearClicked(Fl_Widget*, void *data);
    };
}


#endif //MOVIEPLAITER_HIGHSCORESWINDOW_H
