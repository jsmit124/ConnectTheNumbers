#include <FL/Fl_Window.H>

#include "View/MainGameWindow.h"
using namespace view;

/// Program launch point.
//
int main (int argc, char ** argv)
{
  MainGameWindow *window;

  window = new MainGameWindow(500, 575, "Connect the Numbers by Smith, Williams, and Steinborn");
  window->show();

  int exitCode = Fl::run();
  return exitCode;
}
