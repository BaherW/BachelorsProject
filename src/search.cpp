#include "../headers/search.h"
#include "../headers/movelist.h"
#include "../headers/movegen.h"
#include "../headers/eval.h"
#include "../headers/transposition_table.h"
#include "../headers/zobrist.h"
#include "sysinfoapi.h"

void Searcher::search(int depth, State state)
{
    int val;
    Move temp_best_move;

    stop_time = GetTickCount() + 15000; // 15 second max search for max depth

    // Itterative Deepening
    for (int i = 1; i <= depth; i++)
    {
        depth_searched = i;
        if (timeout_flag)
            break;

        temp_best_move = best_move;
        val = alpha_beta(i, state, -INFINITY, INFINITY);
    }
    best_move = temp_best_move;
}

int Searcher::alpha_beta(int depth, State &state, int alpha, int beta)
{
    if ((nodes_searched & 10000) == 0)
        check_timeout();

    int val;
    int hash_flag = hashfALPHA;

    if ((val = tt.read(state.zobrist_hash, alpha, beta, depth, best_move)) != NO_HASH)
        return val;

    if (depth <= 0)
        return quiescent(state, alpha, beta);

    nodes_searched++;

    int check = state.in_check();

    if (check)
        depth++;

    int legal_moves = 0;

    // Null move pruning
    if (depth >= 3 && !check && ply)
    {
        int reduction = 2;
        State old_state = state;
        ply++;

        if (state.enpassant != 0)
            state.zobrist_hash ^= en_passant_key[state.enpassant];
        state.enpassant = 0;

        state.current_color = !state.current_color;
        state.zobrist_hash ^= current_color_key;

        val = -alpha_beta(depth - 1 - reduction, state, -beta, -beta + 1);

        ply--;
        state = old_state;

        if (timeout_flag)
            return 0;

        if (val >= beta)
            return beta;
    }

    int old_alpha = alpha;
    Move current_best_move;
    bool foundPV = false;
    MoveList move_list;
    generate_moves(move_list, state);
    move_list.sort_moves(state);
    for (int i = 0; i < move_list.num_moves; i++)
    {
        State old_state = state;
        ply++;
        if (!state.play_move(move_list.moves[i]))
        {
            ply--;
            state = old_state;
            continue;
        }

        legal_moves++;

        // PV Search
        if (foundPV)
        {
            val = -alpha_beta(depth - 1, state, -alpha - 1, -alpha);
            if (val > alpha && val < beta)
                val = -alpha_beta(depth - 1, state, -beta, -alpha);
        }
        else
            val = -alpha_beta(depth - 1, state, -beta, -alpha);

        ply--;
        state = old_state;

        if (timeout_flag)
            return 0;

        if (val >= beta)
        {
            tt.write(state.zobrist_hash, depth, hashfBETA, beta, best_move);
            return beta;
        }

        if (val > alpha)
        {
            hash_flag = hashfEXACT;
            alpha = val;
            current_best_move = move_list.moves[i];
            if (ply == 0)
                foundPV = true;
        }
    }

    // Mate & Stalemate scoring
    if (!legal_moves)
    {
        if (check)
            return -49000 + ply;
        return 0;
    }

    if (old_alpha != alpha)
        best_move = current_best_move;

    tt.write(state.zobrist_hash, depth, hash_flag, alpha, best_move);

    return alpha;
}

int Searcher::quiescent(State &state, int alpha, int beta)
{
    if ((nodes_searched & 10000) == 0)
        check_timeout();

    nodes_searched++;

    int val = eval(state);

    if (val >= beta)
        return beta;

    if (val > alpha)
        alpha = val;

    MoveList move_list = MoveList(true); // Only appends captures (captures_only flag set)
    generate_moves(move_list, state);
    move_list.sort_moves(state);
    for (int i = 0; i < move_list.num_moves; i++)
    {
        State old_state = state;
        ply++;
        if (!state.play_move(move_list.moves[i]))
        {
            ply--;
            state = old_state;
            continue;
        }

        val = -quiescent(state, -beta, -alpha);

        ply--;
        state = old_state;

        if (timeout_flag)
            return 0;

        if (val >= beta)
            return beta;

        if (val > alpha)
            alpha = val;
    }
    return alpha;
}

void Searcher::check_timeout()
{
    if (GetTickCount() > stop_time)
        timeout_flag = 1;
}