#pragma once
#include <iostream>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
typedef uint64_t U64;
using namespace std;

#include "bitboard.cpp"

const int BOARD_SIZE = 64;

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

enum Promotions
{
    PROMOTION_NONE,
    PROMOTION_QUEEN,
    PROMOTION_ROOK,
    PROMOTION_BISHOP,
    PROMOTION_KNIGHT
};

const BitBoard empty_board = BitBoard();

const BitBoard NOT_A_FILE = BitBoard(0xFEFEFEFEFEFEFEFEull);
const BitBoard NOT_B_FILE = BitBoard(0xFDFDFDFDFDFDFDFDull);
const BitBoard NOT_G_FILE = BitBoard(0xBFBFBFBFBFBFBFBFull);
const BitBoard NOT_H_FILE = BitBoard(0x7F7F7F7F7F7F7F7Full);
const BitBoard NOT_AB_FILE = NOT_A_FILE & NOT_B_FILE;
const BitBoard NOT_GH_FILE = NOT_G_FILE & NOT_H_FILE;