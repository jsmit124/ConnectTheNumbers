#include "Messenger.h"

namespace view
{

Messenger::Messenger()
{
    this->addPuzzleEndMessages();
}

Messenger::~Messenger()
{
}

void Messenger::showPuzzleEndMessage(int timeCompleted)
{
    int minute = 60;
    string message;

    if (timeCompleted <= minute)
    {
        message = this->puzzleEndMessages.at(0);
    }
    else if (timeCompleted <= minute * 2)
    {
        message = this->puzzleEndMessages.at(1);
    }
    else if (timeCompleted <= minute * 3)
    {
        message = this->puzzleEndMessages.at(2);
    }
    else if (timeCompleted <= minute * 4)
    {
        message = this->puzzleEndMessages.at(3);
    }
    else
    {
        message = this->puzzleEndMessages.at(4);
    }

    fl_message(message.c_str());
}

void Messenger::addPuzzleEndMessages()
{
    this->puzzleEndMessages.push_back("Wow.. that was impressive.");
    this->puzzleEndMessages.push_back("Not bad, not bad...");
    this->puzzleEndMessages.push_back("Not slow, not fast, just average.");
    this->puzzleEndMessages.push_back("You're just plain EG-NO-RA-MOOSE.");
    this->puzzleEndMessages.push_back("Yikes!");
}

}
