#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H

#include <string>
#include "Position.h"
#include "AnsiPrint.h"

class GameObject {

protected:
    int age;
    Position position;

public:
    GameObject(Position pos);
    virtual ~GameObject();

    Position getPosition() const;

    // return the object's view
    virtual void display() const;

    virtual void update() = 0;

    // return true if the object should be moved
    virtual bool shouldMove() const = 0;

    virtual void move(Position newPos) = 0;

    // return true if the object is eatable
    virtual bool eatable() const = 0;

    virtual void eat() = 0;

    // return true if the object should be added child to the game
    virtual bool shouldAddChild() const = 0;

    // return child object
    virtual GameObject* makeChild(Position pos) = 0;

    // return true if the object should be removed from the game
    virtual bool shouldDie() const = 0;
};

#endif // _GAMEOBJECT_H