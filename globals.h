#pragma once
#include <iostream>
#include <stdint.h>
#include <vector>
#include <string>
typedef uint64_t U64;
using namespace std;

#include "bitboard.cpp"

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


BitBoard empty_board = BitBoard();

BitBoard NOT_A_FILE = BitBoard(0xFEFEFEFEFEFEFEFEull);
BitBoard NOT_B_FILE = BitBoard(0xFDFDFDFDFDFDFDFDull);
BitBoard NOT_G_FILE = BitBoard(0xBFBFBFBFBFBFBFBFull);
BitBoard NOT_H_FILE = BitBoard(0x7F7F7F7F7F7F7F7Full);
BitBoard NOT_AB_FILE = NOT_A_FILE & NOT_B_FILE;
BitBoard NOT_GH_FILE = NOT_G_FILE & NOT_H_FILE;