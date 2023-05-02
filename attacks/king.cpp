#include "../globals.h"

BitBoard king_attacks_mask(int square)
{
    BitBoard attacks = BitBoard();
    BitBoard board = BitBoard();

    board.set_bit(square);

    if (((board >> 8)) != empty_board) {
        attacks |= board >> 8;
    }
    if (((board << 8)) != empty_board) {
        attacks |= board << 8;
    }
    if (((board >> 1) & NOT_H_FILE) != empty_board) {
        attacks |= board >> 1;
    }
    if (((board << 1) & NOT_A_FILE) != empty_board) {
        attacks |= board << 1;
    }
    if (((board >> 7) & NOT_A_FILE) != empty_board) {
        attacks |= board >> 7;
    }
    if (((board << 7) & NOT_H_FILE) != empty_board) {
        attacks |= board << 7;
    }
    if (((board >> 9) & NOT_H_FILE) != empty_board) {
        attacks |= board >> 9;
    }
    if (((board << 9) & NOT_A_FILE) != empty_board) {
        attacks |= board << 9;
    }
    
    return attacks;
}
