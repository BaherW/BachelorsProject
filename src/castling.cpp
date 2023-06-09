#include "../headers/castling.h"

uint8_t CASTLING_RIGHTS[BOARD_SIZE] = {
    7, 15, 15, 15,  3, 15, 15, 11,
   15, 15, 15, 15, 15, 15, 15, 15,
   15, 15, 15, 15, 15, 15, 15, 15,
   15, 15, 15, 15, 15, 15, 15, 15,
   15, 15, 15, 15, 15, 15, 15, 15,
   15, 15, 15, 15, 15, 15, 15, 15,
   15, 15, 15, 15, 15, 15, 15, 15,
   13, 15, 15, 15, 12, 15, 15, 14
};

Castling::Castling()
{
    castle_rights = 0b00001111;
}

Castling::Castling(uint8_t rights)
{
    castle_rights = rights;
}

Castling::Castling(string fen)
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

void Castling::update_castle_right(const int &source, const int &target)
{
    castle_rights &= CASTLING_RIGHTS[source] & CASTLING_RIGHTS[target];
}

bool Castling::wk_can_castle()
{
    return castle_rights & 0b00000001;
}

bool Castling::wq_can_castle()
{
    return castle_rights & 0b00000010;
}

bool Castling::bk_can_castle()
{
    return castle_rights & 0b00000100;
}

bool Castling::bq_can_castle()
{
    return castle_rights & 0b00001000;
}

void Castling::print()
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
