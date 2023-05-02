#include "state.cpp"
#include "move.cpp"
#include "attacks/piece_attacks.cpp"

int main()
{
    State state = State("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
    state.print();
    generate_leaping_attacks();
    generate_magic_attacks();
}