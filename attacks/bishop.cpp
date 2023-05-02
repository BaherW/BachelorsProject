#include "../globals.h"

BitBoard bishop_attacks_mask(int square)
{
    BitBoard occupancy = BitBoard();

    int row, file;

    row = square / 8 + 1;
    file = square % 8 + 1;
    while (row <= 6 && file <= 6)
        occupancy |= BitBoard(1) << (row++ * 8 + file++);

    row = square / 8 - 1;
    file = square % 8 + 1;
    while (row >= 1 && file <= 6)
        occupancy |= BitBoard(1) << (row-- * 8 + file++);

    row = square / 8 + 1;
    file = square % 8 - 1;
    while (row <= 6 && file >= 1)
        occupancy |= BitBoard(1) << (row++ * 8 + file--);

    row = square / 8 - 1;
    file = square % 8 - 1;
    while (row >= 1 && file >= 1)
        occupancy |= BitBoard(1) << (row-- * 8 + file--);

    return occupancy;
}