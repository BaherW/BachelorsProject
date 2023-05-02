#include "../globals.h"

BitBoard rook_attacks_mask(int square)
{
    BitBoard occupancy = BitBoard();

    int row, file;

    for (row = (square / 8) + 1; row <= 6; ++row) 
        occupancy |= BitBoard(1) << (row * 8 + (square % 8));

    for (row = (square / 8) - 1; row >= 1; --row) 
        occupancy |= BitBoard(1) << (row * 8 + (square % 8));

    for (file = (square % 8) + 1; file <= 6; ++file) 
        occupancy |= BitBoard(1) << ((square / 8) * 8 + file);
    
    for (file = (square % 8) - 1; file >= 1; --file) 
        occupancy |= BitBoard(1) << ((square / 8) * 8 + file);

    return occupancy;
}
