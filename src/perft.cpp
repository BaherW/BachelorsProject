#include <chrono>
#include "globals.h"
#include "movegen.cpp"
#include "movelist.cpp"
#include "state.cpp"

U64 perft(int depth, State &state)
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
        if (state.play_move(move_list.moves[i]))
            nodes += perft(depth - 1, state);
        state = oldState;
    }
    return nodes;
}

void time_perft(int depth, State &state)
{
    auto start = chrono::steady_clock::now();
    U64 result = perft(depth, state);
    auto end = chrono::steady_clock::now();

    chrono::duration<double> elapsed_seconds = end - start;
    cout << "Perft Result: " << result << endl;
    cout << "Elapsed Time: " << elapsed_seconds.count() << " seconds" << endl;
}