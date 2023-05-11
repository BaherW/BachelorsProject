#include "pawn.cpp"
#include "knight.cpp"
#include "king.cpp"

BitBoard PAWN_MASKS[2][BOARD_SIZE];
BitBoard KNIGHT_MASKS[BOARD_SIZE];
BitBoard KING_MASKS[BOARD_SIZE];

void init_normal_attacks()
{
    for (int square = 0; square < BOARD_SIZE; square++)
    {
        if (square < 56)
            PAWN_MASKS[WHITE][square] = pawn_attacks_mask(square, WHITE);

        if (square > 7)
            PAWN_MASKS[BLACK][square] = pawn_attacks_mask(square, BLACK);

        KNIGHT_MASKS[square] = knight_attacks_mask(square);
        KING_MASKS[square] = king_attacks_mask(square);
    }
}