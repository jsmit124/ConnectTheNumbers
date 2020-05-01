//
// Created by andrew on 5/1/20.
//

#include "HighScoresWindow.h"

namespace view
{

    HighScoresWindow::HighScoresWindow(GameManager *manager) : Fl_Window(500, 460, "High Scores")
    {
        this->manager = manager;
        this->table = new HighScoreboardTable(10, 10, 480, 400, this->manager->getTopTenScoresByDuration());
        this->clearButton = new Fl_Button(10, 420, 40, 30, "Clear");
        this->clearButton->callback(HighScoresWindow::cbClearClicked, this);
    }

    void HighScoresWindow::cbClearClicked(Fl_Widget *, void *data)
    {
        HighScoresWindow *window = (HighScoresWindow *) data;
        window->manager->clearHighScores();
        window->table->refresh(window->manager->getTopTenScoresByDuration());
    }

    HighScoresWindow::~HighScoresWindow() = default;
}