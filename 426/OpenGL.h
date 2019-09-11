#ifndef OPENGL_H
#define OPENGL_H

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>

#include "MainApp.h"
#include <thread>
#include <mutex>

void init();
void display();
void glutTimer_(int value);
void Build(MainApp &mapp);
void Calc(MainApp &mapp);

#endif
