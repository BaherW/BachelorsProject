#pragma once

#include "globals.h"

class Move
{
private:
    uint32_t move;

public:
    Move();
    Move(const uint8_t &source, const uint8_t &target, const uint8_t &piece, const uint8_t &promoted, const bool &capture, const bool &double_push, const bool &enpassant, const bool &castling);
    uint8_t get_source() const;
    uint8_t get_target() const;
    uint8_t get_piece() const;
    uint8_t get_promoted_piece() const;
    bool is_capture() const;
    bool is_double_push() const;
    bool is_enpassant() const;
    bool is_castle() const;
    int get_value() const;
    void print();
};
