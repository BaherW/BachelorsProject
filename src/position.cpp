#include "globals.h"

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
                        switch (piece)
                        {
                        case wPAWN:
                            cout << " ♟︎";
                            break;
                        case wKNIGHT:
                            cout << " ♞";
                            break;
                        case wBISHOP:
                            cout << " ♝";
                            break;
                        case wROOK:
                            cout << " ♜";
                            break;
                        case wQUEEN:
                            cout << " ♛";
                            break;
                        case wKING:
                            cout << " ♚";
                            break;
                        case bPAWN:
                            cout << " ♙";
                            break;
                        case bKNIGHT:
                            cout << " ♘";
                            break;
                        case bBISHOP:
                            cout << " ♗";
                            break;
                        case bROOK:
                            cout << " ♖";
                            break;
                        case bQUEEN:
                            cout << " ♕";
                            break;
                        case bKING:
                            cout << " ♔";
                            break;
                        default:
                            cout << " .";
                            break;
                        }
                    }
                }
                if (!found)
                {
                    cout << " .";
                }
            }
            cout << endl;
        }
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
};