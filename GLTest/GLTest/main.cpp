//
//  main.cpp
//  GLTest by nspool
//


#include <iostream>
#include <GL/glew.h>
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include "LoadShaders.h"

#define BUFFER_OFFSET(x)  ((const void*) (x))

enum VAO_IDs { Triangles, NumVAOs };
enum Buffer_IDs { ArrayBuffer, NumBuffers };
enum Attrib_IDs { vPosition = 0 };
GLuint  VAOs[NumVAOs];
GLuint  Buffers[NumBuffers];
const GLuint  NumVertices = 6;

using namespace std;

void
init(void)
{
    // allocate vertex array object names for our use
    glGenVertexArrays(NumVAOs, VAOs);
    
    // create a new vertex-array objects for the previously assigned names
    // when binding an object for the first time OpenGL internally allocs memory
    // and makes the object *current*, ie. any operations relavent to the bound
    // object will affect its state from now on
    
    glBindVertexArray(VAOs[Triangles]); // initialised to default state
    
    // use glDeleteVertexArrays to delete when finished, or
    // use glIsVertexArray to test if previously generated but not deleted
    // now initialise the vertex-buffer objects
    
    // normalised device coordinates, always within [-1,1] in x & y
    GLfloat vertices[6][2] = {
        { -0.90, -0.90 },
        {  0.85, -0.90 },
        { -0.90,  0.85 },
        {  0.90, -0.85 },
        {  0.90,  0.90 },
        { -0.85,  0.90 }
    };
    
    // create some names for the vertex buffer objects
    glGenBuffers(NumBuffers, Buffers);
    
    // now bring them into existence
    // delete with glDeleteBuffer, check with glIsBuffer
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
    
    // allocate storage for and transfer vertex data into the buffer object
    // we could be reading |vertices| in from a file or dynamically generating them
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    // must provide *at least* a vertex shader and a fragment shader
    ShaderInfo shaders[] = {
        { GL_VERTEX_SHADER, "triangles.vert" },
        { GL_FRAGMENT_SHADER, "triangles.frag" },
        { GL_NONE, NULL }
    };
    
    GLuint program = LoadShaders(shaders);
    glUseProgram(program);
    
    // "shader plumbing" associating application data with variables in the shader programs
    // associate variables in a vertex shader with data stored in a buffer object
    // connect shader 'in' variables to a *vertex-attribute array*
    // |vPosition| is the location value for the respective vertex shader input variable
    // |2| is the number if values for each vertex
    glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    // enable the vertex array
    glEnableVertexAttribArray(vPosition);
}

void
display(void)
{
    // Clear the screen, clearing colour is black by default
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Render objects
    glBindVertexArray(VAOs[Triangles]);
    
    // actually send vertex objects to the OpenGL pipeline
    glDrawArrays(GL_TRIANGLES, 0, NumVertices);
    
    // process any pending OpenGL calls
    glFlush(); // non-blocking, can use glFinish for blocking, but only in development!
}


int
main(int argc, char** argv)
{
    
    // initialise the GLUT library
    glutInit(&argc, argv);
    
    // type of window
    glutInitDisplayMode(GLUT_RGBA | GLUT_3_2_CORE_PROFILE);
    
    // don't have to do this here, can query instead
    glutInitWindowSize(512,512);
    
    // type of context; ie. what features
    //	glutInitContextVersion(3,3);
    // only the latest features
    //	glutInitContextProfile(GLUT_CORE_PROFILE);
    // with the display mode specified above
    
    glutCreateWindow(argv[0]);
    
    // helper lib
    if(glewInit()) {
        printf("Unable to initialise GLEW!\n");
        exit(EXIT_FAILURE);
    }
    
    init();
    
    // setup the *display callback*, callbacks also used for user input, window resize etc
    glutDisplayFunc(display);
    
    // infinite loop
    // invokes callbacks handle user input, determine if window needs repainting
    glutMainLoop();
    
}
