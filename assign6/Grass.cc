#include "Grass.h"
#include "GameObject.h"

Grass::Grass(Position pos): GameObject(pos) {

}

Grass::~Grass() {

}

void Grass::display() const {
    AnsiPrint("I", green, black);
}

void Grass::update() {
    age++;
}

bool Grass::shouldMove() const {
    return false;
}

void Grass::move(Position newPos) {
    // never move
}

void Grass::eat() {
    // never eat
}

bool Grass::eatable() const {
    return true;
}

bool Grass::shouldAddChild() const {
    return age >= makeChildMin && age <= makeChildMax;
}

bool Grass::shouldDie() const {
    return age >= ageMax;
}

Grass* Grass::makeChild(Position pos) {
    return new Grass(pos);
}