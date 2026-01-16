//
//  window.cpp
//  JAGE
//
//  Created by Benjamin Wulf on 1/13/26.
//

#include "glad/glad.h" //needs to be included prior to GLFW
#include "GLFW/glfw3.h"
#include <iostream>
#include "jage_window.hpp"


JAGEWindow::JAGEWindow()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    
    window = glfwCreateWindow(width, height, windowTitle.c_str(), NULL, NULL);
    if(!window)
    {
        std::cerr << "ERROR: Failed to create main game window" << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    
    glfwMakeContextCurrent(window);
    
    // Initialize GLAD for OS-specific function pointers
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    
    // roundabout way of setting window size OpenGL is able to draw to due to macOS dpi scaling issues
    
 
    //This is a messy way of doing this but
    glfwGetFramebufferSize(window, &realWidth, &realHeight);
    scale = (float)width / (float)realWidth;
    width = (int)(width * scale);
    height = (int)(height * scale);
    glfwSetWindowSize(window, width, height);
    glfwGetFramebufferSize(window, &realWidth, &realHeight);
    glViewport(0, 0, realWidth, realHeight);
    
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void JAGEWindow::processInput()
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

void JAGEWindow::getInput()
{
    glfwPollEvents();
}

void JAGEWindow::terminate()
{
    glfwTerminate();
}

void JAGEWindow::resize(int newWidth, int newHeight)
{
    width = (int)(newWidth * scale);
    height = (int)(newHeight * scale);
    glfwSetWindowSize(window, width, height);
    glfwGetFramebufferSize(window, &realWidth, &realHeight);
    
    //std::cout << "Requested Width: " << newWidth << ", Requested Height: " << newHeight << std::endl;
    //std::cout << "Window Width: " << width << ", Window Height: " << height << std::endl;
    //std::cout << "Real Width: " << realWidth << ", Real Height: " << realHeight << std::endl;

    glViewport(0, 0, realWidth, realHeight);
}
