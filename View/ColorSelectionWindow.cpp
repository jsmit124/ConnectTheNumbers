#include "ColorSelectionWindow.h"

namespace view
{

ColorSelectionWindow::ColorSelectionWindow() : Fl_Window(250, 325, "Select a color")
{
        this->blueButton = new Fl_Button(25, 25, 200, 30, "Blue");
        this->darkButton = new Fl_Button(25, 67, 200, 30, "Dark");
        this->lightBlueButton = new Fl_Button(25, 109, 200, 30, "Light Blue");
        this->yellowButton = new Fl_Button(25, 151, 200, 30, "Yellow");
        this->cyanButton = new Fl_Button(25,193, 200, 30, "Cyan");
        this->magentaButton = new Fl_Button(25, 235, 200, 30, "Magenta");
        this->cancelButton = new Fl_Button(25, 277, 200, 30,"Cancel");

        this->blueButton->callback(cbBlue, this);
        this->darkButton->callback(cbDark, this);
        this->lightBlueButton->callback(cbLightBlue, this);
        this->yellowButton->callback(cbYellow, this);
        this->cyanButton->callback(cbCyan, this);
        this->magentaButton->callback(cbMagenta, this);
        this->cancelButton->callback(cbCancel, this);
}

Fl_Color ColorSelectionWindow::getColor()
{
    return this->selectedColor;
}

void ColorSelectionWindow::setColor(Fl_Color color)
{
    this->selectedColor = color;
}

void ColorSelectionWindow::cbBlue(Fl_Widget* widget, void* data)
{
    ColorSelectionWindow* window = (ColorSelectionWindow*)data;
    window->setColor(FL_DARK_BLUE);
    window->hide();
}

void ColorSelectionWindow::cbDark(Fl_Widget* widget, void* data)
{
    ColorSelectionWindow* window = (ColorSelectionWindow*)data;
    window->setColor(FL_DARK3);
    window->hide();
}

void ColorSelectionWindow::cbLightBlue(Fl_Widget* widget, void* data)
{
    ColorSelectionWindow* window = (ColorSelectionWindow*)data;
    window->setColor(FL_BLUE);
    window->hide();
}

void ColorSelectionWindow::cbYellow(Fl_Widget* widget, void* data)
{
    ColorSelectionWindow* window = (ColorSelectionWindow*)data;
    window->setColor(FL_DARK_YELLOW);
    window->hide();
}

void ColorSelectionWindow::cbCyan(Fl_Widget* widget, void* data)
{
    ColorSelectionWindow* window = (ColorSelectionWindow*)data;
    window->setColor(FL_DARK_CYAN);
    window->hide();
}

void ColorSelectionWindow::cbMagenta(Fl_Widget* widget, void* data)
{
    ColorSelectionWindow* window = (ColorSelectionWindow*)data;
    window->setColor(FL_DARK_MAGENTA);
    window->hide();
}

void ColorSelectionWindow::cbCancel(Fl_Widget* widget, void* data)
{
    ColorSelectionWindow* window = (ColorSelectionWindow*)data;
    window->hide();
}

ColorSelectionWindow::~ColorSelectionWindow()
{
    delete this->blueButton;
    delete this->darkButton;
    delete this->lightBlueButton;
    delete this->yellowButton;
    delete this->cyanButton;
    delete this->magentaButton;
    delete this->cancelButton;
}

}
