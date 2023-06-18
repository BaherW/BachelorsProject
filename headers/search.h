#pragma once

#include "globals.h"
#include "state.h"

class Searcher
{
public:
    int ply = 0;
    Move best_move;
    int nodes_searched = 0;
    int depth_searched;
    int stop_time;
    int timeout_flag = 0;

    void search(int depth, State state);

private:
    int alpha_beta(int depth, State& state, int alpha, int beta);
    int quiescent(State& state, int alpha, int beta);
    void check_timeout();
};
