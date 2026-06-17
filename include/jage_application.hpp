#ifndef JAGE_APPLICATION_HPP
#define JAGE_APPLICATION_HPP

#include "jage_window.hpp"
#include "jage_event.hpp"

namespace JAGE
{
    class Application
    {
    private:
        std::unique_ptr<Window> m_Window;
        bool m_Running = true;
        
        static inline Application* s_Instance = nullptr;
        
    public:
        Application();
        virtual ~Application();
        
        void Run();
        
        void OnEvent(Event& e);
        
        virtual void OnInitialize();
        virtual void OnUpdate(float deltaTime) {}
        virtual void OnShutdown() {}
        
        static Application& GetInstance() { return *s_Instance; }
        Window& GetWindow() { return *m_Window; }
        void Close() { m_Running = false; }
        
        
    };

    Application* CreateApplication();

}


#endif
