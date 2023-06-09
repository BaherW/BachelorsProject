#pragma once

#include "globals.h"
#include "state.h"

extern BitBoard PAWN_ATTACKS[2][BOARD_SIZE];
extern BitBoard KNIGHT_ATTACKS[BOARD_SIZE];
extern BitBoard KING_ATTACKS[BOARD_SIZE];

BitBoard pawn_attacks_mask(int square, int color);
void generate_pawn_moves(int color, MoveList &move_list, State &state);

BitBoard knight_attacks_mask(int square);
void generate_knight_moves(int color, MoveList &move_list, State &state);

BitBoard king_attacks_mask(int square);
void generate_king_moves(int color, MoveList &move_list, State &state);

void init_normal_attacks();

BitBoard bishop_attacks_mask(int square, BitBoard blockers, int edges);
void generate_bishop_moves(int color, MoveList &move_list, State &state);

BitBoard rook_attacks_mask(int square, BitBoard blockers, int edges);
void generate_rook_moves(int color, MoveList &move_list, State &state);

void generate_queen_moves(int color, MoveList &move_list, State &state);