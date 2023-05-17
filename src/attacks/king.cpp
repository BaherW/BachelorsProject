#pragma once
#include "../globals.h"
#include "../movelist.cpp"
#include "../state.cpp"

BitBoard king_attacks_mask(int square)
{
    BitBoard attacks = BitBoard();
    BitBoard board = BitBoard();

    board.set_bit(square);

    if (((board >> 8)) != empty_board)
        attacks |= board >> 8;

    if (((board << 8)) != empty_board)
        attacks |= board << 8;

    if (((board >> 1) & NOT_H_FILE) != empty_board)
        attacks |= board >> 1;

    if (((board << 1) & NOT_A_FILE) != empty_board)
        attacks |= board << 1;

    if (((board >> 7) & NOT_A_FILE) != empty_board)
        attacks |= board >> 7;

    if (((board << 7) & NOT_H_FILE) != empty_board)
        attacks |= board << 7;

    if (((board >> 9) & NOT_H_FILE) != empty_board)
        attacks |= board >> 9;

    if (((board << 9) & NOT_A_FILE) != empty_board)
        attacks |= board << 9;

    return attacks;
}

void init_king_attacks()
{
    for (int square = 0; square < BOARD_SIZE; square++)
    {
        KING_ATTACKS[square] = king_attacks_mask(square);
    }
}

void generate_king_moves(int color, MoveList &move_list, State &state)
{
    BitBoard board, attacks;
    int source, target;

    if (color == WHITE)
    {
        board = state.position.pieces[wKING];

        while (board != empty_board)
        {
            source = board.get_ls1b_index();
            attacks = KING_ATTACKS[source] & !state.position.sides[WHITE];
            
            while (attacks != empty_board)
            {
                target = attacks.get_ls1b_index();

                if (!state.position.sides[BLACK].get_bit(target))
                    move_list.add_move(Move(source, target, wKING, 0, 0, 0, 0, 0));
                else
                    move_list.add_move(Move(source, target, wKING, 0, 1, 0, 0, 0));
                attacks.unset_bit(target);
            }
            board.unset_bit(source);
        }

        if (state.castling.wk_can_castle())
        {
            if (!state.position.sides[BOTH].get_bit(f1) && !state.position.sides[BOTH].get_bit(g1))
            {
                if (!state.position.is_square_attacked(e1, BLACK) && !state.position.is_square_attacked(f1, BLACK))
                    move_list.add_move(Move(e1, g1, wKING, 0, 0, 0, 0, 1));
            }
        }
        if (state.castling.wq_can_castle())
        {
            if (!state.position.sides[BOTH].get_bit(d1) && !state.position.sides[BOTH].get_bit(c1) && !state.position.sides[BOTH].get_bit(b1))
            {
                if (!state.position.is_square_attacked(e1, BLACK) && !state.position.is_square_attacked(d1, BLACK))
                    move_list.add_move(Move(e1, c1, wKING, 0, 0, 0, 0, 1));
            }
        }
    }
    else
    {
        board = state.position.pieces[bKING];

        while (board != empty_board)
        {
            source = board.get_ls1b_index();
            attacks = KING_ATTACKS[source] & !state.position.sides[BLACK];
            
            while (attacks != empty_board)
            {
                target = attacks.get_ls1b_index();

                if (!state.position.sides[WHITE].get_bit(target))
                    move_list.add_move(Move(source, target, bKING, 0, 0, 0, 0, 0));
                else
                    move_list.add_move(Move(source, target, bKING, 0, 1, 0, 0, 0));
                attacks.unset_bit(target);
            }
            board.unset_bit(source);
        }

        if (state.castling.bk_can_castle())
        {
            if (!state.position.sides[BOTH].get_bit(f8) && !state.position.sides[BOTH].get_bit(g8))
            {
                if (!state.position.is_square_attacked(e8, WHITE) && !state.position.is_square_attacked(f8, WHITE))
                    move_list.add_move(Move(e8, g8, bKING, 0, 0, 0, 0, 1));
            }
        }
        if (state.castling.bq_can_castle())
        {
            if (!state.position.sides[BOTH].get_bit(d8) && !state.position.sides[BOTH].get_bit(c8) && !state.position.sides[BOTH].get_bit(b8))
            {
                if (!state.position.is_square_attacked(e8, WHITE) && !state.position.is_square_attacked(d8, WHITE))
                    move_list.add_move(Move(e8, c8, bKING, 0, 0, 0, 0, 1));
            }
        }
    }
}