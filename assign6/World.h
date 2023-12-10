#ifndef _WORLD_H
#define _WORLD_H

#include "GameObject.h"
#include "RandomNum.h"
#include <array>
#include <list>

enum Dim {
    up = 1, down = 2, left = 4, right = 8
};

class World {
    int numPasses;
    int round;

    void lifeCycle();
    void display() const;
    Position newPos(Position pos) const;
    Position randomPos() const;

    static const int worldSizeX = 35;
    static const int worldSizeY = 20;
    RandomNum rnd;

    // map data structure that stores dara using list iterators
    // when map[i][j] == list<GameObject *>::iterator(), it means that there is no object at (i, j)
    std::list<GameObject *> objectList;
    std::array<
        std::array<
            std::list<GameObject *>::iterator, 
            worldSizeY
        >, worldSizeX
    > map;

public:
    World(int numPasses, int seed = 0);
    void mainLoop(int displayInterval);
};

#endif // _WORLD_H