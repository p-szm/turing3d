//
//  turingmachine3d.cpp
//  turing3d
//
//  Created by Patrick on 11/08/2015.
//  Copyright (c) 2015 Patrick. All rights reserved.
//

#include "turingmachine3d.h"
#include <iostream>

TuringMachine3d::TuringMachine3d(Tape3d* t, RuleBook* book,
              State start_state, State end,
              Vec3<int> start_pos, bool verb)
{
    position = start_pos;
    tape = t;
    rulebook = book;
    state = start_state;
    end_state = end;
    verbose = verb;
    crashed = false;
    move_no = 0;
}

Symbol TuringMachine3d::read_square() const
{
    return tape->get(position.x, position.y, position.z);
}

void TuringMachine3d::move(Vec3<int> dir)
{
    position += dir;
}

void TuringMachine3d::change_state(State new_state)
{
    state = new_state;
}

void TuringMachine3d::write(Symbol symbol) const
{
    tape->set(position.x, position.y, position.z, symbol);
}

void TuringMachine3d::step()
{
    if (crashed and verbose)
        std::cout << "Machine has crashed" << std::endl;
    
    move_no++;
    Symbol sym = read_square();
    
    Instruction instr;
    try
    {
        instr = rulebook->get_instruction(state, sym);
    }
    catch (std::out_of_range)
    {
        if (verbose)
            std::cout << "Machine has crashed" << std::endl;
        crashed = true;
        return;
    }
    
    if (verbose)
        std::cout << "Move " << move_no <<
        ", pos " << position << ": " <<
        '(' << state << "," << sym << ")->(" <<
        instr.new_state << "," << instr.new_symbol << "), move by " <<
        instr.direction << std::endl;
    
    write(instr.new_symbol);
    move(instr.direction);
    change_state(instr.new_state);
}

State TuringMachine3d::get_state() const
{
    return state;
}

Vec3<int> TuringMachine3d::get_position() const
{
    return position;
}

bool TuringMachine3d::is_crashed() const
{
    return crashed;
}

bool TuringMachine3d::is_done() const
{
    return (state == end_state);
}