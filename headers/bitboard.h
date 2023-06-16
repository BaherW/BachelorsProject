#pragma once

#include "globals.h"

class BitBoard
{
private:
    U64 board;

public:
    BitBoard();
    BitBoard(U64 b);

    void set_bit(const int &n);
    void unset_bit(const int &n);
    int get_bit(const int &n);
    int pop_count();
    int get_ls1b_index();

    BitBoard operator&(const BitBoard &rhs);
    BitBoard operator&=(const BitBoard &rhs);
    BitBoard operator|(const BitBoard &rhs);
    BitBoard operator|=(const BitBoard &rhs);
    BitBoard operator!();
    BitBoard operator>>(const int &n);
    BitBoard &operator>>=(const int &n);
    BitBoard operator<<(const int &n);
    BitBoard operator*(BitBoard &rhs);
    BitBoard &operator*=(const BitBoard &rhs);
    bool operator==(const BitBoard &rhs);
    bool operator!=(const BitBoard &rhs);
    explicit operator bool() const;
    operator size_t() const;
    U64 get_board();
    void printLatexBitboardString();
    void print();
};
