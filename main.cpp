#include <FL/Fl.H>
#include <FL/Fl_Window.H>

#include "./View/PuzzleGrid.h"

using namespace view;

int main (int argc, char ** argv)
{
  Fl_Window *window;
  PuzzleGrid *grid;

  window = new Fl_Window (500, 400, "Connect the Numbers by Smith, Williams, and Steinborn");
  grid = new PuzzleGrid (20, 40);

  window->end ();
  window->show (argc, argv);

  return(Fl::run());
}
