#include "../globals.h"

BitBoard rook_attacks_mask(int square, BitBoard blockers = empty_board)
{
    BitBoard attacks = BitBoard();
    BitBoard mask;
    int row, file;
    int max, min;

    if (blockers == empty_board)
        max = 6, min = 1;
    else
        max = 7, min = 0;

    for (row = (square / 8) + 1; row <= max; ++row)
    {
        mask = BitBoard(1) << (row * 8 + (square % 8));
        attacks |= mask;
        if (mask & blockers)
            break;
    }

    for (row = (square / 8) - 1; row >= min; --row)
    {
        mask = BitBoard(1) << (row * 8 + (square % 8));
        attacks |= mask;
        if (mask & blockers)
            break;
    }

    for (file = (square % 8) + 1; file <= max; ++file)
    {
        mask = BitBoard(1) << ((square / 8) * 8 + file);
        attacks |= mask;
        if (mask & blockers)
            break;
    }

    for (file = (square % 8) - 1; file >= min; --file)
    {
        mask = BitBoard(1) << ((square / 8) * 8 + file);
        attacks |= mask;
        if (mask & blockers)
            break;
    }

    return attacks;
}
