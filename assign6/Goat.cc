#include "Goat.h"
#include "GameObject.h"

Goat::Goat(Position pos): GameObject(pos) {
    foodPoints = 20;
}

Goat::~Goat() {
    
}

void Goat::display() const {
    AnsiPrint("X", red, black);
}

void Goat::update() {
    age++;
    foodPoints--;
}

bool Goat::shouldMove() const {
    return (age >= makeChildMin && age <= makeChildMax) ? false : true;
}

void Goat::move(Position newPos) {
    position = newPos;
}

void Goat::eat() {
    foodPoints += foodPointsFromFoods;
}

bool Goat::eatable() const {
    return false;
}

bool Goat::shouldAddChild() const {
    return age >= makeChildMin && age <= makeChildMax;
}

bool Goat::shouldDie() const {
    return age >= ageMax || foodPoints <= 0;
}

Goat* Goat::makeChild(Position pos) {
    return new Goat(pos);
}


