#include "../headers/globals.h"
#include "../headers/movegen.h"
#include "../headers/movelist.h"
#include "../headers/state.h"

U64 perft(int depth, State &state);
void time_perft(int depth, State &state);