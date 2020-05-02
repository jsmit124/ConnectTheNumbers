#ifndef PUZZLEGRIDBUTTON_H
#define PUZZLEGRIDBUTTON_H

#include <FL/Fl_Button.H>
using namespace std;

namespace view {

/// Handles implementation of the PuzzleGridButton button widget
//
class PuzzleGridButton : public Fl_Button
{

    public:
        PuzzleGridButton(int x, int y, int width, int height, int inputID);
        virtual ~PuzzleGridButton();

        void setColors(Fl_Color* background, Fl_Color* label);
        int getID();

    private:
        int ID;

};

}

#endif // PUZZLEGRIDBUTTON_H
