#pragma once
#include "globals.h"
#include <iomanip>

class Move
{
private:
    U64 move;

public:
    Move()
    {
        move = 0;
    }

    Move(uint8_t source, uint8_t target, uint8_t piece, uint8_t promoted, bool capture, bool double_push, bool enpassant, bool castling)
    {
        move = ((source) |
                (target << 6) |
                (piece << 12) |
                (promoted << 16) |
                (capture << 20) |
                (double_push << 21) |
                (enpassant << 22) |
                (castling << 23));
    }

    uint64_t get_source() const
    {
        return (move & 0x3F);
    }

    uint64_t get_target() const
    {
        return (move & 0xfc0) >> 6;
    }

    uint64_t get_piece() const
    {
        return (move & 0xf000) >> 12;
    }

    uint64_t get_promoted_piece() const
    {
        return (move & 0xf0000) >> 16;
    }

    bool is_capture() const
    {
        return move & 0x100000;
    }

    bool is_double_push() const
    {
        return move & 0x200000;
    }

    bool is_enpassant() const
    {
        return move & 0x400000;
    }

    bool is_castling() const
    {
        return move & 0x800000;
    }

    void print()
    {
        cout << "Source"
             << "      " << "Target"
             << "      " << "Piece"
             << "      " << "Promoted"
             << "      " << "Capture"
             << "      " << "Double"
             << "      " << "Enpassant"
             << "      " << "Castling" << endl;
        cout << SQUARE_TO_STRING[get_source()]
             << "          " << SQUARE_TO_STRING[get_target()]
             << "          " << PIECE_UNICODE[get_piece()]
             << "          " << get_promoted_piece()
             << "             " << is_capture()
             << "            " << is_double_push()
             << "           " << is_enpassant()
             << "              " << is_castling() << endl;
    }
};