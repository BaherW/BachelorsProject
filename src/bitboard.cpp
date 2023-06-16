#include "../headers/globals.h"

BitBoard::BitBoard()
{
    board = 0ULL;
}

BitBoard::BitBoard(U64 b)
{
    board = b;
}

void BitBoard::set_bit(const int &n)
{
    board |= 1ULL << n;
}

void BitBoard::unset_bit(const int &n)
{
    board &= ~(1ULL << n);
}

int BitBoard::get_bit(const int &n)
{
    return board & (1ULL << n) ? 1 : 0;
}

int BitBoard::pop_count()
{
    return __builtin_popcountll(board);
}

int BitBoard::get_ls1b_index()
{
    return __builtin_ctzll(board);
}

BitBoard BitBoard::operator&(const BitBoard &rhs)
{
    return BitBoard(board & rhs.board);
}

BitBoard BitBoard::operator&=(const BitBoard &rhs)
{
    return BitBoard(board &= rhs.board);
}

BitBoard BitBoard::operator|(const BitBoard &rhs)
{
    return BitBoard(board | rhs.board);
}

BitBoard BitBoard::operator|=(const BitBoard &rhs)
{
    return BitBoard(board |= rhs.board);
}

BitBoard BitBoard::operator!()
{
    return BitBoard(~board);
}

BitBoard BitBoard::operator>>(const int &n)
{
    return BitBoard(board >> n);
}

BitBoard &BitBoard::operator>>=(const int &n)
{
    board >>= n;
    return *this;
}

BitBoard BitBoard::operator<<(const int &n)
{
    return BitBoard(board << n);
}

BitBoard BitBoard::operator*(BitBoard &rhs)
{
    return BitBoard(board * rhs);
}

BitBoard &BitBoard::operator*=(const BitBoard &rhs)
{
    board *= rhs.board;
    return *this;
}

bool BitBoard::operator==(const BitBoard &rhs)
{
    return board == rhs.board;
}

bool BitBoard::operator!=(const BitBoard &rhs)
{
    return board != rhs.board;
}

BitBoard::operator bool() const
{
    return board != 0ULL;
}

BitBoard::operator size_t() const
{
    return static_cast<size_t>(board);
}

U64 BitBoard::get_board()
{
    return board;
}

void BitBoard::printLatexBitboardString()
{
    uint64_t value = board;
    std::stringstream ss;
    ss << "\\bitboard{";
    for (int row = 0; row < 8; ++row)
    {
        ss << "{";
        for (int col = 0; col < 8; ++col)
        {
            int index = row * 8 + col;
            bool bit = (value >> index) & 1;
            ss << bit;
            if (col < 7)
            {
                ss << ",";
            }
        }
        ss << "}";
        if (row < 7)
        {
            ss << ",";
        }
    }
    ss << "}";
    cout << ss.str() << endl;
}

void BitBoard::print()
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
