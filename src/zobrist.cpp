#include "../headers/zobrist.h"

U64 pieces_key[12][BOARD_SIZE];
U64 castling_key[16];
U64 en_passant_key[BOARD_SIZE];
U64 current_color_key;

void init_keys()
{
    for (int p = wPAWN; p <= bKING; p++)
    {
        for (int square = 0; square < BOARD_SIZE; square++)
        {
            pieces_key[p][square] = random_U64();
        }
    }

    for (int i = 0; i < 16; i++)
        castling_key[i] = random_U64();

    for (int square = 0; square < BOARD_SIZE; square++)
        en_passant_key[square] = random_U64();

    current_color_key = random_U64();
}
