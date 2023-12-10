#include "position.h"

Position::Position(int x, int y) : x_(x), y_(y) {}

Position::Position() : x_(0), y_(0) {}

Position::Position(const Position& p) : x_(p.X()), y_(p.Y()) {}

Position& Position::operator=(const Position& p) {
    x_ = p.X();
    y_ = p.Y();
    return *this;
}

bool Position::operator==(const Position& p) const {
    return x_ == p.X() && y_ == p.Y();
}

bool Position::operator!=(const Position& p) const {
    return !(*this == p);
}

int Position::X() const {
    return x_;
}

int Position::Y() const {
    return y_;
}
