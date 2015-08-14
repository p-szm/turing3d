//
//  rulebook.cpp
//  turing3d
//
//  Created by Patrick on 11/08/2015.
//  Copyright (c) 2015 Patrick. All rights reserved.
//

#include "rulebook.h"

Instruction RuleBook::get_instruction(State state, Symbol symbol)
{
    return data.at(state).at(symbol);
}

void RuleBook::add_rule(State state, Symbol symbol, Instruction instruction)
{
    data[state][symbol] = instruction;
}