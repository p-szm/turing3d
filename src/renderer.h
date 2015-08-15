//
//  renderer.h
//  turing3d
//
//  Created by Patrick on 11/08/2015.
//  Copyright (c) 2015 Patrick. All rights reserved.
//

#ifndef __turing3d__renderer__
#define __turing3d__renderer__

#include <stdio.h>
#include <map>
#include "vec3.h"
#include "typedefs.h"

class Tape3d;
class TuringMachine3d;

class Renderer
{
public:
    Renderer();
    void render(const Tape3d* tape) const;
    void render(const TuringMachine3d* machine) const;
    
    void define_symbol_color(Symbol sym, Vec3<float> color);
    void define_state_color(State state, Vec3<float> color);
    
    float axis_len;
    float voxel_size;
private:
    std::map<Symbol, Vec3<float> > symbol_colors;
    std::map<State, Vec3<float> > state_colors;
};

#endif /* defined(__turing3d__renderer__) */
