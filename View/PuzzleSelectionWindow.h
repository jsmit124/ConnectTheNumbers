#ifndef PUZZLESELECTIONWINDOW_H
#define PUZZLESELECTIONWINDOW_H

#include <Fl/Fl_Choice.H>
#include <Fl/Fl.H>
#include <Fl/Fl_Window.H>
#include <Fl/Fl_Button.H>
#include <Fl/fl_ask.H>
#include <string>
using namespace std;

class PuzzleSelectionWindow : public Fl_Window
{
    public:
        PuzzleSelectionWindow();
        virtual ~PuzzleSelectionWindow();

        int getPuzzleSelectionValue();
        void setPuzzleSelectionValue(int puzzleNumber);

    private:
        Fl_Choice* puzzleSelectionChoice;
        Fl_Button* okButton;
        Fl_Button* cancelButton;

        int puzzleSelectionValue;

        void addSelectionOptions();

        void okHandler();
        void cancelHandler();

        void setPuzzleSelectionLocation(int, int);
        void setOkButtonLocation(int, int);
        void setCancelButtonLocation(int, int);

        static void cbOk(Fl_Widget*, void*);
        static void cbCancel(Fl_Widget*, void*);

};

#endif // PUZZLESELECTIONWINDOW_H
