#include "attacks/normal_attacks.cpp"
#include "attacks/magic_attacks.cpp"

void init_all()
{
    init_normal_attacks();
    init_magic_attacks();
}

int main()
{
    init_all();
    State state = State("rnbqkbnr/pp2p1pp/5p2/3pP3/1PpP4/2P5/P4PPP/RNBQKBNR b KQkq b3 0 5");
    state.print();

    MoveList move_list = MoveList();
    generate_pawn_moves(WHITE, move_list, state);

    move_list.print();
}