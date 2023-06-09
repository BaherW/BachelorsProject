#pragma once

#include "globals.h"
#include "movelist.h"
#include "position.h"
#include "castling.h"
#include "zobrist.h"

class State
{
public:
    Position position = Position();
    uint8_t current_color = 0;
    Castling castling = Castling();
    uint8_t enpassant = 0;
    uint16_t halfmove = 0;
    U64 zobrist_hash;

    State();
    State(string fen);
    bool play_move(const Move move, const int &capture_only = 0);
    bool in_check();
    U64 compute_hash();
    void print();
};