#ifndef COLORSELECTIONWINDOW_H
#define COLORSELECTIONWINDOW_H

#include <Fl/Fl_Button.H>
#include <Fl/Fl_Window.H>
using namespace std;

namespace view
{

/// UI window with buttons for allowing user to select a color
//
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
        Fl_Button* darkButton;
        Fl_Button* whiteButton;
        Fl_Button* yellowButton;
        Fl_Button* cyanButton;
        Fl_Button* magentaButton;
        Fl_Button* cancelButton;

        static void cbBlue(Fl_Widget*, void*);
        static void cbDark(Fl_Widget*, void*);
        static void cbWhite(Fl_Widget*, void*);
        static void cbYellow(Fl_Widget*, void*);
        static void cbCyan(Fl_Widget*, void*);
        static void cbMagenta(Fl_Widget*, void*);
        static void cbCancel(Fl_Widget*, void*);
        static void cbOnWindowClose(Fl_Widget*, void*);
};

}

#endif // COLORSELECTIONWINDOW_H
