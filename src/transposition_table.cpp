#include "../headers/transposition_table.h"

void TranspositionTable::clear() {
    for (int i = 0; i < hash_size; i++) {
        table[i].hash = 0;
        table[i].depth = 0;
        table[i].flag = 0;
        table[i].val = 0;
    }
}

U64 TranspositionTable::read(U64 hash, int alpha, int beta, int depth, Move& best_move) {
    HashEntry* entry = &table[hash % hash_size];

    if (entry->hash == hash && entry->depth >= depth) {
        if (entry->flag == hashfEXACT)
            return entry->val;

        if (entry->flag == hashfALPHA && entry->val <= alpha)
            return alpha;

        if (entry->flag == hashfBETA && entry->val >= beta)
            return beta;

        best_move = entry->best_move;
    }
    return NO_HASH;
}

void TranspositionTable::write(U64 hash, int depth, int flag, int val, Move& best_move) {
    HashEntry* entry = &table[hash % hash_size];

    entry->hash = hash;
    entry->depth = depth;
    entry->flag = flag;
    entry->val = val;
    entry->best_move = best_move;
}

TranspositionTable tt;
