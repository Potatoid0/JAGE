#ifndef JAGE_INPUT_HPP
#define JAGE_INPUT_HPP

#include "jage_event.hpp"

namespace JAGE
{
    class Input
    {
    private:
        // this might be better as a bit mask(?)
        static inline bool s_KeyStates[512] = { false };
        
    public:
        
        static void UpdateKeyState(int key, bool isPressed) { s_KeyStates[key] = isPressed; }
        static bool IsKeyPressed(int key) { return s_KeyStates[key]; }
        static void OnEvent(Event& e);

        
    };
}





#endif
