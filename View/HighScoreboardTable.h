#ifndef MOVIEPLAITER_HIGHSCOREBOARDTABLE_H
#define MOVIEPLAITER_HIGHSCOREBOARDTABLE_H

#include "../Model/HighScoreEntry.h"
#include "../Utils/Utils.h"

#include <FL/Fl.H>
#include <FL/Fl_Table_Row.H>
#include <FL/fl_draw.H>

#define HIGH_SCORE_COLS 3

#define COLUMN_PLAYER 0
#define COLUMN_DURATION 1
#define COLUMN_PUZZLE 2

using namespace model;

namespace view {
    /**
     * A component that displays the high scoreboard tables.
     */
    class HighScoreboardTable : public Fl_Table_Row {
    private:
        vector<HighScoreEntry *> entriesUsed;

        void drawHeader(const char *s, int X, int Y, int W, int H);

        void drawData(const char *s, int X, int Y, int W, int H);

        void draw_cell(TableContext context, int row, int col, int x, int y, int w, int h) override;
    public:
        /**
         * Constructs the high scoreboard.
         * @param X the x-position to place the component
         * @param Y the y-position to place the component
         * @param W the width of the component
         * @param H the height of the component
         * @param entries the initial entries to populate with
         */
        HighScoreboardTable(int X, int Y, int W, int H, vector<HighScoreEntry *> entries);

        /**
         * Refreshes the scoreboard.
         * @param entries the new entries to use
         */
        void refresh(vector<HighScoreEntry *> entries);
    };
}


#endif //MOVIEPLAITER_HIGHSCOREBOARDTABLE_H
