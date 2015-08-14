//
//  renderer.cpp
//  turing3d
//
//  Created by Patrick on 11/08/2015.
//  Copyright (c) 2015 Patrick. All rights reserved.
//

#include "renderer.h"
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include "tape3d.h"
#include "turingmachine3d.h"

double voxel_size = 0.5;

void Renderer::define_symbol_color(Symbol sym, Vec3<float> color)
{
    symbol_colors[sym] = color;
}

void Renderer::define_state_color(State state, Vec3<float> color)
{
    state_colors[state] = color;
}

void Renderer::render(const Tape3d *tape) const
{
    double cube_size = voxel_size * TAPE_SIZE;
    
    glColor3f(0, 0, 0);
    glLineWidth(0.5);
    glutWireCube(cube_size*1.01);
    
    glBegin(GL_LINES);
    glColor3f(1, 0, 0);
    glVertex3f(-cube_size*0.6, 0, 0);
    glVertex3f(cube_size, 0, 0);
    
    glColor3f(0, 1, 0);
    glVertex3f(0, -cube_size*0.6, 0);
    glVertex3f(0, cube_size, 0);
    
    glColor3f(0, 0, 1);
    glVertex3f(0, 0, -cube_size*0.6);
    glVertex3f(0, 0, cube_size);
    glEnd();
    
    for (auto it = tape->data.begin(); it != tape->data.end(); it++)
    {
        Symbol sym = it->second;
        if (sym == tape->default_elem)
            continue;
        int x = it->first.first;
        int y = it->first.second;
        int z = it->first.third;
        
        Vec3<float> symbol_color;
        try
        {
            // Use defined color
            symbol_color = symbol_colors.at(sym);
        }
        catch (std::out_of_range)
        {
            // Color not defined, use grey
            symbol_color = Vec3<float>(0.5, 0.5, 0.5);
        }
        
        glPushMatrix();
        glTranslated(voxel_size * x, voxel_size * y, voxel_size * z);
        glColor3f(symbol_color.x, symbol_color.y, symbol_color.z);
        glutSolidCube(voxel_size * 0.8);
        glColor3f(0, 0, 0);
        glutWireCube(voxel_size * 0.81);
        glPopMatrix();
    }
}

void Renderer::render(const TuringMachine3d *machine) const
{
    double machine_size = voxel_size*1.2;
    
    Vec3<float> state_color;
    try
    {
        // Use defined color
        state_color = state_colors.at(machine->get_state());
    }
    catch (std::out_of_range)
    {
        // Color not defined, use grey
        state_color = Vec3<float>(0.5, 0.5, 0.5);
    }
    
    glPushMatrix();
    
    Vec3<int> pos = machine->get_position();
    glTranslated(pos.x*voxel_size, pos.y*voxel_size, pos.z*voxel_size);
    glColor3f(0, 0, 0);
    glLineWidth(2);
    glutWireCube(machine_size);
    
    glColor4f(state_color.x, state_color.y, state_color.z, 0.5);
    glutSolidCube(machine_size);
    
    glPopMatrix();
}