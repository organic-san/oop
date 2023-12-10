#ifndef _GRASS_H
#define _GRASS_H

#include "GameObject.h"

class Grass : public GameObject {

    static const int ageMax = 6;
    static const int makeChildMin = 3;
    static const int makeChildMax = 5;

public:
    Grass(Position pos);
    ~Grass();

    void display() const;

    void update();

    bool shouldMove() const;

    void move(Position newPos);

    bool eatable() const;

    void eat();

    bool shouldAddChild() const;

    Grass* makeChild(Position pos);

    bool shouldDie() const;
};

#endif // _GRASS_H