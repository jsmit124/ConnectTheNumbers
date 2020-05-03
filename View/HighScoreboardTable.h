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

namespace view
{

/// Handles implementation of the Window to display the high scoreboard table.
//
class HighScoreboardTable : public Fl_Table_Row
{

private:
    vector<HighScoreEntry *> entriesUsed;
    void drawHeader(const char *s, int X, int Y, int W, int H);
    void drawData(const char *s, int X, int Y, int W, int H);
    void draw_cell(TableContext context, int row, int col, int x, int y, int w, int h) override;

public:
    HighScoreboardTable(int X, int Y, int W, int H, vector<HighScoreEntry *> entries);
    void refresh(vector<HighScoreEntry *> entries);

};
}


#endif //MOVIEPLAITER_HIGHSCOREBOARDTABLE_H
