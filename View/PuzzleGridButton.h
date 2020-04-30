#ifndef PUZZLEGRIDBUTTON_H
#define PUZZLEGRIDBUTTON_H

#include <FL/Fl_Button.H>
using namespace std;

namespace view {

class PuzzleGridButton : public Fl_Button
{
    public:
        PuzzleGridButton(int x, int y, int width, int height, int inputID);
        virtual ~PuzzleGridButton();

        int getID();

    private:
        int ID;
};

}

#endif // PUZZLEGRIDBUTTON_H
