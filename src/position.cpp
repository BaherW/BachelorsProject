#include "../headers/position.h"
#include "../headers/attacks.h"
#include "../headers/magic_attacks.h"

Position::Position()
{
    set_position("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
}

Position::Position(string fen)
{
    set_position(fen);
}

void Position::combine_boards()
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

    sides[0] = white;
    sides[1] = black;
    sides[2] = white | black;
}

bool Position::is_square_attacked(int square, int color)
{
    return color ? is_black_attacking(square) : is_white_attacking(square);
}

void Position::print()
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
    printf("\n   a b c d e f g h\n\n");
}

void Position::print_attacked_squares(int color)
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

void Position::init_boards()
{
    for (int piece = 0; piece < 12; piece++)
    {
        BitBoard emptyBoard;
        pieces[piece] = emptyBoard;
    }
}

void Position::read_fen(string fen)
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

void Position::set_position(string fen)
{
    init_boards();
    read_fen(fen);
    combine_boards();
}

bool Position::is_white_attacking(int square)
{
    if (PAWN_ATTACKS[BLACK][square] & pieces[wPAWN])
        return true;
    if (KNIGHT_ATTACKS[square] & pieces[wKNIGHT])
        return true;
    if (get_bishop_attacks(square, sides[BOTH]) & pieces[wBISHOP])
        return true;
    if (get_rook_attacks(square, sides[BOTH]) & pieces[wROOK])
        return true;
    if (get_queen_attacks(square, sides[BOTH]) & pieces[wQUEEN])
        return true;

    return KING_ATTACKS[square] & pieces[wKING];
}

bool Position::is_black_attacking(int square)
{
    if (PAWN_ATTACKS[WHITE][square] & pieces[bPAWN])
        return true;
    if (KNIGHT_ATTACKS[square] & pieces[bKNIGHT])
        return true;
    if (get_bishop_attacks(square, sides[BOTH]) & pieces[bBISHOP])
        return true;
    if (get_rook_attacks(square, sides[BOTH]) & pieces[bROOK])
        return true;
    if (get_queen_attacks(square, sides[BOTH]) & pieces[bQUEEN])
        return true;

    return KING_ATTACKS[square] & pieces[bKING];
}
