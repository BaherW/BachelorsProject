#include "attacks/normal_attacks.cpp"
#include "attacks/magic_attacks.cpp"
#include "perft.cpp"

void init_all()
{
    init_normal_attacks();
    init_magic_attacks();
}

int main()
{
    init_all();
    State state = State("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1");
    state.print();

    cout << perft2(3, state).nodes << endl;
    cout << perft2(3, state).captures << endl;
    cout << perft2(3, state).enp << endl;
    cout << perft2(3, state).castles << endl;
}