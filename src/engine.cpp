#include "state.cpp"
#include "move.cpp"
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
    State state = State("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
    state.print();
    BitBoard occupancy_board = empty_board;
    occupancy_board.set_bit(b4);
    occupancy_board.set_bit(e2);
    occupancy_board.set_bit(f4);
    get_rook_attacks(e4, occupancy_board).print();
}