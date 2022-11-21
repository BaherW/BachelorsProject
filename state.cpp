#include "globals.h"
#include "position.cpp"

class State
{
public:
    Position pos;
    int currentColor;

    State(string fen)
    {
        currentColor = WHITE;
        pos = Position(fen);
    }

    void print()
    {
        pos.print();
    }
};