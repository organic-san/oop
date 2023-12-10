#include "World.h"
#include "GameObject.h"
#include "Grass.h"
#include "Goat.h"
#include <unistd.h>
#include <iostream>
#include <iomanip>

World::World(int numPasses, int seed) 
: numPasses(numPasses), round(0) {
    rnd = RandomNum(seed);
    for(int i = 0; i < worldSizeX; i++) {
        for(int j = 0; j < worldSizeY; j++) {
            map[i][j] = std::list<GameObject *>::iterator();
        }
    }

    // create initial objects
    for(int i = 0; i < 10; i++) {
        GameObject *goat = new Grass(randomPos());
        objectList.push_front(goat);
        map[goat->getPosition().X()][goat->getPosition().Y()] = objectList.begin();
    }
    for(int i = 0; i < 5; i++) {
        GameObject *wolf = new Goat(randomPos());
        objectList.push_front(wolf);
        map[wolf->getPosition().X()][wolf->getPosition().Y()] = objectList.begin();
    }
    
    // set map
    for(auto i = objectList.begin(); i != objectList.end(); ++i) {
        map[(*i)->getPosition().X()][(*i)->getPosition().Y()] = i;
    }
}

Position World::newPos(Position pos) const {
    // handle edge cases
    int moveDim = 0;
    moveDim |= pos.X() != 0 ? Dim::left : 0;
    moveDim |= pos.X() != worldSizeX - 1 ? Dim::right : 0;
    moveDim |= pos.Y() != 0 ? Dim::up : 0;
    moveDim |= pos.Y() != worldSizeY - 1 ? Dim::down : 0;
    int movePas = 0;
    for(int j = 0; j < 4; j++) {
        if(moveDim & (1 << j)) {
            movePas++;
        }
    }
    // decide the movement direction
    int moveDir = rnd.getRandomNum(1, movePas);
    int moveRoute = 0;
    for(int j = 0; j < 4; j++) {
        moveDir -= (moveDim & (1 << j)) ? 1 : 0;
        moveRoute |= moveDir == 0 ? (--moveDir, 1 << j) : 0;
    }
    const int newPosX = pos.X() + ((moveRoute & Dim::right) ? 1 : 0) - ((moveRoute & Dim::left) ? 1 : 0);
    const int newPosY = pos.Y() + ((moveRoute & Dim::down) ? 1 : 0) - ((moveRoute & Dim::up) ? 1 : 0);
    return Position(newPosX, newPosY);
}

Position World::randomPos() const {
    while(true) {
        Position pos = Position(rnd.getRandomNum(0, worldSizeX - 1), rnd.getRandomNum(0, worldSizeY - 1));
        if(map[pos.X()][pos.Y()] == std::list<GameObject *>::iterator()) {
            return pos;
        }
    }
}

void World::lifeCycle() {
    for(auto i = objectList.begin(); i != objectList.end(); ++i) {

        (*i)->update();

        // move
        if((*i)->shouldMove()) {
            const Position newPos = this->newPos((*i)->getPosition());

            auto& mapBlock = map[newPos.X()][newPos.Y()];
            auto target = mapBlock != std::list<GameObject *>::iterator() ? *mapBlock : nullptr;

            if(!target || (target->eatable() && (delete target, objectList.erase(mapBlock), (*i)->eat(), true))) {
                map[(*i)->getPosition().X()][(*i)->getPosition().Y()] = std::list<GameObject *>::iterator();
                mapBlock = i;
                (*i)->move(newPos);
            }
        }

        // make child and add to list and map
        if((*i)->shouldAddChild()) {
            const Position childPos = newPos((*i)->getPosition());

            auto& mapBlock = map[childPos.X()][childPos.Y()];
            auto target = mapBlock != std::list<GameObject *>::iterator() ? *mapBlock : nullptr;
 
            if (!target || (target->eatable() && (delete target, objectList.erase(mapBlock), (*i)->eat(), true))) {
                GameObject *child = (*i)->makeChild(childPos);
                objectList.push_front(child);
                map[child->getPosition().X()][child->getPosition().Y()] = objectList.begin();
            }
        }

        // remove object from list and map
        if((*i)->shouldDie()) {
            Position pos = (*i)->getPosition();
            delete (*i);
            auto temp = i;
            i++;
            objectList.erase(temp);
            i--;
            map[pos.X()][pos.Y()] = std::list<GameObject *>::iterator();
            continue;
        }
    }
}

void World::display() const {
    std::cout << "[" << std::setw(10) << round << "]" << std::endl;
    std::cout << " ";
    for(int i = 0; i < worldSizeX; i++) {
        std::cout << " " << (i % 10);
    }
    std::cout << std::endl;
    
    for(int i = 0; i < worldSizeY; i++) {
        std::cout << (i % 10);
        for(int j = 0; j < worldSizeX; j++) {
            if(map[j][i] == std::list<GameObject *>::iterator()) {
                std::cout << "  ";
            } else {
                std::cout << " "; 
                (*map[j][i]) -> display();
            }
        }
        std::cout << std::endl;
    }

    for(int i = 0; i < worldSizeX + 1; i++) {
        std::cout << "--";
    }
    std::cout << std::endl;
}

void World::mainLoop(int displayInterval) {
    
    for(int i = 0; i < numPasses; i++) {
        if(i % displayInterval == 0) {
            system("clear");
            display();
            usleep(50000);
        }

        lifeCycle();
        round++;
    }
    
}

