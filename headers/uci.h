#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "globals.h"
#include "movelist.h"
#include "state.h"
#include "search.h"
#include "movegen.h"

class UCI
{
public:
    State state;

    void startUCIProtocol();
    void handle_go();
    void handle_position(const std::string &command);
    void handle_move(const std::string &move);
};