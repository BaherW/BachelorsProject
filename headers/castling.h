#pragma once

#include "globals.h"

extern uint8_t CASTLING_RIGHTS[BOARD_SIZE];

class Castling
{
public:
    uint8_t castle_rights;

    Castling();
    Castling(uint8_t rights);
    Castling(string fen);

    void update_castle_right(const int &source, const int &target);

    bool wk_can_castle();
    bool wq_can_castle();
    bool bk_can_castle();
    bool bq_can_castle();

    void print();
};
