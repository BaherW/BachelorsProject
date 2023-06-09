#include "../headers/search.h"
#include "../headers/movelist.h"
#include "../headers/movegen.h"
#include "../headers/eval.h"
#include "../headers/transposition_table.h"
#include "../headers/zobrist.h"

void Searcher::search(int depth, State state)
{
    int val;

    for (int i = 1; i <= depth; i++)
        val = alpha_beta(i, state, -INFINITY, INFINITY);
}

int Searcher::alpha_beta(int depth, State &state, int alpha, int beta)
{
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
        State old_state = state;
        ply++;

        if (state.enpassant != 0)
            state.zobrist_hash ^= en_passant_key[state.enpassant];
        state.enpassant = 0;

        state.current_color = !state.current_color;
        state.zobrist_hash ^= current_color_key;

        val = -alpha_beta(depth - 3, state, -beta, -beta + 1);

        ply--;
        state = old_state;

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

        if (val >= beta)
        {
            tt.write(state.zobrist_hash, depth, hashfBETA, beta, best_move);
            return beta;
        }

        if (val > alpha)
        {
            hash_flag = hashfEXACT;
            alpha = val;
            if (ply == 0)
            {
                current_best_move = move_list.moves[i];
                foundPV = true;
            }
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
    nodes_searched++;

    int val = eval(state);

    if (val >= beta)
        return beta;

    if (val > alpha)
        alpha = val;

    MoveList move_list = MoveList(true);
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

        if (val >= beta)
            return beta;

        if (val > alpha)
            alpha = val;
    }
    return alpha;
}