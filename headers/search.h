#pragma once

#include "globals.h"
#include "state.h"

class Searcher
{
public:
    int ply = 0;
    Move best_move;
    int nodes_searched = 0;

    void search(int depth, State state);

private:
    int alpha_beta(int depth, State& state, int alpha, int beta);
    int quiescent(State& state, int alpha, int beta);
};
