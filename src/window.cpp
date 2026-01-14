//
//  window.cpp
//  JAGE
//
//  Created by Benjamin Wulf on 1/13/26.
//

#include "glad/glad.h" //needs to be included prior to GLFW
#include "GLFW/glfw3.h"
#include <iostream>
#include "window.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processWindowInput(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}
