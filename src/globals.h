#pragma once
#include <iostream>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <vector>

typedef uint64_t U64;
using namespace std;

#include "bitboard.cpp"

const int BOARD_SIZE = 64;
const int MAX_MOVES = 256;

enum {
    a8, b8, c8, d8, e8, f8, g8, h8,
    a7, b7, c7, d7, e7, f7, g7, h7,
    a6, b6, c6, d6, e6, f6, g6, h6,
    a5, b5, c5, d5, e5, f5, g5, h5,
    a4, b4, c4, d4, e4, f4, g4, h4,
    a3, b3, c3, d3, e3, f3, g3, h3,
    a2, b2, c2, d2, e2, f2, g2, h2,
    a1, b1, c1, d1, e1, f1, g1, h1
};

string SQUARE_TO_STRING[BOARD_SIZE] = {
    "a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8",
    "a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7",
    "a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6",
    "a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5",
    "a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4",
    "a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3",
    "a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2",
    "a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1"
};

u_int8_t CASTLING_RIGHTS[BOARD_SIZE] = {
    7, 15, 15, 15,  3, 15, 15, 11,
   15, 15, 15, 15, 15, 15, 15, 15,
   15, 15, 15, 15, 15, 15, 15, 15,
   15, 15, 15, 15, 15, 15, 15, 15,
   15, 15, 15, 15, 15, 15, 15, 15,
   15, 15, 15, 15, 15, 15, 15, 15,
   15, 15, 15, 15, 15, 15, 15, 15,
   13, 15, 15, 15, 12, 15, 15, 14
};

string PIECE_UNICODE[12] = {"♟︎", "♞", "♝", "♜", "♛", "♚", "♙", "♘", "♗", "♖", "♕", "♔"};

int SQUARE_TO_INDEX(string square) {
    int file = square[0] - 'a';
    int rank = square[1] - '1';
    return (7 - rank) * 8 + file;
}

enum color
{
    WHITE,
    BLACK,
    BOTH
};

enum pieceType
{
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING
};

enum piece
{
    wPAWN,
    wKNIGHT,
    wBISHOP,
    wROOK,
    wQUEEN,
    wKING,
    bPAWN,
    bKNIGHT,
    bBISHOP,
    bROOK,
    bQUEEN,
    bKING
};


const BitBoard empty_board = BitBoard();

const BitBoard NOT_A_FILE = BitBoard(0xFEFEFEFEFEFEFEFEull);
const BitBoard NOT_B_FILE = BitBoard(0xFDFDFDFDFDFDFDFDull);
const BitBoard NOT_G_FILE = BitBoard(0xBFBFBFBFBFBFBFBFull);
const BitBoard NOT_H_FILE = BitBoard(0x7F7F7F7F7F7F7F7Full);
const BitBoard NOT_AB_FILE = NOT_A_FILE & NOT_B_FILE;
const BitBoard NOT_GH_FILE = NOT_G_FILE & NOT_H_FILE;

BitBoard PAWN_ATTACKS[2][BOARD_SIZE];
BitBoard KNIGHT_ATTACKS[BOARD_SIZE];
BitBoard KING_ATTACKS[BOARD_SIZE];
BitBoard get_bishop_attacks(int square, BitBoard occupancy);
BitBoard get_rook_attacks(int square, BitBoard occupancy);
BitBoard get_queen_attacks(int square, BitBoard occupancy);