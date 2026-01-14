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

// GLSL Vertex and Fragment Shaders, for now just stored as C style strings

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "out vec4 vertexColor;\n"
    "void main()\n"
    "{\n"
    "gl_Position = vec4(aPos, 1.0);\n"
    "vertexColor = vec4(0.5, 0.0, 0.0, 1.0);\n"
    "}\0";

const char *vertexShaderSource2 = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aColor;\n"
    "out vec3 ourColor;\n"
    "void main()\n"
    "{\n"
    "gl_Position = vec4(aPos, 1.0);\n"
    "ourColor = aColor;\n"
    "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "in vec4 vertexColor;\n"
    "void main()\n"
    "{\n"
    "FragColor = vertexColor;\n"
    "}\0";

const char *fragmentShaderSource2 = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "in vec3 ourColor;\n"
    "void main()\n"
    "{\n"
    "FragColor = vec4(ourColor, 1.0);\n"
    "}\0";

int main(int argc, const char * argv[]) {


    
    char infoLog[512];
    int width, height, realWidth, realHeight;
    width = 800;
    height = 600;
    
    // @TODO: Move GLFW Window creation to window.cpp
    // Create a GLFW window
    glfwInit();
    // Set the GLFW window to use OpenGL 3.3 with core profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // Needed only for macOS
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    GLFWwindow* window = glfwCreateWindow(width, height, "Learn OpenGL Tutorial", NULL, NULL);

    if(!window)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    
    glfwMakeContextCurrent(window);
    
    // Need to setup glad for OS-specific function pointers for OpenGL
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    // Next need to tell OpenGL the size of the rendering window
    //Rendering window has issues with macOS DPI scaling, fixing by using glfwGetFrameBufferSize, rather than directly telling OpenGL to use 800 x 600
    glfwGetFramebufferSize(window, &realWidth, &realHeight);
    glViewport(0, 0, realWidth, realHeight);
    
    // Used for resizing the window
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    // Create two triangles
    float verticesLeftTri[] =
    {
       -0.5f,  0.5f, 0.0f,
       -1.0f, -0.5f, 0.0f,
        0.0f, -0.5f, 0.0f
    };
    
    float verticesRightTri[] =
    {
        0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f
    };
    
    // ===== Creating the Shaders =====
    // Vertex Shader:
    
    int success;
    unsigned int vertexShader, vertexShader2;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    
    // Check if the compilation was successful
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cerr << "ERROR: Vertex Shader failed to compile:\n" << infoLog << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    vertexShader2 = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader2, 1, &vertexShaderSource2, NULL);
    glCompileShader(vertexShader2);
    glGetShaderiv(vertexShader2, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertexShader2, 512, NULL, infoLog);
        std::cerr << "ERROR: Vertex Shader failed to compile:\n" << infoLog << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    
    // Fragment Shader:
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cerr << "ERROR: Fragment Shader failed to compile:\n" << infoLog << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    
    // Fragment Shader 2:
    unsigned int fragmentShader2;
    fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader2, 1, &fragmentShaderSource2, NULL);
    glCompileShader(fragmentShader2);
    glGetShaderiv(fragmentShader2, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragmentShader2, 512, NULL, infoLog);
        std::cerr << "ERROR: Fragment Shader failed to compile:\n" << infoLog << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    
    // Shader Program:
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cerr << "ERROR: Failed to link shader program:\n" << infoLog << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    
    // Shader Program 2:
    unsigned int shaderProgram2;
    shaderProgram2 = glCreateProgram();
    glAttachShader(shaderProgram2, vertexShader2);
    glAttachShader(shaderProgram2, fragmentShader2);
    glLinkProgram(shaderProgram2);
    glGetProgramiv(shaderProgram2, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(shaderProgram2, 512, NULL, infoLog);
        std::cerr << "ERROR: Failed to link shader program:\n" << infoLog << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    // We no longer need the individual shader data now that it's linked to the program, deallocate
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteShader(vertexShader2);
    glDeleteShader(vertexShader2);
    
    // ===== Create Vertex Array Objects and Buffer Objects =====
    // Generate VBO and VAOs
    unsigned int VAOs[2], VBOs[2];
    glGenVertexArrays(2, VAOs);
    glGenBuffers(2, VBOs);
    
    // First triangle:
    glBindVertexArray(VAOs[0]); //index 0, aka first triangle
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]); //index 0, aka first triangle
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesLeftTri), verticesLeftTri, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // Second Triangle:
    glBindVertexArray(VAOs[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesRightTri), verticesRightTri, GL_STATIC_DRAW);
    //first param is offset which we only set to 0 because it's tightly packed, therefore OpenGL can figure it out
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
  
    // Optionally set wireframe mode
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    // Fragment Shader Uniform Variables
    float greenValue;
    int vertexColorLocation = glGetUniformLocation(shaderProgram2, "myColor");
    
    while(!glfwWindowShouldClose(window))
    {
        
        processWindowInput(window);
        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glUseProgram(shaderProgram);
        
        glBindVertexArray(VAOs[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Use second shader program to change color of the second triangle
        glUseProgram(shaderProgram2);
        
        // ===== Fragment Shader Uniform Updating =====
        greenValue = (sin(glfwGetTime()) / 2.0f) + 0.5f;
        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
        
        glBindVertexArray(VAOs[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glBindVertexArray(0);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    // Cleanly shut down
    // @TODO: Move all shutdown/terminate to a dedicated function
    glDeleteVertexArrays(2, VAOs);
    glDeleteBuffers(2, VBOs);
    glDeleteProgram(shaderProgram);
    glfwTerminate();
    
    return EXIT_SUCCESS;
}
