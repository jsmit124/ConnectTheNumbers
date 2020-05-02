#ifndef MESSENGER_H
#define MESSENGER_H

#include <FL/fl_ask.H>
#include <vector>
#include <string>
using namespace std;

namespace view
{

class Messenger
{
    private:
        vector<string> puzzleEndMessages;
        void addPuzzleEndMessages();

    public:
        Messenger();
        virtual ~Messenger();

        void showPuzzleEndMessage(int timeCompleted);
};

}

#endif // MESSENGER_H
