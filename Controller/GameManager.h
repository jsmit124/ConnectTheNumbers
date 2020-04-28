#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "../Model/PuzzleManager.h"
using namespace model;

namespace controller
{

/// Manages the current Game state
//
class GameManager
{
    private:
        PuzzleManager puzzleManager;

    public:
        GameManager();
        virtual ~GameManager();
};

}

#endif // GAMEMANAGER_H
