//
//  main.cpp
//  GLTest
//
//  Created by nspool on 7/05/2016.
//  Copyright © 2016 tujv. All rights reserved.
//
///////////////////////////////////////////////////////////////////////
//
// triangles.cpp
//
///////////////////////////////////////////////////////////////////////


#include <iostream>
using namespace std;

#include <GL/glew.h>
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#define BUFFER_OFFSET(x)  ((const void*) (x))

#include "LoadShaders.h"

enum VAO_IDs { Triangles, NumVAOs };
enum Buffer_IDs { ArrayBuffer, NumBuffers };
enum Attrib_IDs { vPosition = 0 };

GLuint  VAOs[NumVAOs];
GLuint  Buffers[NumBuffers];

const GLuint  NumVertices = 6;

//---------------------------------------------------------------------
//
// init
//

void
init(void)
{
  glGenVertexArrays(NumVAOs, VAOs);
  glBindVertexArray(VAOs[Triangles]);
  
  GLfloat  vertices[NumVertices][2] = {
    { -0.90, -0.90 },  // Triangle 1
    {  0.85, -0.90 },
    { -0.90,  0.85 },
    {  0.90, -0.85 },  // Triangle 2
    {  0.90,  0.90 },
    { -0.85,  0.90 }
  };
  
  glGenBuffers(NumBuffers, Buffers);
  glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),
               vertices, GL_STATIC_DRAW);
  
  ShaderInfo  shaders[] = {
    { GL_VERTEX_SHADER, "triangles.vert" },
    { GL_FRAGMENT_SHADER, "triangles.frag" },
    { GL_NONE, NULL }
  };
  
  GLuint program = LoadShaders(shaders);
  glUseProgram(program);
  
  glVertexAttribPointer(vPosition, 2, GL_FLOAT,
                        GL_FALSE, 0, BUFFER_OFFSET(0));
  glEnableVertexAttribArray(vPosition);
}

//---------------------------------------------------------------------
//
// display
//

void
display(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  
  glBindVertexArray(VAOs[Triangles]);
  glDrawArrays(GL_TRIANGLES, 0, NumVertices);
  
  glFlush();
}

//---------------------------------------------------------------------
//
// main
//

int
main(int argc, char** argv)
{
  
  
  
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_3_2_CORE_PROFILE);
  glutInitWindowSize(512, 512);
  glutCreateWindow(argv[0]);
  
  glewExperimental = GL_TRUE;
  
  if (glewInit()) {
    cerr << "Unable to initialize GLEW ... exiting" << endl;
    exit(EXIT_FAILURE);
  }
  
  init();
  
  glutDisplayFunc(display);
  
  glutMainLoop();
}
