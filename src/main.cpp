//
//  main.cpp
//  JAGE
//
//  Created by Benjamin Wulf on 1/13/26.
//
#include "glad/glad.h" //needs to be included prior to GLFW
#include "GLFW/glfw3.h"
#include "window.hpp"
#include <iostream>

// Unsure where exactly to put this, but need to create a GLSL vertex shader
// for some reason it's just stored in a C style string tho
const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";

int main(int argc, const char * argv[]) {


// Create a GLFW window, this should probably move to it's own function (or even file) eventually
    glfwInit();
    // Set the GLFW window to use OpenGL 3.3 with core profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    // Needed only for macOS
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    // Creating a Window Object
    GLFWwindow* window = glfwCreateWindow(800, 600, "Learn OpenGL Tutorial", NULL, NULL);

    if(!window)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    
    // If reaching here, successfully made a window, so set it to main context on current thread
    glfwMakeContextCurrent(window);
    
    // Need to setup glad for OS-specific function pointers for OpenGL
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    // Next need to tell OpenGL the size of the rendering window
    //glViewport(0, 0, 800, 600);
    //Rendering window seems to have issues with macOS DPI scaling, attempting a fix
    int realWidth, realHeight;
    glfwGetFramebufferSize(window, &realWidth, &realHeight);
    glViewport(0, 0, realWidth, realHeight);
    // worked, I'm the best
    
    
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    // Create the vertices of a triangle, stored within a float array
    // I moved it up to the corner to make room for a square
    float vertices[] =
    {
        // First triangle
       -0.5f,  0.5f, 0.0f,
       -1.0f, -0.5f, 0.0f,
        0.0f, -0.5f, 0.0f,
        //Second triangle
        0.5f, 0.5f, 0.0f,
        0.0f, -0.5f, 0.0f,
        1.0f, -0.5f, 0.0f
    };
    
    // OpenGL also has Element Buffer Objects, which are used to store vertex data without overlapping points
    // but then specifying the order to draw them
    // example given is a square would have two overlapping points when drawing two triangles
    
    
    float vertices2[] =
    {
      // Triangle 1
      0.75f,  0.0f,  0.0f, // top right
      0.75f, -0.75f, 0.0f, // bottom right
      0.25f, -0.75f, 0.0f, // bottom left
      // Triangle 2 only needs top left connecting point
      0.25f, 0.0f, 0.0f
    };
     
    // EBO needs to be told which points make up the triangles
    unsigned int indices[] =
    {
      0, 1, 2,
      0, 2, 3
    };
    
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    
    // Make a [V]ertex [B]uffer [O]bject to store data that will be sent to the GPU
    unsigned int VBO;
    glGenBuffers(1, &VBO); // assign this buffer a unique ID (1), and the address of the VBO we created
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // Buffer Data allows us to copy user supplied data to the specified buffer
    // fourth param has three options:
    // GL_STREAM_DRAW is for data set once, and used only a few times
    // GL_STATIC_DRAW is for data set once, and used many times
    // GL_DYNAMIC_DRAW is for data changed frequently and used many times
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    // As of this point, a theoretical triangle exists within the vertex buffer object, and is passed to the GPU
    // needs a vertex shader and fragment shader to process the data.
    
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // &vertexShaderSource refers to the address of the string stored at the top of this program
    // so that it can be compiled at runtime
    // I assume in normal applications you create a function to locate, parse, and load the shader
    // then pass to compile
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    
    // Check if the compilation was successful
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    
    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cerr << "ERROR: Vertex Shader failed to compile:\n" << infoLog << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    
    // Next up, the fragment shader, which is primarily used to determine color output of specific pixels
    // similar process as the vertex shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // since we're here, reusing the success and infolog should be fine I think, but reset success(?)
    success = NULL;
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cerr << "ERROR: Fragment Shader failed to compile:\n" << infoLog << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    
    // next step before drawing is to create a shader program object
    // which is a linked version of multiple shaders combined
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    
    // Similarly to the shaders, we can check to see if the shader program linking was successful
    success = NULL;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cerr << "ERROR: Failed to link shader program:\n" << infoLog << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    // activate it by using the following
    //glUseProgram(shaderProgram); moved to render looo
    // every single rendering call after this point will use this shader program
    
    // We no longer need the individual shader data now that it's linked to the program
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    // Final step before drawing is to tell OpenGL how to interpret the vertex data
    // because vertex shader data can be any input
    // our vertex data is very simply xyz, xyz, xyz for vertex 1, 2, and 3 (all of which are floats)
    // first value is beginning of buffer, and the values are tightly packed
    
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    //glEnableVertexAttribArray(0);
    
    // Create a Vertex Array Object
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    //for square, this part is added
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    

    
    // set wireframe mode?
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    
    // Tell the window to actually remain open
    while(!glfwWindowShouldClose(window))
    {
        
        processWindowInput(window);
        
        // all rendering commands go here
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); //sets a default background color
        glClear(GL_COLOR_BUFFER_BIT); // draws background color to window
        
        glUseProgram(shaderProgram);
        
        glBindVertexArray(VAO);
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
        glDrawArrays(GL_TRIANGLES, 0, 6);
        
        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        
        glBindVertexArray(0);

        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    // Cleanly shut down GLFW
    // @TODO: Move all shutdown/terminate to a dedicated function
    glfwTerminate();
    return EXIT_SUCCESS;
}
