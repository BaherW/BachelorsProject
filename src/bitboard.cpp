#pragma once
#include "globals.h"

// TODO: maybe make is_empty function

class BitBoard
{
private:
    U64 board;

public:
    BitBoard()
    {
        board = 0ULL;
    }

    BitBoard(U64 b)
    {
        board = b;
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

    // Brian Kerninghan's way
    int pop_count()
    {
        U64 temp_board = board;
        int count = 0;
        while (temp_board)
        {
            count++;
            temp_board &= temp_board - 1; // reset LS1B
        }
        return count;
    }

    int get_ls1b_index()
    {
        if (board)
            return BitBoard((board & -board) - 1).pop_count();
        return -1;
    }

    BitBoard operator&(const BitBoard &rhs)
    {
        return BitBoard(board & rhs.board);
    }

    BitBoard operator&=(const BitBoard &rhs)
    {
        return BitBoard(board &= rhs.board);
    }

    BitBoard operator|(const BitBoard &rhs)
    {
        return BitBoard(board | rhs.board);
    }

    BitBoard operator|=(const BitBoard &rhs)
    {
        return BitBoard(board |= rhs.board);
    }

    BitBoard operator!()
    {
        return BitBoard(~board);
    }

    BitBoard operator>>(int n) const
    {
        return BitBoard(board >> n);
    }

    BitBoard &operator>>=(int n)
    {
        board >>= n;
        return *this;
    }

    BitBoard operator<<(int n) const
    {
        return BitBoard(board << n);
    }

    BitBoard operator*(BitBoard &rhs) const
    {
        return BitBoard(board * rhs);
    }

    BitBoard &operator*=(const BitBoard &rhs)
    {
        board *= rhs.board;
        return *this;
    }

    bool operator==(const BitBoard &rhs)
    {
        return board == rhs.board;
    }

    bool operator!=(const BitBoard &rhs)
    {
        return board != rhs.board;
    }

    operator size_t() const
    {
        return static_cast<size_t>(board);
    }

    U64 get_board()
    {
        return board;
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