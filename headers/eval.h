#pragma once

#include "globals.h"
#include "state.h"

enum
{
opening,
endgame,
middlegame
};

void init_pesto_tables();
int eval(State &state);