#include "../headers/magic_attacks.h"
#include "../headers/attacks.h"

BitBoard BISHOP_MASKS[BOARD_SIZE];
BitBoard ROOK_MASKS[BOARD_SIZE];

int RELEVANT_OCCUPANCY_BISHOP[BOARD_SIZE] = {
    6, 5, 5, 5, 5, 5, 5, 6,
    5, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 7, 7, 7, 7, 5, 5,
    5, 5, 7, 9, 9, 7, 5, 5,
    5, 5, 7, 9, 9, 7, 5, 5,
    5, 5, 7, 7, 7, 7, 5, 5,
    5, 5, 5, 5, 5, 5, 5, 5,
    6, 5, 5, 5, 5, 5, 5, 6};

int RELEVANT_OCCUPANCY_ROOK[BOARD_SIZE] = {
    12, 11, 11, 11, 11, 11, 11, 12,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    12, 11, 11, 11, 11, 11, 11, 12};

BitBoard BISHOP_MAGICS[BOARD_SIZE];
BitBoard ROOK_MAGICS[BOARD_SIZE];

BitBoard BISHOP_ATTACKS[64][512];
BitBoard ROOK_ATTACKS[64][4096];

BitBoard generate_random_magic()
{
    return BitBoard(random_U64() & random_U64() & random_U64());
}

BitBoard get_occupancy_bitboard(int index, int attack_mask_bits, BitBoard attack_mask)
{
    BitBoard occupancy = EMPTY_BOARD;

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
            used_atacks[i] = EMPTY_BOARD;

        for (i = 0, fail = 0; !fail && (i < (1 << relevant_bits)); i++)
        {
            j = (int)((occupancies[i] * magic_number) >> (64 - relevant_bits));
            if (used_atacks[j] != EMPTY_BOARD)
                used_atacks[j] = attacks[i];
            else if (used_atacks[j] != attacks[i])
                fail = 1;
        }
        if (!fail)
            return magic_number;
    }
    cout << "FAILED\n";
    return EMPTY_BOARD;
}

void init_magic_numbers()
{
    for (int square = 0; square < BOARD_SIZE; square++)
    {
        BISHOP_MASKS[square] = bishop_attacks_mask(square, EMPTY_BOARD, 0);
        ROOK_MASKS[square] = rook_attacks_mask(square, EMPTY_BOARD, 0);

        // Currently my magic numbers are stored in magics.cpp, to regenerate them uncomment the following lines and print them:
        // BISHOP_MAGICS[square] = find_magic_number(square, RELEVANT_OCCUPANCY_BISHOP[square], BISHOP);
        // ROOK_MAGICS[square] = find_magic_number(square, RELEVANT_OCCUPANCY_ROOK[square], ROOK);

        // Comment these lines out if we are generating new magic numbers.
        BISHOP_MAGICS[square] = BISHOP_SAVED_MAGICS[square];
        ROOK_MAGICS[square] = ROOK_SAVED_MAGICS[square];
    }
}

void init_attacks()
{
    for (int square = 0; square < BOARD_SIZE; square++)
    {
        int bishop_bits = RELEVANT_OCCUPANCY_BISHOP[square];
        int rook_bits = RELEVANT_OCCUPANCY_ROOK[square];

        for (int i = 0; i < (1 << bishop_bits); i++)
        {
            BitBoard occupancy = get_occupancy_bitboard(i, bishop_bits, BISHOP_MASKS[square]);
            int magic_index = (occupancy * BISHOP_MAGICS[square]) >> (64 - bishop_bits);
            BISHOP_ATTACKS[square][magic_index] = bishop_attacks_mask(square, occupancy, 1);
        }
        for (int i = 0; i < (1 << rook_bits); i++)
        {
            BitBoard occupancy = get_occupancy_bitboard(i, rook_bits, ROOK_MASKS[square]);
            int magic_index = (occupancy * ROOK_MAGICS[square]) >> (64 - rook_bits);
            ROOK_ATTACKS[square][magic_index] = rook_attacks_mask(square, occupancy, 1);
        }
    }
}

void init_magic_attacks()
{
    init_magic_numbers();
    init_attacks();
}

BitBoard get_bishop_attacks(const int &square, BitBoard occupancy)
{
    //Turn off Magic Bitboard:
    //return bishop_attacks_mask(square, occupancy, 1);

    occupancy &= BISHOP_MASKS[square];
    occupancy *= BISHOP_MAGICS[square];
    occupancy >>= 64 - RELEVANT_OCCUPANCY_BISHOP[square];

    return BISHOP_ATTACKS[square][occupancy];
}

BitBoard get_rook_attacks(const int &square, BitBoard occupancy)
{
    // Turn off Magic Bitboard:
    //return rook_attacks_mask(square, occupancy, 1);

    occupancy &= ROOK_MASKS[square];
    occupancy *= ROOK_MAGICS[square];
    occupancy >>= 64 - RELEVANT_OCCUPANCY_ROOK[square];

    return ROOK_ATTACKS[square][occupancy];
}

BitBoard get_queen_attacks(const int &square, BitBoard occupancy)
{
    BitBoard attacks = get_bishop_attacks(square, occupancy);

    attacks |= get_rook_attacks(square, occupancy);

    return attacks;
}