#pragma once
#include "globals.h"
#include "attacks/magic_attacks.cpp"
#include "attacks/pawn.cpp"
#include "attacks/knight.cpp"
#include "attacks/king.cpp"

class Position
{
public:
    BitBoard pieces[12];
    BitBoard sides[3];

    Position()
    {
        setPosition("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
    }

    Position(string fen)
    {
        setPosition(fen);
    }

    bool is_square_attacked(int square, int color)
    {
        return color ? is_black_attacked(square) : is_white_attacked(square);
    }

    void print()
    {
        for (int rank = 0; rank < 8; rank++)
        {
            for (int file = 0; file < 8; file++)
            {
                int square = rank * 8 + file;

                if (file == 0)
                    cout << abs(rank - 8) << " ";

                bool found = false;
                for (int piece = 0; piece < 12; piece++)
                {
                    if (pieces[piece].get_bit(square))
                    {
                        found = true;
                        if (piece <= 11)
                            cout << " " << PIECE_UNICODE[piece];
                        else
                            cout << " .";
                    }
                }
                if (!found)
                    cout << " .";
            }
            cout << endl;
        }
    }

    void print_attacked_squares(int color)
    {
        cout << endl;
        for (int rank = 0; rank < 8; rank++)
        {
            for (int file = 0; file < 8; file++)
            {
                int square = rank * 8 + file;

                if (!file)
                    printf("  %d ", 8 - rank);

                printf(" %d", is_square_attacked(square, color) ? 1 : 0);
            }

            cout << endl;
        }

        // print files
        printf("\n     a b c d e f g h\n\n");
    }

private:
    void initBoards()
    {
        for (int piece = 0; piece < 12; piece++)
        {
            BitBoard emptyBoard;
            pieces[piece] = emptyBoard;
        }
    }
    void readFen(string fen)
    {
        int square = 0;
        for (int i = 0; i < fen.length(); i++)
        {
            int skippedSquares = 1;
            switch (fen.at(i))
            {
            case 'p':
                pieces[bPAWN].set_bit(square);
                break;
            case 'n':
                pieces[bKNIGHT].set_bit(square);
                break;
            case 'b':
                pieces[bBISHOP].set_bit(square);
                break;
            case 'r':
                pieces[bROOK].set_bit(square);
                break;
            case 'q':
                pieces[bQUEEN].set_bit(square);
                break;
            case 'k':
                pieces[bKING].set_bit(square);
                break;
            case 'P':
                pieces[wPAWN].set_bit(square);
                break;
            case 'N':
                pieces[wKNIGHT].set_bit(square);
                break;
            case 'B':
                pieces[wBISHOP].set_bit(square);
                break;
            case 'R':
                pieces[wROOK].set_bit(square);
                break;
            case 'Q':
                pieces[wQUEEN].set_bit(square);
                break;
            case 'K':
                pieces[wKING].set_bit(square);
                break;
            case '/':
                square--;
                break;
            default:
                int skip = fen.at(i) - '0';
                skippedSquares += skip - 1;
                break;
            }
            square += skippedSquares;
        }
    }
    void combineBoards()
    {
        BitBoard white = pieces[wPAWN] |
                         pieces[wKNIGHT] |
                         pieces[wBISHOP] |
                         pieces[wROOK] |
                         pieces[wQUEEN] |
                         pieces[wKING];
        BitBoard black = pieces[bPAWN] |
                         pieces[bKNIGHT] |
                         pieces[bBISHOP] |
                         pieces[bROOK] |
                         pieces[bQUEEN] |
                         pieces[bKING];
        BitBoard both = white | black;

        sides[0] = white;
        sides[1] = black;
        sides[2] = both;
    }

    void setPosition(string fen)
    {
        initBoards();
        readFen(fen);
        combineBoards();
    }

    bool is_white_attacked(int square)
    {
        if ((PAWN_ATTACKS[BLACK][square] & pieces[wPAWN]) != empty_board)
            return true;
        if ((KNIGHT_ATTACKS[square] & pieces[wKNIGHT]) != empty_board)
            return true;
        if ((get_bishop_attacks(square, sides[BOTH]) & pieces[wBISHOP]) != empty_board)
            return true;
        if ((get_rook_attacks(square, sides[BOTH]) & pieces[wROOK]) != empty_board)
            return true;
        if ((get_queen_attacks(square, sides[BOTH]) & pieces[wQUEEN]) != empty_board)
            return true;
        if ((KING_ATTACKS[square] & pieces[wKING]) != empty_board)
            return true;

        return false;
    }

    bool is_black_attacked(int square)
    {
        if ((PAWN_ATTACKS[WHITE][square] & pieces[bPAWN]) != empty_board)
            return true;
        if ((KNIGHT_ATTACKS[square] & pieces[bKNIGHT]) != empty_board)
            return true;
        if ((get_bishop_attacks(square, sides[BOTH]) & pieces[bBISHOP]) != empty_board)
            return true;
        if ((get_rook_attacks(square, sides[BOTH]) & pieces[bROOK]) != empty_board)
            return true;
        if ((get_queen_attacks(square, sides[BOTH]) & pieces[bQUEEN]) != empty_board)
            return true;
        if ((KING_ATTACKS[square] & pieces[bKING]) != empty_board)
            return true;

        return false;
    }
};