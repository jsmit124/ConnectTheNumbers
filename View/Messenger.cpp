#include "Messenger.h"

namespace view
{

Messenger::Messenger() = default;
Messenger::~Messenger() = default;

/// Returns a puzzle message dialog based on the time completed
// @param timeCompleted: the time completed
// @post: dialog shown with msg
void Messenger::showPuzzleEndMessage(int timeCompleted)
{
    int minute = 60;
    string message;

    if (timeCompleted <= minute)
    {
        fl_message("Wow.. that was impressive.");
    }
    else if (timeCompleted <= minute * 2)
    {
        fl_message("Not bad, not bad...");
    }
    else if (timeCompleted <= minute * 3)
    {
        fl_message("Not slow, not fast, just average.");
    }
    else if (timeCompleted <= minute * 4)
    {
        fl_message("You're just plain EG-NO-RA-MOOSE.");
    }
    else
    {
        fl_message("Yikes!");
    }
}

}
