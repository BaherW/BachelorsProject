#include "../globals.h"

BitBoard knight_attacks_mask(int square)
{
    BitBoard attacks = BitBoard();
    BitBoard board = BitBoard();

    board.set_bit(square);

    if (((board >> 17) & NOT_H_FILE) != empty_board)
        attacks |= board >> 17;

    if (((board >> 15) & NOT_A_FILE) != empty_board)
        attacks |= board >> 15;

    if (((board >> 10) & NOT_GH_FILE) != empty_board)
        attacks |= board >> 10;

    if (((board >> 6) & NOT_AB_FILE) != empty_board)
        attacks |= board >> 6;

    if (((board << 17) & NOT_A_FILE) != empty_board)
        attacks |= board << 17;

    if (((board << 15) & NOT_H_FILE) != empty_board)
        attacks |= board << 15;

    if (((board << 10) & NOT_AB_FILE) != empty_board)
        attacks |= board << 10;

    if (((board << 6) & NOT_GH_FILE) != empty_board)
        attacks |= board << 6;

    return attacks;
}
