#include <chrono>
#include "../headers/globals.h"
#include "../headers/movegen.h"
#include "../headers/movelist.h"
#include "../headers/state.h"

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
        State old_state = state;
        if (state.play_move(move_list.moves[i]))
            nodes += perft(depth - 1, state);
        state = old_state;
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