#include "../headers/uci.h"
#include "../headers/transposition_table.h"

void UCI::startUCIProtocol()
{
    std::cout << "id name HeadAche" << std::endl;
    std::cout << "id author Baher" << std::endl;
    std::cout << "uciok" << std::endl;

    std::string command;
    while (true)
    {
        std::getline(std::cin, command);

        if (command == "uci")
        {
            std::cout << "uciok" << std::endl;
        }
        else if (command == "isready")
        {
            std::cout << "readyok" << std::endl;
        }
        else if (command.substr(0, 8) == "position")
        {
            handle_position(command.substr(9));
        }
        else if (command.substr(0, 2) == "go")
        {
            handle_go();
        }
        else if (command == "quit")
        {
            break;
        }
    }
}

void UCI::handle_go()
{
    tt.clear();
    Searcher searcher;
    searcher.search(6, state);

    Move best_move = searcher.best_move;

    std::cout << "bestmove ";
    std::cout << SQUARE_TO_STRING[best_move.get_source()] << SQUARE_TO_STRING[best_move.get_target()];

    int promoted = best_move.get_promoted_piece();
    if (promoted)
    {
        if (promoted == wQUEEN || promoted == bQUEEN)
            std::cout << "q";
        else if (promoted == wROOK || promoted == bROOK)
            std::cout << "r";
        else if (promoted == wBISHOP || promoted == bBISHOP)
            std::cout << "b";
        else if (promoted == wKNIGHT || promoted == bKNIGHT)
            std::cout << "n";
    }

    std::cout << std::endl;
}

void UCI::handle_position(const std::string &command)
{
    if (command.find("startpos") != std::string::npos)
        state = State();
    else
        state = State(command.substr(4));

    int pos = command.find("moves");
    if (pos != std::string::npos)
    {
        std::string moves_string = command.substr(pos + 6);

        std::istringstream iss(moves_string);
        std::string temp_move;
        std::vector<std::string> moves;
        while (std::getline(iss, temp_move, ' '))
            moves.push_back(temp_move);

        for (int i = 0; i < moves.size(); i++)
            handle_move(moves[i]);
    }
}

void UCI::handle_move(const std::string &move)
{
    MoveList move_list;

    generate_moves(move_list, state);

    state.play_move(move_list.get_move(move));
}
