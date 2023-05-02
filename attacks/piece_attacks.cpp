#include "pawn.cpp"
#include "knight.cpp"
#include "king.cpp"

vector<vector<BitBoard>> PAWN_MASKS(2, vector<BitBoard>(64));
vector<BitBoard> KNIGHT_MASKS(64);
vector<BitBoard> KING_MASKS(64);

void generate_leaping_attacks()
{
    for (int square = 0; square < 64; square++)
    {
        if (square < 56)
            PAWN_MASKS[WHITE][square] = pawn_attacks_mask(square, WHITE);

        if (square > 7)
            PAWN_MASKS[BLACK][square] = pawn_attacks_mask(square, BLACK);

        KNIGHT_MASKS[square] = knight_attacks_mask(square);
        KING_MASKS[square] = king_attacks_mask(square);
    }
}