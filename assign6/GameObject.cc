#include "GameObject.h"
#include "Position.h"

GameObject::GameObject(Position pos)
: age(0), position(pos) {
    
}

GameObject::~GameObject() {

}

void GameObject::display() const {
    AnsiPrint(" ", black, black);
}

Position GameObject::getPosition() const {
    return position;
}