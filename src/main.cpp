//
//  main.cpp
//  JAGE
//
//  Created by Benjamin Wulf on 1/13/26.
//
#include "glad/glad.h" //needs to be included prior to GLFW
#include "GLFW/glfw3.h"
#include "jage_window.hpp"
#include "jage_shaders.hpp"
#include <iostream>

int main(int argc, const char * argv[]) {


    
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
    // Rendering window has issues with macOS DPI scaling, fixing by using glfwGetFrameBufferSize, rather than directly telling OpenGL to use 800 x 600
    glfwGetFramebufferSize(window, &realWidth, &realHeight);
    glViewport(0, 0, realWidth, realHeight);
    
    // Used for resizing the window
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    // Create two triangles
    float verticesLeftTri[] =
    {
       -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
       -1.0f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f
    };
    
    float verticesRightTri[] =
    {
        0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f
    };
    
    // TESTING NEW SHADER CLASS
    JAGEShader newShader("/Users/ben/Dev/JAGE/shaders/default.vs", "/Users/ben/Dev/JAGE/shaders/default.fs");
    newShader.use();
    
    // ===== Create Vertex Array Objects and Buffer Objects =====
    // Generate VBO and VAOs
    unsigned int VAOs[2], VBOs[2];
    glGenVertexArrays(2, VAOs);
    glGenBuffers(2, VBOs);
    
    // First triangle:
    glBindVertexArray(VAOs[0]); //index 0, aka first triangle
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]); //index 0, aka first triangle
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesLeftTri), verticesLeftTri, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
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
    //float greenValue;
    //int vertexColorLocation = glGetUniformLocation(shaderProgram2, "myColor");
    
    while(!glfwWindowShouldClose(window))
    {
        
        processWindowInput(window);
        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        newShader.use();
        
        glBindVertexArray(VAOs[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        // ===== Fragment Shader Uniform Updating =====
        //greenValue = (sin(glfwGetTime()) / 2.0f) + 0.5f;
        //glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
        
        //glBindVertexArray(VAOs[1]);
        //glDrawArrays(GL_TRIANGLES, 0, 3);

        glBindVertexArray(0);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    // Cleanly shut down
    // @TODO: Move all shutdown/terminate to a dedicated function
    glDeleteVertexArrays(2, VAOs);
    glDeleteBuffers(2, VBOs);
    //glDeleteProgram(shaderProgram);
    glfwTerminate();
    
    return EXIT_SUCCESS;
}
