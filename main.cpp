#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <Fl/Fl_Export.H>

#include "MainGameWindow.h"
#include "./View/PuzzleGrid.h"
using namespace view;

/// Program launch point.
//
int main (int argc, char ** argv)
{
  MainGameWindow *window;

  window = new MainGameWindow(600, 425, "Connect the Numbers by Smith, Williams, and Steinborn");
  //window->color(fl_darker(fl_darker(fl_darker(FL_DARK_BLUE))));
  window->show();

  int exitCode = Fl::run();
  return exitCode;
}
