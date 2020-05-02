#ifndef MOVIEPLAITER_HIGHSCORESWINDOW_H
#define MOVIEPLAITER_HIGHSCORESWINDOW_H

#include <Fl/Fl_Button.H>
#include <Fl/Fl_Choice.H>
#include <Fl/Fl_Window.H>

#include "../Controller/GameManager.h"
#include "./HighScoreboardTable.h"

using namespace controller;
using namespace model;

namespace view {

    enum HighScoresSort { BY_DURATION, BY_PUZZLE };

    class HighScoresWindow : public Fl_Window {

    public:
        explicit HighScoresWindow(GameManager *manager);
        ~HighScoresWindow() override;

        void refreshTableData();

    private:
        GameManager *manager;
        Fl_Button *clearButton;
        Fl_Choice *sortChoice;
        HighScoreboardTable *table;
        HighScoresSort sortBy;

        static void cbClearClicked(Fl_Widget*, void *data);
        static void cbSortChanged(Fl_Widget*, void *data);

        void applyColorScheme();
    };
}


#endif //MOVIEPLAITER_HIGHSCORESWINDOW_H
