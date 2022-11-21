#pragma once
#include <iostream>
#include <stdint.h>
#include <vector>
#include <string>
using namespace std;

typedef uint64_t U64;

enum color
{
    WHITE = 0,
    BLACK = 1,
    BOTH = 2
};

enum piece
{
    wPAWN = 0,
    wKNIGHT = 1,
    wBISHOP = 2,
    wROOK = 3,
    wQUEEN = 4,
    wKING = 5,
    bPAWN = 6,
    bKNIGHT = 7,
    bBISHOP = 8,
    bROOK = 9,
    bQUEEN = 10,
    bKING = 11
};