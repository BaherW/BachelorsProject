#include "../headers/move.h"

Move::Move()
{
    move = 0;
}

Move::Move(const uint8_t &source, const uint8_t &target, const uint8_t &piece, const uint8_t &promoted, const bool &capture, const bool &double_push, const bool &enpassant, const bool &castling)
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

uint8_t Move::get_source() const
{
    return move & 0x3F;
}

uint8_t Move::get_target() const
{
    return (move & 0xFC0) >> 6;
}

uint8_t Move::get_piece() const
{
    return (move & 0xF000) >> 12;
}

uint8_t Move::get_promoted_piece() const
{
    return (move & 0xF0000) >> 16;
}

bool Move::is_capture() const
{
    return move & 0x100000;
}

bool Move::is_double_push() const
{
    return move & 0x200000;
}

bool Move::is_enpassant() const
{
    return move & 0x400000;
}

bool Move::is_castle() const
{
    return move & 0x800000;
}

int Move::get_value() const
{
    return move;
}

void Move::print()
{
    cout << "Source"
         << "      "
         << "Target"
         << "      "
         << "Piece"
         << "      "
         << "Promoted"
         << "      "
         << "Capture"
         << "      "
         << "Double"
         << "      "
         << "Enpassant"
         << "      "
         << "Castling" << endl;
    cout << SQUARE_TO_STRING[get_source()]
         << "          " << SQUARE_TO_STRING[get_target()]
         << "          " << PIECE_UNICODE[get_piece()]
         << "          " << get_promoted_piece()
         << "             " << is_capture()
         << "            " << is_double_push()
         << "           " << is_enpassant()
         << "              " << is_castle() << endl;
}
