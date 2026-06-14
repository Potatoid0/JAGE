#ifndef JAGE_WINDOW_HPP
#define JAGE_WINDOW_HPP

//
//  window.hpp
//  JAGE
//
//  Created by Benjamin Wulf on 1/13/26.
//



//#include "glad/glad.h" //needs to be included prior to GLFW
#include "GLFW/glfw3.h"
#include <string>


class JAGEWindow
{
private:
    int width = 1920;
    int height = 1080;
    float scale = 1.0;
    std::string windowTitle = "Game Window";
    
public:
    //int realWidth = 0;
    //int realHeight = 0;
    float tempOpac = 0.0;
    GLFWwindow* window;
    JAGEWindow();
    void processInput();
    void getInput();
    void terminate();
    void resize(int newWidth, int newHeight);
    int getHeight();
    int getWidth();
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

//void processWindowInput(GLFWwindow* window);

#endif
