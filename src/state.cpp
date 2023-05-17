#pragma once
#include "globals.h"
#include "movelist.cpp"
#include "position.cpp"
#include "castling.cpp"

class State
{
public:
    Position position = Position();
    uint8_t current_color = 0;
    Castling castling = Castling();
    uint8_t enpassant = 0;
    uint16_t halfmove = 0;
    uint16_t fullmove = 1;

    State() {}

    State(string fen)
    {
        istringstream iss(fen);
        string fen_piece;
        vector<string> split_fen;
        while (getline(iss, fen_piece, ' '))
            split_fen.push_back(fen_piece);

        position = Position(split_fen[0]);
        current_color = split_fen[1] == "w" ? WHITE : BLACK;
        castling = Castling(split_fen[2]);
        enpassant = split_fen[3] == "-" ? 0 : SQUARE_TO_INDEX(split_fen[3]);
        halfmove = stoi(split_fen[4]);
        fullmove = stoi(split_fen[5]);
    }

    bool play_move(Move move)
    {
        int source = move.get_source();
        int target = move.get_target();
        int piece = move.get_piece();
        int promoted = move.get_promoted_piece();

        position.pieces[piece].unset_bit(source);
        position.pieces[piece].set_bit(target);

        if (move.is_double_push())
        {
            if (current_color == WHITE)
                enpassant = target + 8;
            else
                enpassant = target - 8;
        }
        else
            enpassant = 0;

        if (move.is_enpassant())
        {
            if (current_color == WHITE)
                position.pieces[bPAWN].unset_bit(target + 8);
            else
                position.pieces[wPAWN].unset_bit(target - 8);
        }

        if (promoted != 0)
        {
            if (current_color == WHITE)
                position.pieces[wPAWN].unset_bit(target);
            else
                position.pieces[bPAWN].unset_bit(target);
            position.pieces[promoted].set_bit(target);
        }

        if (move.is_castling())
        {
            switch (target)
            {
            case g1:
                position.pieces[wROOK].unset_bit(h1);
                position.pieces[wROOK].set_bit(f1);
                break;
            case c1:
                position.pieces[wROOK].unset_bit(a1);
                position.pieces[wROOK].set_bit(d1);
                break;
            case g8:
                position.pieces[bROOK].unset_bit(h8);
                position.pieces[bROOK].set_bit(f8);
                break;
            case c8:
                position.pieces[bROOK].unset_bit(a8);
                position.pieces[bROOK].set_bit(d8);
                break;
            }
        }

        castling.update_castle_right(source, target);

        position.combine_boards();

        current_color = !current_color;

        int king_location = position.pieces[current_color ? bKING : wKING].get_ls1b_index();
        if (position.is_square_attacked(king_location, current_color))
            return false;

        return true;
    }

    void print()
    {
        position.print();
        cout << "Color: " << (current_color ? "Black " : "White ");
        castling.print();
        cout << " Enpassant: " << (enpassant == 0 ? "-" : SQUARE_TO_STRING[enpassant]);
        cout << " HalfMove: " << halfmove << " FullMove " << fullmove << endl;
    }
};