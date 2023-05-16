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
    State state = State();
    state.print();

    MoveList movelist = MoveList();
    generate_pawn_moves(WHITE, movelist, state);

    movelist.print();
}