//
//  jage_input.cpp
//  JAGE
//
//  Created by Benjamin Wulf on 6/15/26.
//

#include "jage_input.hpp"
#include <iostream>
void JAGE::Input::OnEvent(Event& e)
{
    if(e.GetType() == EventType::KeyPress)
    {
        auto& keyEvent = static_cast<KeyPressEvent&>(e);
        UpdateKeyState(keyEvent.GetKey(), true);
    }
}
