#pragma once

#include "globals.h"
#include "state.h"

enum
{
opening,
endgame,
middlegame
};

extern const int opening_phase_score;
extern const int endgame_phase_score;

extern const int piece_value[2][12];

extern const int pst[2][6][64];

int eval(State &state);