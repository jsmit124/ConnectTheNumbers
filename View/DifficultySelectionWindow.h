#ifndef DIFFICULTYSELECTIONWINDOW_H
#define DIFFICULTYSELECTIONWINDOW_H

#include "../Enum/Difficulty.h"

#include <Fl/Fl_Choice.H>
#include <Fl/Fl.H>
#include <Fl/Fl_Window.H>
#include <Fl/Fl_Button.H>
#include <Fl/fl_ask.H>
#include <string>
using namespace std;

namespace view
{

class DifficultySelectionWindow : public Fl_Window
{
    public:
        DifficultySelectionWindow();
        virtual ~DifficultySelectionWindow();

        Difficulty getDifficultyValue();
        void setDifficultyValue(Difficulty puzzleNumber);

    private:
        Fl_Choice* difficultyChoice;
        Fl_Button* okButton;
        Fl_Button* cancelButton;

        Difficulty difficultyValue;

        void addDifficultyOptions();

        void okHandler();
        void cancelHandler();

        void setDifficultyLocation(int, int);
        void setOkButtonLocation(int, int);
        void setCancelButtonLocation(int, int);

        static void cbOk(Fl_Widget*, void*);
        static void cbCancel(Fl_Widget*, void*);
};

}

#endif // DIFFICULTYSELECTIONWINDOW_H
