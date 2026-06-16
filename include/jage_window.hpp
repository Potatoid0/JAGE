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
//#include <string>
//#include "jage_core.hpp"
#include <functional>
#include "jage_event.hpp"


namespace JAGE
{
    class Window
    {
    
    public:
        using EventCallbackFn = std::function<void(Event&)>;
        void SetEventCallback(const EventCallbackFn& callback) { m_Callback = callback; }
        GLFWwindow* window;
        //void Initialize();
        //void terminate();
        Window();
        static void getInput() { glfwPollEvents(); }
        uint16_t getHeight() const { return height; }
        uint16_t getWidth() const { return width; }
        
    private:
        int width = 960;
        int height = 540;
        const char* title = "JAGE"; // c style string as used by GLFW to save a conversion later
        EventCallbackFn m_Callback;
    };
}
/*
class JAGEWindow
{
private:
    int width = 960;
    int height = 540;
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
    uint16_t getHeight() const { return height; }
    uint16_t getWidth() const { return width; }
    
    //int getHeight();
    //int getWidth();
    
};
*/
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

//void processWindowInput(GLFWwindow* window);

#endif
