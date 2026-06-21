#ifndef JAGE_APPLICATION_HPP
#define JAGE_APPLICATION_HPP

//#include "jage_input.hpp"
#include "jage_window.hpp"
//#include "jage_event.hpp"
//#include "jage_renderer.hpp"

namespace JAGE
{
    class Application
    {
    private:
        std::unique_ptr<Window> m_Window;
        std::unique_ptr<Renderer> m_Renderer;
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
        Renderer& GetRenderer() { return *m_Renderer; }
        void Close() { m_Running = false; }
        void MoveCamera();
        
    };

    Application* CreateApplication();

}


#endif
