#ifndef COLORSELECTIONWINDOW_H
#define COLORSELECTIONWINDOW_H

#include <Fl/Fl_Button.H>
#include <Fl/Fl_Window.H>
using namespace std;

namespace view
{

class ColorSelectionWindow : public Fl_Window
{
    public:
        ColorSelectionWindow();
        virtual ~ColorSelectionWindow();

        Fl_Color getColor();
        void setColor(Fl_Color);

    private:
        Fl_Color selectedColor;

        Fl_Button* blueButton;
        Fl_Button* greenButton;
        Fl_Button* redButton;
        Fl_Button* yellowButton;
        Fl_Button* cyanButton;
        Fl_Button* magentaButton;
        Fl_Button* cancelButton;

        void setBlueButtonLocation(int, int);
        void setGreenButtonLocation(int, int);
        void setRedButtonLocation(int, int);
        void setYellowButtonLocation(int, int);
        void setCyanButtonLocation(int, int);
        void setMagentaButtonLocation(int, int);
        void setCancelButtonLocation(int, int);

        static void cbBlue(Fl_Widget*, void*);
        static void cbGreen(Fl_Widget*, void*);
        static void cbRed(Fl_Widget*, void*);
        static void cbYellow(Fl_Widget*, void*);
        static void cbCyan(Fl_Widget*, void*);
        static void cbMagenta(Fl_Widget*, void*);
        static void cbCancel(Fl_Widget*, void*);
};

}

#endif // COLORSELECTIONWINDOW_H
