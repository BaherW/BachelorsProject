#include "../globals.h"

BitBoard pawn_attacks_mask(int square, int color)
{
    BitBoard attacks = BitBoard();
    BitBoard board = BitBoard();

    board.set_bit(square);

    if (color == WHITE)
    {
        if (((board >> 7) & NOT_A_FILE) != empty_board)
        {
            attacks |= board >> 7;
        }
        if (((board >> 9) & NOT_H_FILE) != empty_board)
        {
            attacks |= board >> 9;
        }
    }
    else if (color == BLACK)
    {
        if (((board << 9) & NOT_A_FILE) != empty_board)
        {
            attacks |= board << 9;
        }
        if (((board << 7) & NOT_H_FILE) != empty_board)
        {
            attacks |= board << 7;
        }
    }

    return attacks;
}
