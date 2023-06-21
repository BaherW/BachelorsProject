#pragma once

#include "globals.h"
#include "move.h"
#include <algorithm>

class State;

static int MVV_LVA[12][12] = {
    105, 205, 305, 405, 505, 605, 105, 205, 305, 405, 505, 605,
    104, 204, 304, 404, 504, 604, 104, 204, 304, 404, 504, 604,
    103, 203, 303, 403, 503, 603, 103, 203, 303, 403, 503, 603,
    102, 202, 302, 402, 502, 602, 102, 202, 302, 402, 502, 602,
    101, 201, 301, 401, 501, 601, 101, 201, 301, 401, 501, 601,
    100, 200, 300, 400, 500, 600, 100, 200, 300, 400, 500, 600,

    105, 205, 305, 405, 505, 605, 105, 205, 305, 405, 505, 605,
    104, 204, 304, 404, 504, 604, 104, 204, 304, 404, 504, 604,
    103, 203, 303, 403, 503, 603, 103, 203, 303, 403, 503, 603,
    102, 202, 302, 402, 502, 602, 102, 202, 302, 402, 502, 602,
    101, 201, 301, 401, 501, 601, 101, 201, 301, 401, 501, 601,
    100, 200, 300, 400, 500, 600, 100, 200, 300, 400, 500, 600};

int score_move(State &state, const Move &move);
static bool compare_moves(State &state, const Move &move1, const Move &move2);

class MoveList
{
public:
    Move moves[MAX_MOVES];
    int num_moves;
    bool captures_only;

    MoveList(bool captures = false);

    void add_move(Move new_move);

    Move get_move(const string &move_string);

    void sort_moves(State &state);

    void print();
};
