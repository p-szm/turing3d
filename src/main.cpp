//
//  main.cpp
//  turing3d
//
//  Created by Patrick on 11/08/2015.
//  Copyright (c) 2015 Patrick. All rights reserved.
//

#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <iostream>
#include <cmath>
#include "turingmachine3d.h"
#include "arrows.h"
#include "renderer.h"
#include "loader.h"
#include "typedefs.h"
#include "timer.h"

double delay = 0.5;
double dt = 0.005;

int width = 800;
int height = 600;
double theta = 20.0;
double phi = 30.0;
double r = 15.0;
double eyeX = 0.0;
double eyeY = 0.0;
double eyeZ = r;
double upX = 0.0;
double upY = 1.0;
double upZ = 0.0;

Tape3d* tape;
RuleBook* rulebook;
TuringMachine3d* machine;
Renderer* renderer;
Arrows arrows;
Timer timer(delay);
bool manual = false;

void quit()
{
    delete tape;
    delete rulebook;
    delete machine;
    delete renderer;
    std::exit(0);
}

void update_view()
{
    // Convert spherical to Cartesian coordinates
    double c = M_PI / 180.0;
    eyeX = r * sin(theta*c) * cos(phi*c);
    eyeY = r * sin(phi*c);
    eyeZ = r * cos(theta*c) * cos(phi*c);
    
    // Calculate up vector
    GLfloat dt = 1.0;
    GLfloat eyeXtemp = r * sin(theta*c) * cos(phi*c - dt);
    GLfloat eyeYtemp = r * sin(phi*c - dt);
    GLfloat eyeZtemp = r * cos(theta*c) * cos(phi*c - dt);
    upX = eyeX - eyeXtemp;
    upY = eyeY - eyeYtemp;
    upZ = eyeZ - eyeZtemp;
    
    // Define the projection transformation
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, width/(float)height, 0.1, r + renderer->axis_len*2);
}

void update_axes()
{
    // Change the length of the axes
    renderer->axis_len = r/2.0;
    if (renderer->axis_len < 10.0)
        renderer->axis_len = 10.0;
}

void onMouseMove(int x, int y)
{
    // Change mouse coordinates to the coordinate system with
    // the centre in the middle of the screen
    x = (x - width / 2);
    y = - (y - height / 2);
    
    // Convert mouse position to angles
    theta = -0.5 * 360.0 * x / 400.0;
    phi = -0.5 * 360.0 * y / 400.0;
    
    // Trim angles
    if (theta > 360)
        theta = fmod((double)theta, 360.0);
    if (phi > 360)
        phi = fmod((double)theta, 360.0);
    
    update_view();
    
    // Refresh the display
    glutPostRedisplay();
}


void display()
{
    // Clear window
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Switch to the modelview matrix
    glMatrixMode(GL_MODELVIEW);
    
    glLoadIdentity();
    gluLookAt(eyeX, eyeY, eyeZ, 0.0, 0.0, 0.0, upX, upY, upZ);
    
    renderer->render(tape);
    renderer->render(machine);
    
    glutSwapBuffers();
    glFlush();
}

void reshape(int w, int h)
{
    width = w;
    height = h;
    glViewport(0, 0, width, height);
    update_view();
}

void key_down(unsigned char key, int x, int y)
{
    if (key == 27)
    {
        quit();
    }
    if (key == 13 and manual)
    {
        machine->step();
    }
}

void special_key_down(int key, int x, int y)
{
    // Remember which arrows were pressed
    if (key == GLUT_KEY_UP)
        arrows.up = true;
    if (key == GLUT_KEY_DOWN)
        arrows.down = true;
    if (key == GLUT_KEY_LEFT)
        arrows.left = true;
    if (key == GLUT_KEY_RIGHT)
        arrows.right = true;
}

void special_key_up(int key, int x, int y)
{
    if (key == GLUT_KEY_UP)
        arrows.up = false;
    if (key == GLUT_KEY_DOWN)
        arrows.down = false;
    if (key == GLUT_KEY_LEFT)
        arrows.left = false;
    if (key == GLUT_KEY_RIGHT)
        arrows.right = false;
}

void idle()
{
    if (arrows.up)
    {
        r /= 1.01;
        update_view();
        update_axes();
    }
    else if (arrows.down)
    {
        r *= 1.01;
        update_view();
        update_axes();
    }
    else if (arrows.left)
    {
        delay += dt;
        timer.set_interval(delay);
    }
    else if (arrows.right)
    {
        delay -= dt;
        if (delay < 0)
            delay = 0;
        timer.set_interval(delay);
    }
    
    // Run the Turing machine
    if (!manual)
    {
        if (!machine->is_crashed() && !machine->is_done() && timer.is_done())
        {
            machine->step();
            timer.reset();
        }
    }
    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cerr << "Usage: ./turing3d program" << std::endl;
        std::exit(1);
    }
    int res = load_from_file(argv[1],
                             tape, rulebook, machine, renderer);
    if (res != 0)
    {
        std::cerr << "Error loading " << argv[1] << std::endl;
        std::exit(1);
    }
    
    // Initiallize GLUT
    glutInit(&argc, argv);
    
    // Setup for the new window
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(width, height);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    
    // Create a window
    std::string full_fname = std::string(argv[1]);
    std::string fname = full_fname.substr(full_fname.find_last_of("/\\")+1);
    std::string window_title = "turing3d (" + fname + ")";
    glutCreateWindow(window_title.c_str());
    
    // Register callback functions
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(key_down);
    glutSpecialFunc(special_key_down);
    glutSpecialUpFunc(special_key_up);
    glutIdleFunc(idle);
    glutPassiveMotionFunc(onMouseMove);
    
    // Set up depth-buffering
    glEnable(GL_DEPTH_TEST);
    
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_POINT_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eyeX, eyeY, eyeZ, 0.0, 0.0, 0.0, upX, upY, upZ);
    
    update_view();
    
    timer.reset();
    
    // Enter the main loop
    glutMainLoop();
}
