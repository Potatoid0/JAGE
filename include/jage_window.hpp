#ifndef JAGE_WINDOW_H
#define JAGE_WINDOW_H

//
//  window.hpp
//  JAGE
//
//  Created by Benjamin Wulf on 1/13/26.
//



#include "glad/glad.h" //needs to be included prior to GLFW
#include "GLFW/glfw3.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void processWindowInput(GLFWwindow* window);

#endif
