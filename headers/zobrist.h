#pragma once

#include "globals.h"
#include "state.h"

extern U64 pieces_key[12][BOARD_SIZE];
extern U64 castling_key[16];
extern U64 en_passant_key[BOARD_SIZE];
extern U64 current_color_key;

void init_keys();