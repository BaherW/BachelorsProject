#include "globals.h"
#include "movegen.cpp"
#include "movelist.cpp"
#include "state.cpp"

U64 perft(int depth, State state)
{
    MoveList move_list;
    int n_moves, i;

    if (depth == 0)
        return 1;

    U64 nodes = 0;
    generate_moves(move_list, state);
    n_moves = move_list.num_moves;

    for (i = 0; i < n_moves; i++)
    {
        State oldState = state;
        if (!state.play_move(move_list.moves[i]))
            nodes += perft(depth - 1, state);
        state = oldState;
    }
    return nodes;
}

struct PerftResult
{
    U64 nodes;
    U64 captures;
    U64 enp;
    U64 castles;
};

PerftResult perft2(int depth, State state)
{
    MoveList move_list;
    int n_moves, i;

    if (depth == 0)
    {
        PerftResult result;
        result.nodes = 1;
        result.captures = 0;
        result.enp = 0;
        result.castles = 0;
        return result;
    }

    PerftResult result;
    result.nodes = 0;
    result.captures = 0;
    result.enp = 0;
    result.castles = 0;

    generate_moves(move_list, state);
    n_moves = move_list.num_moves;

    for (i = 0; i < n_moves; i++)
    {
        State oldState = state;
        if (!state.play_move(move_list.moves[i]))
        {
            PerftResult childResult = perft2(depth - 1, state);
            result.nodes += childResult.nodes;
            result.captures += childResult.captures + move_list.moves[i].is_capture();
            result.enp = childResult.enp + move_list.moves[i].is_enpassant();
            result.castles = childResult.castles + move_list.moves[i].is_castling();
        }
        state = oldState;
    }

    return result;
}