#include "attacks/normal_attacks.cpp"
#include "attacks/magic_attacks.cpp"
#include "attacks/queen.cpp"

void init_all()
{
    init_normal_attacks();
    init_magic_attacks();
}

int main()
{
    init_all();
    State state = State("8/8/8/2ppp3/2pQp3/2ppp3/8/8 w - - 0 1");
    state.print();

    MoveList move_list = MoveList();
    generate_queen_moves(WHITE, move_list, state);

    move_list.print();
}