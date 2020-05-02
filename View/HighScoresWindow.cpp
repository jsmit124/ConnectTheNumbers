#include "HighScoresWindow.h"

namespace view
{

    HighScoresWindow::HighScoresWindow(GameManager *manager) : Fl_Window(420, 460, "High Scores")
    {
        this->manager = manager;
        this->sortBy = BY_DURATION;

        this->table = new HighScoreboardTable(10, 10, 400, 400, this->manager->getTopTenScoresByDuration());
        this->clearButton = new Fl_Button(350, 420, 60, 30, "Clear");
        this->sortChoice = new Fl_Choice(150, 420, 100, 30, "Sort: ");

        this->clearButton->callback(HighScoresWindow::cbClearClicked, this);
        this->sortChoice->callback(HighScoresWindow::cbSortChanged, this);

        this->sortChoice->add("Duration");
        this->sortChoice->add("Puzzle");
        this->sortChoice->value(0);

        this->applyColorScheme();
    }

    void HighScoresWindow::applyColorScheme()
    {
        auto settings = this->manager->getSettings();

        this->clearButton->color(settings->getButtonColor());
        this->clearButton->labelcolor(settings->getTextColor());

        this->sortChoice->labelcolor(settings->getTextColor());

        this->color(settings->getBackgroundColor());
    }

    void HighScoresWindow::cbClearClicked(Fl_Widget *, void *data)
    {
        HighScoresWindow *window = (HighScoresWindow *) data;
        window->manager->clearHighScores();
        window->refreshTableData();
    }

    void HighScoresWindow::refreshTableData()
    {
        vector<HighScoreEntry*> entries;
        switch (this->sortBy)
        {
            case BY_PUZZLE:
                entries = this->manager->getTopTenScoresByPuzzle();
                break;
            case BY_DURATION:
            default:
                entries = this->manager->getTopTenScoresByDuration();
                break;
        }

        this->table->refresh(entries);
    }

    HighScoresWindow::~HighScoresWindow()
    {
        delete this->clearButton;
        delete this->table;
        delete this->sortChoice;
    }

    void HighScoresWindow::cbSortChanged(Fl_Widget *, void *data)
    {
        auto *window = (HighScoresWindow *) data;
        switch (window->sortChoice->value())
        {
            case 0:
                window->sortBy = BY_DURATION;
                break;
            default:
                window->sortBy = BY_PUZZLE;
                break;
        }

        window->refreshTableData();
    }

}
