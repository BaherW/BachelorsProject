#pragma once
#include "pawn.cpp"
#include "knight.cpp"
#include "king.cpp"

void init_normal_attacks()
{
    init_pawn_attacks();
    init_knight_attacks();
    init_king_attacks();
}