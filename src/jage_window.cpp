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

namespace JAGE
{
    Window::Window()
    {
        std::cout << "INFO: Attempting to create game window" << std::endl;
        
        // Initial glfw initialization
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        
        // macOS-specific flag(?)
#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
        
        window = glfwCreateWindow(width, height, title, NULL, NULL);
        
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
            std::cerr << "ERROR: Failed to initialize GLAD" << std::endl;
        }
        
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);
        
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    }

}

/*
 * @brief Creates a GLFW-based JAGEWindow object
 * @note Defaults screen size to 960x540
 * @note Currently has an issue with mac dpi scaling with window size
 */
/*
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
        std::cerr << "JAGEERROR: Failed to create main game window" << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    
    glfwMakeContextCurrent(window);
    
    // Initialize GLAD for OS-specific function pointers
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "JAGEERROR: Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    
    // roundabout way of setting window size OpenGL is able to draw to due to macOS dpi scaling issues
    
    //This is a messy way of doing this but
    int realWidth, realHeight;
    glfwGetFramebufferSize(window, &realWidth, &realHeight);
    //scale = (float)width / (float)realWidth;
    //std::cout << "scale: " << scale << std::endl;
    //width = (int)(width * scale);
    //height = (int)(height * scale);
    //glfwSetWindowSize(window, width, height);
    //glfwGetFramebufferSize(window, &realWidth, &realHeight);
    glViewport(0, 0, realWidth, realHeight);
    
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
}
*/
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
/*
void JAGEWindow::processInput()
{
    //const float cameraSpeed = 0.05f;
    
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    
    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS && tempOpac < 1.0)
    {
        tempOpac += 0.01;
    }
    
    if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS && tempOpac > 0.0)
    {
        tempOpac -= 0.01;
        
    }
}
*/
/*
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
    // breaking the resize function while I figure out mac dpi scaling
    
    //width = (int)(newWidth * scale);
    //height = (int)(newHeight * scale);
    width = newWidth;
    height = newHeight;
    glfwSetWindowSize(window, width, height);
    //glfwGetFramebufferSize(window, width, height);
    
    //std::cout << "Requested Width: " << newWidth << ", Requested Height: " << newHeight << std::endl;
    //std::cout << "Window Width: " << width << ", Window Height: " << height << std::endl;
    //std::cout << "Real Width: " << realWidth << ", Real Height: " << realHeight << std::endl;

    glViewport(0, 0, width, height);
}
 */
/*
int JAGEWindow::getHeight()
{
    return height;
}

int JAGEWindow::getWidth()
{
    return width;
}
*/
