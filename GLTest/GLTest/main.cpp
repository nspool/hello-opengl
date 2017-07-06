//
// main.cpp
// GLTest by nspool
//

#define GLFW_INCLUDE_GLCOREARB 1

#include <iostream>

#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>

#define BUFFER_OFFSET(x) ((const void*) (x))

enum VAO_IDs { Triangles, NumVAOs };
enum Buffer_IDs { ArrayBuffer, NumBuffers };
enum Attrib_IDs { vPosition = 0 };
GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];
const GLuint NumVertices = 6;

using namespace std;

static const char* vertex_shader_text =
"layout(location = 0) in vec4 vPosition;\n"
"void main()\n"
"{\n"
" gl_Position = vPosition;\n"
"}\n";

static const char* fragment_shader_text =
"out vec4 fColor;\n"
"void main()\n"
"{\n"
" fColor = vec4(0.0, 0.0, 1.0, 1.0);\n"
"}\n";

void
init(void)
{
    GLuint vertex_shader, fragment_shader, program;
    
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
        { 0.85, -0.90 },
        { -0.90, 0.85 },
        { 0.90, -0.85 },
        { 0.90, 0.90 },
        { -0.85, 0.90 }
    };
    
    // create some names for the vertex buffer objects
    glGenBuffers(NumBuffers, Buffers);
    
    // now bring them into existence
    // delete with glDeleteBuffer, check with glIsBuffer
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
    
    // allocate storage for and transfer vertex data into the buffer object
    // we could be reading |vertices| in from a file or dynamically generating them
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
    glCompileShader(vertex_shader);
    
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
    glCompileShader(fragment_shader);
    
    program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);
    
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
    GLFWwindow* window;
    
    // initialise the GLFW library
    if (!glfwInit())
        return -1;
    
    // type of window
    window = glfwCreateWindow(640, 480, "Hello OpenGL", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    
    /* Make the window's context current */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwMakeContextCurrent(window);
    
    init();
    
    // infinite loop
    // invokes callbacks handle user input, determine if window needs repainting
    while (!glfwWindowShouldClose(window))
    {
        glViewport(0, 0, 640, 480);
        
        /* Render here */
        // glClear(GL_COLOR_BUFFER_BIT);
        
        display();
        
        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        
        /* Poll for and process events */
        glfwPollEvents();
    }
    
    glfwTerminate();
    return 0;
}
