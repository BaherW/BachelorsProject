#pragma once

#include "globals.h"
#include "move.h"

#define hash_size 0x2560000
#define NO_HASH 10000

#define hashfEXACT 0
#define hashfALPHA 1
#define hashfBETA 2

struct HashEntry
{
    U64 hash;
    int depth;
    int flag;
    int val;
    Move best_move;
};

class TranspositionTable
{
public:
    void clear();
    U64 read(U64 hash, int alpha, int beta, int depth, Move &best_move);
    void write(U64 hash, int depth, int flag, int val, Move &best_move);

private:
    HashEntry table[hash_size];
};

extern TranspositionTable tt;