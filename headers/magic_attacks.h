#pragma once

#include "globals.h"

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
