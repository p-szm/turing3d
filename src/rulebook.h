//
//  rulebook.h
//  turing3d
//
//  Created by Patrick on 11/08/2015.
//  Copyright (c) 2015 Patrick. All rights reserved.
//

#ifndef __turing3d__rulebook__
#define __turing3d__rulebook__

#include <stdio.h>
#include <map>
#include "typedefs.h"
#include "instruction.h"

class RuleBook
{
public:
    Instruction get_instruction(State state, Symbol symbol);
    void add_rule(State state, Symbol symbol, Instruction instruction);
private:
    std::map<State, std::map<Symbol, Instruction> > data;
};

#endif /* defined(__turing3d__rulebook__) */
