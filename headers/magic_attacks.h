#pragma once

#include "attacks.h"

extern BitBoard BISHOP_MASKS[BOARD_SIZE];
extern BitBoard ROOK_MASKS[BOARD_SIZE];

extern int RELEVANT_OCCUPANCY_BISHOP[BOARD_SIZE];
extern int RELEVANT_OCCUPANCY_ROOK[BOARD_SIZE];

extern BitBoard BISHOP_MAGICS[BOARD_SIZE];
extern BitBoard ROOK_MAGICS[BOARD_SIZE];

extern BitBoard BISHOP_ATTACKS[64][512];
extern BitBoard ROOK_ATTACKS[64][4096];

extern BitBoard BISHOP_SAVED_MAGICS[BOARD_SIZE];
extern BitBoard ROOK_SAVED_MAGICS[BOARD_SIZE];

BitBoard generate_random_magic();
BitBoard get_occupancy_bitboard(int index, int attack_mask_bits, BitBoard attack_mask);
BitBoard find_magic_number(int square, int relevant_bits, int bishop);
void init_magic_numbers();
void init_attacks();
void init_magic_attacks();
BitBoard get_bishop_attacks(const int& square, BitBoard occupancy);
BitBoard get_rook_attacks(const int& square, BitBoard occupancy);
BitBoard get_queen_attacks(const int& square, BitBoard occupancy);
