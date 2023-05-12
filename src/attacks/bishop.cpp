#include "../globals.h"


BitBoard bishop_attacks_mask(int square, BitBoard blockers = empty_board, int edges = 0)
{
    BitBoard attacks = BitBoard();
    BitBoard mask;
    int row, file;
    int max, min;

    if (edges == 0)
        max = 6, min = 1;
    else
        max = 7, min = 0;

    int original_square = square / 8;
    int original_file = square % 8;

    row = original_square + 1;
    file = original_file + 1;
    while (row <= max && file <= max)
    {
        mask = BitBoard(1) << (row * 8 + file);
        attacks |= mask;
        if (mask & blockers)
            break;
        row++, file++;
    }

    row = original_square - 1;
    file = original_file + 1;
    while (row >= min && file <= max)
    {
        mask = BitBoard(1) << (row * 8 + file);
        attacks |= mask;
        if (mask & blockers)
            break;
        row--, file++;
    }

    row = original_square + 1;
    file = original_file - 1;
    while (row <= max && file >= min)
    {
        mask = BitBoard(1) << (row * 8 + file);
        attacks |= mask;
        if (mask & blockers)
            break;
        row++, file--;
    }

    row = original_square - 1;
    file = original_file - 1;
    while (row >= min && file >= min)
    {
        mask = BitBoard(1) << (row * 8 + file);
        attacks |= mask;
        if (mask & blockers)
            break;
        row--, file--;
    }

    return attacks;
}
