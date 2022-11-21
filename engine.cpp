#include "globals.h"
#include "state.cpp"

int main()
{
    State state = State("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
    state.print();
}