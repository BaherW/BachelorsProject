#pragma once
#include "globals.h"
#include "position.cpp"
#include "castling.cpp"

class State
{
public:
    Position position = Position();
    int current_color = 0;
    Castling castling = Castling();
    int enpassant = -1;
    int halfmove = 0;
    int fullmove = 1;
    
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
        enpassant = split_fen[3] == "-" ? -1 : string_to_square(split_fen[3]);
        halfmove = stoi(split_fen[4]);
        fullmove = stoi(split_fen[5]);
    }

    void print()
    {
        position.print();
        cout << "Color: " << (current_color ? "Black " : "White ");
        castling.print();
        cout << " Enpassant: " << (enpassant == -1 ? "-" : SQUARE_TO_STRING[enpassant]);
        cout << " HalfMove: " << halfmove << " FullMove " << fullmove << endl;
    }
};