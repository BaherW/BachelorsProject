#include "../headers/attacks.h"
#include "../headers/magic_attacks.h"

// Attack Masks
BitBoard PAWN_ATTACKS[2][BOARD_SIZE];
BitBoard KNIGHT_ATTACKS[BOARD_SIZE];
BitBoard KING_ATTACKS[BOARD_SIZE];

BitBoard pawn_attacks_mask(int square, int color)
{
    BitBoard attacks = EMPTY_BOARD;
    BitBoard board = EMPTY_BOARD;

    board.set_bit(square);

    if (color == WHITE)
    {
        // Capture left
        if (((board >> 7) & NOT_A_FILE))
            attacks |= board >> 7;

        // Capture right
        if (((board >> 9) & NOT_H_FILE))
            attacks |= board >> 9;
    }
    else if (color == BLACK)
    {
        // Capture right
        if (((board << 9) & NOT_A_FILE))
            attacks |= board << 9;

        // Capture left
        if (((board << 7) & NOT_H_FILE))
            attacks |= board << 7;
    }

    return attacks;
}

void generate_pawn_moves(int color, MoveList &move_list, State &state)
{
    BitBoard board, attacks;
    int source, target;

    if (color == WHITE)
    {
        board = state.position.pieces[wPAWN];

        while (board)
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
            while (attacks)
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
                BitBoard enpassant_square;
                enpassant_square.set_bit(state.enpassant);
                BitBoard enpassant_attacks = PAWN_ATTACKS[WHITE][source] & enpassant_square;
                if (enpassant_attacks)
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

        while (board)
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
            while (attacks)
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
                BitBoard enpassant_square;
                enpassant_square.set_bit(state.enpassant);
                BitBoard enpassant_attacks = PAWN_ATTACKS[BLACK][source] & enpassant_square;
                if (enpassant_attacks)
                {
                    target = enpassant_attacks.get_ls1b_index();
                    move_list.add_move(Move(source, target, bPAWN, 0, 1, 0, 1, 0));
                }
            }
            board.unset_bit(source);
        }
    }
}

BitBoard knight_attacks_mask(int square)
{
    BitBoard attacks = EMPTY_BOARD;
    BitBoard board = EMPTY_BOARD;

    board.set_bit(square);

    // All 8 movement directions
    if ((board >> 17) & NOT_H_FILE)
        attacks |= board >> 17;

    if ((board >> 15) & NOT_A_FILE)
        attacks |= board >> 15;

    if ((board >> 10) & NOT_GH_FILE)
        attacks |= board >> 10;

    if ((board >> 6) & NOT_AB_FILE)
        attacks |= board >> 6;

    if ((board << 17) & NOT_A_FILE)
        attacks |= board << 17;

    if ((board << 15) & NOT_H_FILE)
        attacks |= board << 15;

    if ((board << 10) & NOT_AB_FILE)
        attacks |= board << 10;

    if ((board << 6) & NOT_GH_FILE)
        attacks |= board << 6;

    return attacks;
}

void generate_knight_moves(int color, MoveList &move_list, State &state)
{
    BitBoard board, attacks;
    int source, target;

    if (color == WHITE)
    {
        board = state.position.pieces[wKNIGHT];

        while (board)
        {
            source = board.get_ls1b_index();
            attacks = KNIGHT_ATTACKS[source] & !state.position.sides[WHITE];

            while (attacks)
            {
                target = attacks.get_ls1b_index();

                if (!state.position.sides[BLACK].get_bit(target))
                    // No capture flag if target square is empty
                    move_list.add_move(Move(source, target, wKNIGHT, 0, 0, 0, 0, 0));
                else
                    move_list.add_move(Move(source, target, wKNIGHT, 0, 1, 0, 0, 0));
                attacks.unset_bit(target);
            }
            board.unset_bit(source);
        }
    }
    else
    {
        board = state.position.pieces[bKNIGHT];

        while (board)
        {
            source = board.get_ls1b_index();
            attacks = KNIGHT_ATTACKS[source] & !state.position.sides[BLACK];

            while (attacks)
            {
                target = attacks.get_ls1b_index();

                if (!state.position.sides[WHITE].get_bit(target))
                    // No capture flag if target square is empty
                    move_list.add_move(Move(source, target, bKNIGHT, 0, 0, 0, 0, 0));
                else
                    move_list.add_move(Move(source, target, bKNIGHT, 0, 1, 0, 0, 0));
                attacks.unset_bit(target);
            }
            board.unset_bit(source);
        }
    }
}

BitBoard king_attacks_mask(int square)
{
    BitBoard attacks = EMPTY_BOARD;
    BitBoard board = EMPTY_BOARD;

    board.set_bit(square);

    // All 8 movement directions
    if (board >> 8)
        attacks |= board >> 8;

    if (board << 8)
        attacks |= board << 8;

    if ((board >> 1) & NOT_H_FILE)
        attacks |= board >> 1;

    if ((board << 1) & NOT_A_FILE)
        attacks |= board << 1;

    if ((board >> 7) & NOT_A_FILE)
        attacks |= board >> 7;

    if ((board << 7) & NOT_H_FILE)
        attacks |= board << 7;

    if ((board >> 9) & NOT_H_FILE)
        attacks |= board >> 9;

    if ((board << 9) & NOT_A_FILE)
        attacks |= board << 9;

    return attacks;
}

void generate_king_moves(int color, MoveList &move_list, State &state)
{
    BitBoard board, attacks;
    int source, target;

    if (color == WHITE)
    {
        board = state.position.pieces[wKING];

        while (board)
        {
            source = board.get_ls1b_index();
            attacks = KING_ATTACKS[source] & !state.position.sides[WHITE];

            while (attacks)
            {
                target = attacks.get_ls1b_index();

                if (!state.position.sides[BLACK].get_bit(target))
                    // No capture flag if target square is empty
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

        while (board)
        {
            source = board.get_ls1b_index();
            attacks = KING_ATTACKS[source] & !state.position.sides[BLACK];

            while (attacks)
            {
                target = attacks.get_ls1b_index();

                if (!state.position.sides[WHITE].get_bit(target))
                    // No capture flag if target square is empty
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

void init_normal_attacks()
{
    for (int square = 0; square < BOARD_SIZE; square++)
    {
        PAWN_ATTACKS[WHITE][square] = pawn_attacks_mask(square, WHITE);
        PAWN_ATTACKS[BLACK][square] = pawn_attacks_mask(square, BLACK);
        KNIGHT_ATTACKS[square] = knight_attacks_mask(square);
        KING_ATTACKS[square] = king_attacks_mask(square);
    }
}

BitBoard bishop_attacks_mask(int square, BitBoard blockers, int edges)
{
    BitBoard attacks = EMPTY_BOARD;
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

void generate_bishop_moves(int color, MoveList &move_list, State &state)
{
    BitBoard board, attacks;
    int source, target;

    if (color == WHITE)
    {
        board = state.position.pieces[wBISHOP];
        while (board)
        {
            source = board.get_ls1b_index();
            attacks = get_bishop_attacks(source, state.position.sides[BOTH]) & !state.position.sides[WHITE];

            while (attacks)
            {
                target = attacks.get_ls1b_index();

                if (!state.position.sides[BLACK].get_bit(target))
                    // No capture flag if target square is empty
                    move_list.add_move(Move(source, target, wBISHOP, 0, 0, 0, 0, 0));
                else
                    move_list.add_move(Move(source, target, wBISHOP, 0, 1, 0, 0, 0));
                attacks.unset_bit(target);
            }
            board.unset_bit(source);
        }
    }
    else
    {
        board = state.position.pieces[bBISHOP];

        while (board)
        {
            source = board.get_ls1b_index();
            attacks = get_bishop_attacks(source, state.position.sides[BOTH]) & !state.position.sides[BLACK];

            while (attacks)
            {
                target = attacks.get_ls1b_index();

                if (!state.position.sides[WHITE].get_bit(target))
                    // No capture flag if target square is empty
                    move_list.add_move(Move(source, target, bBISHOP, 0, 0, 0, 0, 0));
                else
                    move_list.add_move(Move(source, target, bBISHOP, 0, 1, 0, 0, 0));
                attacks.unset_bit(target);
            }
            board.unset_bit(source);
        }
    }
}

BitBoard rook_attacks_mask(int square, BitBoard blockers, int edges)
{
    BitBoard attacks = EMPTY_BOARD;
    BitBoard mask;
    int row, file;
    int max, min;

    if (edges == 0)
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

void generate_rook_moves(int color, MoveList &move_list, State &state)
{
    BitBoard board, attacks;
    int source, target;

    if (color == WHITE)
    {
        board = state.position.pieces[wROOK];

        while (board)
        {
            source = board.get_ls1b_index();
            attacks = get_rook_attacks(source, state.position.sides[BOTH]) & !state.position.sides[WHITE];

            while (attacks)
            {
                target = attacks.get_ls1b_index();

                if (!state.position.sides[BLACK].get_bit(target))
                    // No capture flag if target square is empty
                    move_list.add_move(Move(source, target, wROOK, 0, 0, 0, 0, 0));
                else
                    move_list.add_move(Move(source, target, wROOK, 0, 1, 0, 0, 0));
                attacks.unset_bit(target);
            }
            board.unset_bit(source);
        }
    }
    else
    {
        board = state.position.pieces[bROOK];

        while (board)
        {
            source = board.get_ls1b_index();
            attacks = get_rook_attacks(source, state.position.sides[BOTH]) & !state.position.sides[BLACK];

            while (attacks)
            {
                target = attacks.get_ls1b_index();

                if (!state.position.sides[WHITE].get_bit(target))
                    // No capture flag if target square is empty
                    move_list.add_move(Move(source, target, bROOK, 0, 0, 0, 0, 0));
                else
                    move_list.add_move(Move(source, target, bROOK, 0, 1, 0, 0, 0));
                attacks.unset_bit(target);
            }
            board.unset_bit(source);
        }
    }
}

void generate_queen_moves(int color, MoveList &move_list, State &state)
{
    BitBoard board, attacks;
    int source, target;

    if (color == WHITE)
    {
        board = state.position.pieces[wQUEEN];

        while (board)
        {
            source = board.get_ls1b_index();
            attacks = get_queen_attacks(source, state.position.sides[BOTH]) & !state.position.sides[WHITE];

            while (attacks)
            {
                target = attacks.get_ls1b_index();

                if (!state.position.sides[BLACK].get_bit(target))
                    // No capture flag if target square is empty
                    move_list.add_move(Move(source, target, wQUEEN, 0, 0, 0, 0, 0));
                else
                    move_list.add_move(Move(source, target, wQUEEN, 0, 1, 0, 0, 0));
                attacks.unset_bit(target);
            }
            board.unset_bit(source);
        }
    }
    else
    {
        board = state.position.pieces[bQUEEN];

        while (board)
        {
            source = board.get_ls1b_index();
            attacks = get_queen_attacks(source, state.position.sides[BOTH]) & !state.position.sides[BLACK];

            while (attacks)
            {
                target = attacks.get_ls1b_index();

                if (!state.position.sides[WHITE].get_bit(target))
                    // No capture flag if target square is empty
                    move_list.add_move(Move(source, target, bQUEEN, 0, 0, 0, 0, 0));
                else
                    move_list.add_move(Move(source, target, bQUEEN, 0, 1, 0, 0, 0));
                attacks.unset_bit(target);
            }
            board.unset_bit(source);
        }
    }
}