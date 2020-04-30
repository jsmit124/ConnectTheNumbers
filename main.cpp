#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <Fl/Fl_Export.H>

#include "./Controller/GameManager.h"
using namespace controller;

#include "./View/PuzzleGrid.h"
using namespace view;

/// Program launch point.
//
int main (int argc, char ** argv)
{
  Fl_Window *window;
  PuzzleGrid *grid;

  window = new Fl_Window (500, 400, "Connect the Numbers by Smith, Williams, and Steinborn");
  window->color(fl_darker(fl_darker(fl_darker(FL_DARK_BLUE))));
  grid = new PuzzleGrid (20, 0);

  window->end();
  window->show (argc, argv);

  return(Fl::run());
}
