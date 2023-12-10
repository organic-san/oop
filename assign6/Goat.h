#ifndef _GOAT_H
#define _GOAT_H

#include "GameObject.h"

class Goat : public GameObject {

    
    static const int ageMax = 70;
    static const int makeChildMin = 50;
    static const int makeChildMax = 55;

    int foodPoints;

    static const int foodPointsFromFoods = 5;

public:
    Goat(Position pos);
    ~Goat();
    
    void display() const;

    void update();

    bool shouldMove() const;

    void move(Position newPos);

    bool eatable() const;

    void eat();

    bool shouldAddChild() const;

    Goat* makeChild(Position pos);

    bool shouldDie() const;
};

#endif // _GOAT_H