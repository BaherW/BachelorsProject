#pragma once
#include "globals.h"

class Castling
{
public:
    uint8_t castle_rights;

    Castling()
    {
        castle_rights = 0b00001111;
    }

    Castling(uint8_t rights)
    {
        castle_rights = rights;
    }

    Castling(string fen)
    {
        castle_rights = 0b00000000;
        if (fen == "-")
            return;
        else
        {
            for (char c : fen)
            {
                switch (c)
                {
                case 'K':
                    castle_rights |= 0b0001;
                    break;
                case 'Q':
                    castle_rights |= 0b0010;
                    break;
                case 'k':
                    castle_rights |= 0b0100;
                    break;
                case 'q':
                    castle_rights |= 0b1000;
                    break;
                default:
                    break;
                }
            }
        }
    }

    void update_castle_right(int source, int target)
    {
        castle_rights &= CASTLING_RIGHTS[source] & CASTLING_RIGHTS[target];
    }

    bool wk_can_castle()
    {
        return castle_rights & 0b00000001;
    }

    bool wq_can_castle()
    {
        return castle_rights & 0b00000010;
    }

    bool bk_can_castle()
    {
        return castle_rights & 0b00000100;
    }

    bool bq_can_castle()
    {
        return castle_rights & 0b00001000;
    }

    void disable_wk_castle()
    {
        castle_rights &= 0b00001110;
    }

    void disable_wq_castle()
    {
        castle_rights &= 0b00001101;
    }

    void disable_bk_castle()
    {
        castle_rights &= 0b00001011;
    }

    void disable_bq_castle()
    {
        castle_rights &= 0b00000111;
    }

    void print()
    {
        string output = "Castling: ";
        if (wk_can_castle())
            output.append("K");
        if (wq_can_castle())
            output.append("Q");
        if (bk_can_castle())
            output.append("k");
        if (bq_can_castle())
            output.append("q");
        if (output == "Castling: ")
            output.append("-");
        cout << output;
    }
};