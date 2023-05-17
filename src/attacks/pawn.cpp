#pragma once
#include "../globals.h"
#include "../movelist.cpp"
#include "../state.cpp"

BitBoard pawn_attacks_mask(int square, int color)
{
    BitBoard attacks = BitBoard();
    BitBoard board = BitBoard();

    board.set_bit(square);

    if (color == WHITE)
    {
        if (((board >> 7) & NOT_A_FILE) != empty_board)
            attacks |= board >> 7;

        if (((board >> 9) & NOT_H_FILE) != empty_board)
            attacks |= board >> 9;
    }
    else if (color == BLACK)
    {
        if (((board << 9) & NOT_A_FILE) != empty_board)
            attacks |= board << 9;

        if (((board << 7) & NOT_H_FILE) != empty_board)
            attacks |= board << 7;
    }

    return attacks;
}

void init_pawn_attacks()
{
    for (int square = 0; square < BOARD_SIZE; square++)
    {
        if (square < 56)
            PAWN_ATTACKS[WHITE][square] = pawn_attacks_mask(square, WHITE);

        if (square > 7)
            PAWN_ATTACKS[BLACK][square] = pawn_attacks_mask(square, BLACK);
    }
}

void generate_pawn_moves(int color, MoveList &move_list, State &state)
{
    BitBoard board, attacks;
    int source, target;

    if (color == WHITE)
    {
        board = state.position.pieces[wPAWN];

        while (board != empty_board)
        {
            source = board.get_ls1b_index();
            target = source - 8;

            // Moves without capture
            if (!state.position.sides[BOTH].get_bit(target))
            {
                if (source >= a7 && source <= h7)
                {
                    // Promotion
                    move_list.add_move(Move(source, target, wPAWN, wKNIGHT, 0, 0, 0, 0));
                    move_list.add_move(Move(source, target, wPAWN, wBISHOP, 0, 0, 0, 0));
                    move_list.add_move(Move(source, target, wPAWN, wROOK, 0, 0, 0, 0));
                    move_list.add_move(Move(source, target, wPAWN, wQUEEN, 0, 0, 0, 0));
                }
                else
                {
                    // Single push
                    move_list.add_move(Move(source, target, wPAWN, 0, 0, 0, 0, 0));
                    // Double push
                    if (source >= a2 && source <= h2 && !state.position.sides[BOTH].get_bit(target - 8))
                        move_list.add_move(Move(source, target - 8, wPAWN, 0, 0, 1, 0, 0));
                }
            }
            // Moves with capture
            attacks = PAWN_ATTACKS[WHITE][source] & state.position.sides[BLACK];
            while (attacks != empty_board)
            {
                target = attacks.get_ls1b_index();

                if (source >= a7 && source <= h7)
                {
                    // Promotion
                    move_list.add_move(Move(source, target, wPAWN, wKNIGHT, 1, 0, 0, 0));
                    move_list.add_move(Move(source, target, wPAWN, wBISHOP, 1, 0, 0, 0));
                    move_list.add_move(Move(source, target, wPAWN, wROOK, 1, 0, 0, 0));
                    move_list.add_move(Move(source, target, wPAWN, wQUEEN, 1, 0, 0, 0));
                }
                else
                {
                    // Capture
                    move_list.add_move(Move(source, target, wPAWN, 0, 1, 0, 0, 0));
                }
                attacks.unset_bit(target);
            }
            // Enpassant capture
            if (state.enpassant != 0)
            {
                BitBoard enpassant_attacks = PAWN_ATTACKS[WHITE][source] & (BitBoard(1) << state.enpassant);
                if (enpassant_attacks != empty_board)
                {
                    target = enpassant_attacks.get_ls1b_index();
                    move_list.add_move(Move(source, target, wPAWN, 0, 1, 0, 1, 0));
                }
            }
            board.unset_bit(source);
        }
    }
    else
    {
        board = state.position.pieces[bPAWN];

        while (board != empty_board)
        {
            source = board.get_ls1b_index();
            target = source + 8;

            // Moves without capture
            if (!state.position.sides[BOTH].get_bit(target))
            {
                if (source >= a2 && source <= h2)
                {
                    // Promotion
                    move_list.add_move(Move(source, target, bPAWN, bKNIGHT, 0, 0, 0, 0));
                    move_list.add_move(Move(source, target, bPAWN, bBISHOP, 0, 0, 0, 0));
                    move_list.add_move(Move(source, target, bPAWN, bROOK, 0, 0, 0, 0));
                    move_list.add_move(Move(source, target, bPAWN, bQUEEN, 0, 0, 0, 0));
                }
                else
                {
                    // Single push
                    move_list.add_move(Move(source, target, bPAWN, 0, 0, 0, 0, 0));
                    // Double push
                    if (source >= a7 && source <= h7 && !state.position.sides[BOTH].get_bit(target + 8))
                        move_list.add_move(Move(source, target + 8, bPAWN, 0, 0, 1, 0, 0));
                }
            }
            // Moves with capture
            attacks = PAWN_ATTACKS[BLACK][source] & state.position.sides[WHITE];
            while (attacks != empty_board)
            {
                target = attacks.get_ls1b_index();

                if (source >= a2 && source <= h2)
                {
                    // Promotion
                    move_list.add_move(Move(source, target, bPAWN, bKNIGHT, 1, 0, 0, 0));
                    move_list.add_move(Move(source, target, bPAWN, bBISHOP, 1, 0, 0, 0));
                    move_list.add_move(Move(source, target, bPAWN, bROOK, 1, 0, 0, 0));
                    move_list.add_move(Move(source, target, bPAWN, bQUEEN, 1, 0, 0, 0));
                }
                else
                {
                    // Capture
                    move_list.add_move(Move(source, target, bPAWN, 0, 1, 0, 0, 0));
                }
                attacks.unset_bit(target);
            }
            // Enpassant capture
            if (state.enpassant != 0)
            {
                BitBoard enpassant_attacks = PAWN_ATTACKS[BLACK][source] & (BitBoard(1) << state.enpassant);
                if (enpassant_attacks != empty_board)
                {
                    target = enpassant_attacks.get_ls1b_index();
                    move_list.add_move(Move(source, target, bPAWN, 0, 1, 0, 1, 0));
                }
            }
            board.unset_bit(source);
        }
    }
}