#include "globals.h"

class BitBoard
{
private:
    U64 board;

public:
    BitBoard()
    {
        board = 0ULL;
    }

    BitBoard(U64 board)
    {
        board = board;
    }

    void set_bit(int n)
    {
        board |= 1ULL << n;
    }

    void unset_bit(int n)
    {
        board &= ~(1ULL << n);
    }

    int get_bit(int n)
    {
        return board & (1ULL << n) ? 1 : 0;
    }

    BitBoard operator&(const BitBoard &rhs)
    {
        return BitBoard(board & rhs.board);
    }

    BitBoard operator|(const BitBoard &rhs)
    {
        return BitBoard(board | rhs.board);
    }

    BitBoard operator!()
    {
        return BitBoard(~board);
    }

    bool operator==(const BitBoard &rhs)
    {
        return board == rhs.board;
    }

    bool operator!=(const BitBoard &rhs)
    {
        return board != rhs.board;
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

                cout << " " << get_bit(square);
            }
            cout << endl;
        }
        cout << endl
             << "   a b c d e f g h" << endl;
    }
};