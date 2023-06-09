#include "../headers/state.h"
#include "../headers/movelist.h"
#include "../headers/position.h"
#include "../headers/castling.h"
#include "../headers/zobrist.h"

State::State() { zobrist_hash = compute_hash(); }

State::State(string fen)
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
    zobrist_hash = compute_hash();
}

bool State::play_move(const Move move, const int &capture_only)
{
    int source = move.get_source();
    int target = move.get_target();
    int piece = move.get_piece();
    int promoted = move.get_promoted_piece();

    position.pieces[piece].unset_bit(source);
    position.pieces[piece].set_bit(target);

    zobrist_hash ^= pieces_key[piece][source];
    zobrist_hash ^= pieces_key[piece][target];

    halfmove += 1;

    if (piece == wPAWN || piece == bPAWN)
        halfmove = 0;

    if (move.is_capture())
    {
        halfmove = 0;
        if (current_color == WHITE)
        {
            for (int i = bPAWN; i < bKING; i++)
            {
                if (position.pieces[i].get_bit(target))
                {
                    position.pieces[i].unset_bit(target);
                    zobrist_hash ^= pieces_key[i][target];
                    break;
                }
            }
        }
        else
        {
            for (int i = wPAWN; i < wKING; i++)
            {
                if (position.pieces[i].get_bit(target))
                {
                    position.pieces[i].unset_bit(target);
                    zobrist_hash ^= pieces_key[i][target];
                    break;
                }
            }
        }

        if (move.is_enpassant())
        {
            if (current_color == WHITE)
            {
                position.pieces[bPAWN].unset_bit(target + 8);
                zobrist_hash ^= pieces_key[bPAWN][target + 8];
            }
            else
            {
                position.pieces[wPAWN].unset_bit(target - 8);
                zobrist_hash ^= pieces_key[wPAWN][target - 8];
            }
        }

        enpassant = 0;
    }
    else
    {
        if (move.is_double_push())
        {
            if (current_color == WHITE)
            {
                enpassant = target + 8;
                zobrist_hash ^= en_passant_key[target + 8];
            }
            else
            {
                enpassant = target - 8;
                zobrist_hash ^= en_passant_key[target - 8];
            }
        }
        else
            enpassant = 0;

        if (move.is_castle())
        {
            switch (target)
            {
            case g1:
                position.pieces[wROOK].unset_bit(h1);
                position.pieces[wROOK].set_bit(f1);

                zobrist_hash ^= pieces_key[wROOK][h1];
                zobrist_hash ^= pieces_key[wROOK][f1];
                break;
            case c1:
                position.pieces[wROOK].unset_bit(a1);
                position.pieces[wROOK].set_bit(d1);

                zobrist_hash ^= pieces_key[wROOK][a1];
                zobrist_hash ^= pieces_key[wROOK][d1];
                break;
            case g8:
                position.pieces[bROOK].unset_bit(h8);
                position.pieces[bROOK].set_bit(f8);

                zobrist_hash ^= pieces_key[bROOK][h8];
                zobrist_hash ^= pieces_key[bROOK][f8];
                break;
            case c8:
                position.pieces[bROOK].unset_bit(a8);
                position.pieces[bROOK].set_bit(d8);

                zobrist_hash ^= pieces_key[bROOK][a8];
                zobrist_hash ^= pieces_key[bROOK][d8];
                break;
            }
        }
    }

    if (promoted != 0)
    {
        if (current_color == WHITE)
        {
            position.pieces[wPAWN].unset_bit(target);
            zobrist_hash ^= pieces_key[wPAWN][target];
        }
        else
        {
            position.pieces[bPAWN].unset_bit(target);
            zobrist_hash ^= pieces_key[bPAWN][target];
        }
        position.pieces[promoted].set_bit(target);
        zobrist_hash ^= pieces_key[promoted][target];
    }

    zobrist_hash ^= castling_key[castling.castle_rights];
    castling.update_castle_right(source, target);
    zobrist_hash ^= castling_key[castling.castle_rights];

    position.combine_boards();

    current_color = !current_color;
    zobrist_hash ^= current_color_key;

    int king_location = position.pieces[current_color ? wKING : bKING].get_ls1b_index();
    if (position.is_square_attacked(king_location, current_color))
        return false;

    return true;
}

bool State::in_check()
{
    return position.is_square_attacked((current_color == WHITE ? position.pieces[wKING] : position.pieces[bKING]).get_ls1b_index(), !current_color);
}

U64 State::compute_hash()
{
    U64 hash = 0;
    for (int p = wPAWN; p <= bKING; p++)
    {
        BitBoard board = position.pieces[p];

        while (board)
        {
            int square = board.get_ls1b_index();
            hash ^= pieces_key[p][square];
            board.unset_bit(square);
        }
    }

    hash ^= castling_key[castling.castle_rights];

    if (enpassant != 0)
        hash ^= en_passant_key[enpassant];

    if (current_color == BLACK)
        hash ^= current_color_key;

    return hash;
}

void State::print()
{
    position.print();
    cout << "Color: " << (current_color ? "Black " : "White ");
    castling.print();
    cout << " Enpassant: " << (enpassant == 0 ? "-" : SQUARE_TO_STRING[enpassant]);
    cout << " HalfMove: " << halfmove << endl;
    cout << "BitBoard: " << position.sides[BOTH].get_board() << endl;
}