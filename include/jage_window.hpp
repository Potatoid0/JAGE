#ifndef JAGE_WINDOW_HPP
#define JAGE_WINDOW_HPP

//
//  window.hpp
//  JAGE
//
//  Created by Benjamin Wulf on 1/13/26.
//



#include "glad/glad.h" //needs to be included prior to GLFW
#include "GLFW/glfw3.h"
#include <string>


class JAGEWindow
{
public:
    int width = 800;
    int height = 600;
    float scale = 1.0;
    GLFWwindow* window;
    std::string windowTitle = "Game Window";
    JAGEWindow();
    void processInput();
    void getInput();
    void terminate();
    void resize(int newWidth, int newHeight);
private:
    int realWidth = 0;
    int realHeight = 0;
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

//void processWindowInput(GLFWwindow* window);

#endif
