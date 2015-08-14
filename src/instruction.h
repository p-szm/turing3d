//
//  instruction.h
//  turing3d
//
//  Created by Patrick on 11/08/2015.
//  Copyright (c) 2015 Patrick. All rights reserved.
//

#ifndef __turing3d__instruction__
#define __turing3d__instruction__

#include <stdio.h>
#include <iostream>
#include "vec3.h"
#include "typedefs.h"

struct Instruction
{
    Instruction();
    Instruction(Vec3<int> dir, State state, Symbol symbol);
    Vec3<int> direction;
    State new_state;
    Symbol new_symbol;
    friend std::ostream& operator << (std::ostream &out, const Instruction &instr);
};

#endif /* defined(__turing3d__instruction__) */
