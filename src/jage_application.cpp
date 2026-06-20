#include "jage_application.hpp"
#include <iostream>

namespace JAGE
{
    Application::Application()
    {
        
        std::cout << "INFO: Attempting to create JAGE::Application" << std::endl;
        
        s_Instance = this;
    
        m_Window = std::make_unique<Window>();
        
        m_Window->Initialize(960, 540, "JAGE");
        m_Window->SetEventCallback([this](Event& e) {this->OnEvent(e);} );
        
    }
    
void Application::OnInitialize()
{
    //m_Window->Initialize();
    
    //m_Window->SetEventCallback([this](Event& e) {OnEvent(e); } );
}
    Application::~Application()
    {
        s_Instance = nullptr;
    }

    void Application::OnEvent(Event& e)
    {
        // Handle Core Engine Events
        if(e.GetType() == EventType::WindowClose)
        {
            m_Running = false;
            return;
        }
        // Pass to input manager
        Input::OnEvent(e);
    }

    void Application::Run()
    {
        OnInitialize();
        
        float tempDeltaTime = 0.016f;
        
        while(m_Running)
        {
            // Full Engine loop goes here
            //
            //std::cout << "INFO: Entering Core Loop" << std::endl;
            m_Window->PollEvents();
            if(!m_Running) { break; }
            
            OnUpdate(tempDeltaTime);
            
            m_Renderer->Draw(); // I don't know if this is the right spot for this
            
            m_Window->SwapBuffers();
            
        }
        
        OnShutdown();
    }
}






