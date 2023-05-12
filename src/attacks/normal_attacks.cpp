#pragma once
#include "pawn.cpp"
#include "knight.cpp"
#include "king.cpp"

BitBoard PAWN_ATTACKS[2][BOARD_SIZE];
BitBoard KNIGHT_ATTACKS[BOARD_SIZE];
BitBoard KING_ATTACKS[BOARD_SIZE];

void init_normal_attacks()
{
    for (int square = 0; square < BOARD_SIZE; square++)
    {
        if (square < 56)
            PAWN_ATTACKS[WHITE][square] = pawn_attacks_mask(square, WHITE);

        if (square > 7)
            PAWN_ATTACKS[BLACK][square] = pawn_attacks_mask(square, BLACK);

        KNIGHT_ATTACKS[square] = knight_attacks_mask(square);
        KING_ATTACKS[square] = king_attacks_mask(square);
    }
}