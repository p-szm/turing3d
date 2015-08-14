//
//  loader.cpp
//  turing3d
//
//  Created by Patrick on 12/08/2015.
//  Copyright (c) 2015 Patrick. All rights reserved.
//

#include "loader.h"
#include <fstream>
#include <iostream>
#include "tape3d.h"
#include "rulebook.h"
#include "instruction.h"
#include "renderer.h"
#include "turingmachine3d.h"

#define BUF_SIZE 32

int load_from_file(std::string filename, Tape3d*& tape, RuleBook*& rulebook,
                   TuringMachine3d*& machine, Renderer*& renderer)
{
    std::ifstream file(filename.c_str());
    if (!file.is_open())
        return 1;
    
    enum Mode {NONE, START_STATE, END_STATE, START_POS, DEFAULT_SYMBOL,
        TAPE_SYMBOLS, SYMBOL_COLORS, STATE_COLORS, RULES};
    Mode mode = NONE;
    
    tape = new Tape3d(' ');
    rulebook = new RuleBook;
    renderer = new Renderer;
    std::string start_state = "START";
    std::string end_state = "END";
    Vec3<int> start_pos;
    
    std::string line;
    while (getline(file, line))
    {
        if (line == "[START_STATE]")
        {
            mode = START_STATE;
            continue;
        }
        else if (line == "[END_STATE]")
        {
            mode = END_STATE;
            continue;
        }
        else if (line == "[START_POS]")
        {
            mode = START_POS;
            continue;
        }
        else if (line == "[DEFAULT_SYMBOL]")
        {
            mode = DEFAULT_SYMBOL;
            continue;
        }
        else if (line == "[TAPE_SYMBOLS]")
        {
            mode = TAPE_SYMBOLS;
            continue;
        }
        else if (line == "[SYMBOL_COLORS]")
        {
            mode = SYMBOL_COLORS;
            continue;
        }
        else if (line == "[STATE_COLORS]")
        {
            mode = STATE_COLORS;
            continue;
        }
        else if (line == "[RULES]")
        {
            mode = RULES;
            continue;
        }
        
        if (mode == START_STATE)
        {
            char str[BUF_SIZE];
            int n = sscanf(line.c_str(), "%s", str);
            if (n == 1)
                start_state = str;
        }
        else if (mode == END_STATE)
        {
            char str[BUF_SIZE];
            int n = sscanf(line.c_str(), "%s", str);
            if (n == 1)
                end_state = str;
        }
        else if (mode == START_POS)
        {
            int x, y, z;
            int n = sscanf(line.c_str(), "(%d %d %d)", &x, &y, &z);
            if (n == 3)
                start_pos = Vec3<int>(x, y, z);
        }
        else if (mode == DEFAULT_SYMBOL)
        {
            char c;
            int n = sscanf(line.c_str(), "%c", &c);
            if (n == 1)
                tape->set_default_element(c);
        }
        else if (mode == TAPE_SYMBOLS)
        {
            int x, y, z;
            char c;
            int n = sscanf(line.c_str(), "(%d %d %d) = %c", &x, &y, &z, &c);
            if (n == 4)
                tape->set(x, y, z, c);
        }
        else if (mode == RULES)
        {
            char prev_state[BUF_SIZE];
            char next_state[BUF_SIZE];
            char prev_c;
            char next_c;
            int x, y, z;
            int n = sscanf(line.c_str(), "%s %c = %s %c (%d %d %d)", prev_state, &prev_c, next_state, &next_c, &x, &y, &z);
            if (n == 7)
            {
                Instruction instr(Vec3<int>(x, y, z), next_state, next_c);
                rulebook->add_rule(prev_state, prev_c, instr);
            }
        }
        
        else if (mode == SYMBOL_COLORS)
        {
            char sym;
            float r, g, b;
            int n = sscanf(line.c_str(), "%c = (%f %f %f)", &sym, &r, &g, &b);
            if (n == 4)
                renderer->define_symbol_color(sym, Vec3<float>(r, g, b));
        }
        
        else if (mode == STATE_COLORS)
        {
            char state[BUF_SIZE];
            float r, g, b;
            int n = sscanf(line.c_str(), "%s = (%f %f %f)", state, &r, &g, &b);
            if (n == 4)
                renderer->define_state_color(state, Vec3<float>(r, g, b));
        }
    }
    
    machine = new TuringMachine3d(tape, rulebook, start_state, end_state, start_pos, true);
    
    file.close();
    
    return 0;
}