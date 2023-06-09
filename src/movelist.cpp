#include "../headers/state.h"
#include "../headers/movelist.h"

int score_move(State &state, const Move &move)
{
    if (!move.is_capture())
        return 0;

    int start, end;
    if (state.current_color == WHITE)
    {
        start = wPAWN;
        end = wKING;
    }
    else
    {
        start = bPAWN;
        end = bKING;
    }

    int target_piece = wPAWN;
    for (int p = wPAWN; p <= bKING; p++)
    {
        if (state.position.pieces[p].get_bit(move.get_target()))
            target_piece = p;
    }

    return MVV_LVA[move.get_piece()][target_piece];
}

static bool compare_moves(State &state, const Move &move1, const Move &move2)
{
    int score1 = score_move(state, move1);
    int score2 = score_move(state, move2);
    return score1 > score2;
}

MoveList::MoveList(bool captures)
{
    num_moves = 0;
    captures_only = captures;
}

void MoveList::add_move(Move new_move)
{
    if (captures_only && !new_move.is_capture())
        return;
    moves[num_moves] = new_move;
    num_moves += 1;
}

Move MoveList::get_move(const string &move_string)
{
    int source = SQUARE_TO_INDEX(move_string.substr(0, 2));
    int target = SQUARE_TO_INDEX(move_string.substr(2, 3));

    for (int i = 0; i < num_moves; i++)
    {
        Move move = moves[i];

        if (move.get_source() == source && move.get_target() == target)
        {
            int promoted_piece = move.get_promoted_piece();

            if (promoted_piece)
            {
                char promotion = move_string[4];

                if (promotion == 'q' && (promoted_piece == wQUEEN || promoted_piece == bQUEEN))
                    return move;

                else if (promotion == 'r' && (promoted_piece == wROOK || promoted_piece == bROOK))
                    return move;

                else if (promotion == 'b' && (promoted_piece == wBISHOP || promoted_piece == bBISHOP))
                    return move;

                else if (promotion == 'n' && (promoted_piece == wKNIGHT || promoted_piece == bKNIGHT))
                    return move;
            }

            return move;
        }
    }
    return Move();
}

void MoveList::sort_moves(State &state)
{
    std::sort(moves, moves + num_moves, [&](const Move &move1, const Move &move2)
              { return compare_moves(state, move1, move2); });
}

void MoveList::print()
{
    for (int i = 0; i < num_moves; i++)
    {
        moves[i].print();
    }
}
