#include "state.cpp"
#include "move.cpp"
#include "attacks/normal_attacks.cpp"
#include "attacks/magic_attacks.cpp"

// TODO: do setbit in all move gen

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
    BitBoard bishop_board = empty_board;
    bishop_board.set_bit(d4);
    BitBoard occupancy_board = empty_board;
    occupancy_board.set_bit(f6);
    occupancy_board.set_bit(a7);
    occupancy_board.set_bit(c3);
    get_bishop_attacks(d4, occupancy_board).print();
}