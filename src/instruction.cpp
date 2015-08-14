//
//  instruction.cpp
//  turing3d
//
//  Created by Patrick on 11/08/2015.
//  Copyright (c) 2015 Patrick. All rights reserved.
//

#include "instruction.h"
#include <stdexcept>

Instruction::Instruction()
{
    direction = Vec3<int>(0, 0, 0);
    new_state = "None";
    new_symbol = ' ';
}

double abs_d(double x)
{
    if (x < 0)
        return -x;
    return x;
}

Instruction::Instruction(Vec3<int> dir, State state, Symbol symbol)
{
    int no_ones = 0;
    int no_zeros = 0;
    for (int i = 0; i < 3; i++)
    {
        int a = abs_d(dir.at(i));
        if (a == 0)
            no_zeros += 1;
        else if (a == 1)
            no_ones += 1;
    }
    if (no_ones != 1 || no_zeros != 2)
        throw std::invalid_argument("Invalid direction");
    
    direction = dir;
    new_state = state;
    new_symbol = symbol;
}

std::ostream& operator << (std::ostream &out, const Instruction &instr)
{
    out << "Write " << instr.new_symbol << ", change state to " << instr.new_state << " and go " << instr.direction;
    return out;
}