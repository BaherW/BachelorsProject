#include "../headers/attacks.h"
#include "../headers/magic_attacks.h"
#include "../headers/zobrist.h"
#include "../headers/uci.h"
#include "../headers/perft.h"
#include "../headers/eval.h"
#include <windows.h>


void init_all()
{
    init_normal_attacks();
    init_magic_attacks();
    init_keys();
    init_pesto_tables();
}

int main()
{
    init_all();

    // For printing on windows
    SetConsoleOutputCP(CP_UTF8);
    
    UCI uci;
    uci.startUCIProtocol();
}