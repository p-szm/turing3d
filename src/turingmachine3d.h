//
//  turing.h
//  turing3d
//
//  Created by Patrick on 11/08/2015.
//  Copyright (c) 2015 Patrick. All rights reserved.
//

#ifndef __turing3d__turingmachine3d__
#define __turing3d__turingmachine3d__

#include <stdio.h>
#include <vector>
#include "typedefs.h"
#include "tape3d.h"
#include "rulebook.h"

class TuringMachine3d
{
public:
    TuringMachine3d(Tape3d* t, RuleBook* book,
                  State start_state, State end_state,
                  Vec3<int> start_pos, bool verb=false);
    Symbol read_square() const;
    void step();
    State get_state() const;
    Vec3<int> get_position() const;
    bool is_crashed() const;
    bool is_done() const;
private:
    Tape3d* tape;
    RuleBook* rulebook;
    
    Vec3<int> position;
    State state;
    State end_state;
    
    void move(Vec3<int> dir);
    void change_state(State new_state);
    void write(Symbol symbol) const;
    
    bool verbose;
    bool crashed;
};

#endif /* defined(__turing3d__turingmachine3d__) */
