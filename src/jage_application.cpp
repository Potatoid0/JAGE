#include "jage_application.hpp"

void Application::Initialize()
{
    m_Window->Initialize();
    
    m_Window->SetEventCallback([this](Event& e) {OnEvent(e); } );
}

void Application::OnEvent(Event& e)
{
    JAGE::Input::OnEvent(e);
}
