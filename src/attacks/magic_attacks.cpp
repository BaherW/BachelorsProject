#include "../globals.h"
#include "bishop.cpp"
#include "rook.cpp"
#include <vector>

int RELEVANT_OCCUPANCY_BISHOP[BOARD_SIZE];
int RELEVANT_OCCUPANCY_ROOK[BOARD_SIZE];

BitBoard BISHOP_MAGICS[BOARD_SIZE];
BitBoard ROOK_MAGICS[BOARD_SIZE];

BitBoard BISHOP_ATTACKS[64][512];
BitBoard ROOK_ATTACKS[64][4096];

U64 random_U64()
{
    U64 u1 = (U64)(random()) & 0xFFFF;
    U64 u2 = (U64)(random()) & 0xFFFF;
    U64 u3 = (U64)(random()) & 0xFFFF;
    U64 u4 = (U64)(random()) & 0xFFFF;

    return u1 | (u2 << 16) | (u3 << 32) | (u4 << 48);
}

BitBoard generate_random_magic()
{
    return BitBoard(random_U64() & random_U64() & random_U64());
}

BitBoard get_occupancy_bitboard(int index, int attack_mask_bits, BitBoard attack_mask)
{
    BitBoard occupancy = empty_board;

    for (int i = 0; i < attack_mask_bits; i++)
    {
        int square = attack_mask.get_ls1b_index();
        attack_mask.unset_bit(square);

        if (index & (1 << i))
            occupancy.set_bit(square);
    }

    return occupancy;
}

void init_relevant_occupancy()
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            int square = i * 8 + j;
            RELEVANT_OCCUPANCY_BISHOP[square] = bishop_attacks_mask(square).pop_count();
            RELEVANT_OCCUPANCY_ROOK[square] = rook_attacks_mask(square).pop_count();
        }
    }
}

BitBoard find_magic_number(int square, int relevant_bits, int bishop)
{
    BitBoard occupancies[4096];
    BitBoard attacks[4096];
    BitBoard used_atacks[4096];

    bishop = bishop == 2;
    BitBoard attack_mask = bishop ? bishop_attacks_mask(square) : rook_attacks_mask(square);
    int mask_pop = bishop ? RELEVANT_OCCUPANCY_BISHOP[square] : RELEVANT_OCCUPANCY_ROOK[square];

    int i, j, k, fail;
    for (i = 0; i < (1 << mask_pop); i++)
    {
        occupancies[i] = get_occupancy_bitboard(i, mask_pop, attack_mask);
        attacks[i] = bishop ? bishop_attacks_mask(square, occupancies[i]) : rook_attacks_mask(square, occupancies[i]);
    }

    for (k = 0; k < 100000000; k++)
    {
        BitBoard magic_number = generate_random_magic();

        if (((magic_number * attack_mask) & BitBoard(0xFF00000000000000ULL)).pop_count() < 6)
            continue;

        for (i = 0; i < 4096; i++)
            used_atacks[i] = empty_board;

        for (i = 0, fail = 0; !fail && (i < (1 << mask_pop)); i++)
        {
            j = (int)((occupancies[i] * magic_number) >> (64 - mask_pop));
            if (used_atacks[j] == empty_board)
                used_atacks[j] = attacks[i];
            else if (used_atacks[j] != attacks[i])
                fail = 1;
        }
        if (!fail)
            return magic_number;
    }
    cout << "FAILED\n";
    return empty_board;
}

void init_magic_numbers()
{
    for (int square = 0; square < BOARD_SIZE; square++)
    {
        BISHOP_MAGICS[square] = find_magic_number(square, RELEVANT_OCCUPANCY_BISHOP[square], BISHOP);
        ROOK_MAGICS[square] = find_magic_number(square, RELEVANT_OCCUPANCY_ROOK[square], ROOK);
    }
}

void init_attacks(int bishop)
{
    for (int square = 0; square < BOARD_SIZE; square++)
    {
        cout << " SQUARE " << square << endl;
        BitBoard attack_mask = bishop ? bishop_attacks_mask(square) : rook_attacks_mask(square);

        int relevant_bit_count = attack_mask.pop_count();

        int indicies = 1 << relevant_bit_count;

        for (int i = 0; i < indicies; i++)
        {
            cout << indicies - i << " ";
            if (bishop)
            {
                BitBoard occupancy = get_occupancy_bitboard(i, relevant_bit_count, attack_mask);
                int magic_index = (occupancy * BISHOP_MAGICS[square]) >> (64 - RELEVANT_OCCUPANCY_BISHOP[square]);
                BISHOP_ATTACKS[square][magic_index] = bishop_attacks_mask(square, occupancy);
            }
        }
    }
}

void init_magic_attacks()
{
    init_relevant_occupancy();
    cout << "found relevant occupancy" << endl;
    init_magic_numbers();
    cout << "found magics" << endl;
    init_attacks(1);
    cout << "initialized attacks" << endl;
}

BitBoard get_bishop_attacks(int square, BitBoard occupancy)
{
    // get bishop attacks assuming current board occupancy
    occupancy &= bishop_attacks_mask(square);
    occupancy *= BISHOP_MAGICS[square];
    occupancy >>= 64 - RELEVANT_OCCUPANCY_BISHOP[square];
    
    // return bishop attacks
    return BISHOP_ATTACKS[square][occupancy];
}