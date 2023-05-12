#pragma once
#include "../globals.h"
#include "bishop.cpp"
#include "rook.cpp"
#include "magics.cpp"

BitBoard BISHOP_MASKS[BOARD_SIZE];
BitBoard ROOK_MASKS[BOARD_SIZE];

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

BitBoard find_magic_number(int square, int relevant_bits, int bishop)
{
    BitBoard occupancies[4096];
    BitBoard attacks[4096];
    BitBoard used_atacks[4096];

    bishop = bishop == 2;
    BitBoard attack_mask = bishop ? BISHOP_MASKS[square] : ROOK_MASKS[square];

    int i, j, k, fail;
    for (i = 0; i < (1 << relevant_bits); i++)
    {
        occupancies[i] = get_occupancy_bitboard(i, relevant_bits, attack_mask);
        attacks[i] = bishop ? bishop_attacks_mask(square, occupancies[i], 1) : rook_attacks_mask(square, occupancies[i], 1);
    }

    for (k = 0; k < 100000000; k++)
    {
        BitBoard magic_number = generate_random_magic();

        if (((magic_number * attack_mask) & BitBoard(0xFF00000000000000ULL)).pop_count() < 6)
            continue;

        for (i = 0; i < 4096; i++)
            used_atacks[i] = empty_board;

        for (i = 0, fail = 0; !fail && (i < (1 << relevant_bits)); i++)
        {
            j = (int)((occupancies[i] * magic_number) >> (64 - relevant_bits));
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
        BISHOP_MASKS[square] = bishop_attacks_mask(square);
        ROOK_MASKS[square] = rook_attacks_mask(square);

        RELEVANT_OCCUPANCY_BISHOP[square] = BISHOP_MASKS[square].pop_count();
        RELEVANT_OCCUPANCY_ROOK[square] = ROOK_MASKS[square].pop_count();

       //BISHOP_MAGICS[square] = find_magic_number(square, RELEVANT_OCCUPANCY_BISHOP[square], BISHOP);
        //ROOK_MAGICS[square] = find_magic_number(square, RELEVANT_OCCUPANCY_ROOK[square], ROOK);

        BISHOP_MAGICS[square] = BISHOP_SAVED_MAGICS[square];
        ROOK_MAGICS[square] = ROOK_SAVED_MAGICS[square];
    }
    
}

void init_attacks()
{
    for (int square = 0; square < BOARD_SIZE; square++)
    {
        int bishop_bits = BISHOP_MASKS[square].pop_count();
        int rook_bits = ROOK_MASKS[square].pop_count();

        for (int i = 0; i < (1 << bishop_bits); i++)
        {
            BitBoard occupancy = get_occupancy_bitboard(i, bishop_bits, BISHOP_MASKS[square]);
            int magic_index = (occupancy * BISHOP_MAGICS[square]) >> (64 - RELEVANT_OCCUPANCY_BISHOP[square]);
            BISHOP_ATTACKS[square][magic_index] = bishop_attacks_mask(square, occupancy, 1);
        }
        for (int i = 0; i < (1 << rook_bits); i++)
        {
            BitBoard occupancy = get_occupancy_bitboard(i, rook_bits, ROOK_MASKS[square]);
            int magic_index = (occupancy * ROOK_MAGICS[square]) >> (64 - RELEVANT_OCCUPANCY_ROOK[square]);
            ROOK_ATTACKS[square][magic_index] = rook_attacks_mask(square, occupancy, 1);
        }
    }
}

void init_magic_attacks()
{
    init_magic_numbers();
    init_attacks();
}

BitBoard get_bishop_attacks(int square, BitBoard occupancy)
{
    occupancy &= BISHOP_MASKS[square];
    occupancy *= BISHOP_MAGICS[square];
    occupancy >>= 64 - RELEVANT_OCCUPANCY_BISHOP[square];

    return BISHOP_ATTACKS[square][occupancy];
}

BitBoard get_rook_attacks(int square, BitBoard occupancy)
{
    occupancy &= ROOK_MASKS[square];
    occupancy *= ROOK_MAGICS[square];
    occupancy >>= 64 - RELEVANT_OCCUPANCY_ROOK[square];

    return ROOK_ATTACKS[square][occupancy];
}

BitBoard get_queen_attacks(int square, BitBoard occupancy)
{
    BitBoard attacks = get_bishop_attacks(square, occupancy);

    attacks |= get_rook_attacks(square, occupancy);

    return attacks;
}