#ifndef JAGE_WINDOW_HPP
#define JAGE_WINDOW_HPP

//
//  window.hpp
//  JAGE
//
//  Created by Benjamin Wulf on 1/13/26.
//


//#include "glad/glad.h" //needs to be included prior to GLFW
//#include "GLFW/glfw3.h"
//#include "glad/glad.h" //needs to be included prior to GLFW
//#include <string>
//#include "jage_core.hpp"
#include <functional>
//#include "jage_event.hpp"
#include "jage_input.hpp"
#include "jage_renderer.hpp"


namespace JAGE
{
    class Window
    {
    
    public:
        using EventCallbackFn = std::function<void(Event&)>;
        void SetEventCallback(const EventCallbackFn& callback) { m_Callback = callback; }
        void Initialize(int width, int height, const std::string& title);
        //void Initialize();
        //void terminate();
        Window() : m_Window(nullptr), m_Width(0), m_Height(0) {}
        void PollEvents() { glfwPollEvents(); }
        void SwapBuffers() { glfwSwapBuffers(m_Window); }
        int GetHeight() const { return m_Height; }
        int GetWidth() const { return m_Width; }
        
    private:
        int m_Width = 960;
        int m_Height = 540;
        const char* m_Title = "JAGE"; // c style string as used by GLFW to save a conversion later
        EventCallbackFn m_Callback;
        GLFWwindow* m_Window;

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

//void mouse_callback(GLFWwindow* window, double xpos, double ypos);
//void processWindowInput(GLFWwindow* window);

#endif
