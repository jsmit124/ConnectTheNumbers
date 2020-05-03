#include "HighScoreboardTable.h"

namespace view
{

/// Constructs the high scoreboard.
//
// @pre none
// @post none
//
// @param X the x-position to place the component
// @param Y the y-position to place the component
// @param W the width of the component
// @param H the height of the component
// @param entries the initial entries to populate with
//
HighScoreboardTable::HighScoreboardTable(int X, int Y, int W, int H, vector<HighScoreEntry*> entries) : Fl_Table_Row(X, Y, W, H, nullptr)
{
    this->refresh(entries);
    this->end();
}

/// Refreshes the scoreboard.
//
// @pre none
// @post all entries are refreshed with input values
//
// @param entries the new entries to use
//
void HighScoreboardTable::refresh(vector<HighScoreEntry*> entries)
{
    this->entriesUsed = entries;

    this->rows(this->entriesUsed.size());
    this->row_height_all(20);
    this->cols(HIGH_SCORE_COLS);
    this->col_header(1);
    this->col_width_all(this->h() / HIGH_SCORE_COLS);

    this->redraw();
}

void HighScoreboardTable::drawHeader(const char *s, int X, int Y, int W, int H)
{
    fl_push_clip(X, Y, W, H);
    fl_draw_box(FL_THIN_UP_BOX, X, Y, W, H, row_header_color());
    fl_color(FL_BLACK);
    fl_draw(s, X, Y, W, H, FL_ALIGN_CENTER);
    fl_pop_clip();
}

void HighScoreboardTable::drawData(const char *s, int X, int Y, int W, int H)
{
    fl_push_clip(X, Y, W, H);
    // Draw cell bg
    fl_color(FL_WHITE);
    fl_rectf(X, Y, W, H);
    // Draw cell data
    fl_color(FL_BLACK);
    fl_draw(s, X, Y, W, H, FL_ALIGN_CENTER);
    // Draw box border
    fl_color(color());
    fl_rect(X, Y, W, H);
    fl_pop_clip();
}

void HighScoreboardTable::draw_cell(Fl_Table::TableContext context, int row, int col, int x, int y, int w, int h)
{
    switch (context)
    {
    case CONTEXT_STARTPAGE:                   // before page is drawn..
        fl_font(FL_HELVETICA, 14);              // set the font for our drawing operations
        return;
    case CONTEXT_COL_HEADER:                  // Draw column header
        switch (col)
        {
        case COLUMN_PLAYER:
            this->drawHeader("Player", x, y, w, h);
            break;
        case COLUMN_DURATION:
            this->drawHeader("Time Spent", x, y, w, h);
            break;
        case COLUMN_PUZZLE:
            this->drawHeader("Puzzle", x, y, w, h);
            break;
        default:
            break;
        }
        return;
    case CONTEXT_ROW_HEADER:                  // Draw row headers
        this->drawHeader(to_string(row + 1).c_str(), x, y, w, h);
        return;
    case CONTEXT_CELL:
    {
        auto *entry = this->entriesUsed[row];
        switch (col)
        {
        case COLUMN_PLAYER:
            this->drawData(entry->getName().c_str(), x, y, w, h);
            break;
        case COLUMN_DURATION:
            this->drawHeader(formatDurationHoursSeconds(entry->getDuration()).c_str(), x, y, w, h);
            break;
        case COLUMN_PUZZLE:
            this->drawHeader(to_string(entry->getPuzzle()).c_str(), x, y, w, h);
            break;
        default:
            break;
        }
        return;
    }
    default:
        break;
    }
}
}
