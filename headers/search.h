#pragma once

#include "globals.h"
#include "state.h"

class Searcher
{
public:
    Move best_move;
    int nodes_searched = 0;
    int depth_searched;
    
    void search(int depth, State state);

private:
    int stop_time;
    int timeout_flag = 0;
    int ply = 0;

    int alpha_beta(int depth, State& state, int alpha, int beta);
    int quiescent(State& state, int alpha, int beta);
    void check_timeout();
};
