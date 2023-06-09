#include "../headers/attacks.h"
#include "../headers/magic_attacks.h"
#include "../headers/zobrist.h"
#include "../headers/uci.h"

void init_all()
{
    init_normal_attacks();
    init_magic_attacks();
    init_keys();
}

int main()
{
    init_all();

    UCI uci;
    uci.startUCIProtocol();
}