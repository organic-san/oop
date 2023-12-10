#ifndef _POSITION_H
#define _POSITION_H

class Position {
public:
    Position(int x, int y);
    Position();
    Position(const Position& p);
    Position& operator=(const Position& p);
    bool operator==(const Position& p) const;
    bool operator!=(const Position& p) const;
    int X() const;
    int Y() const;

private:
    int x_;
    int y_;
};

#endif // _POSITION_H
