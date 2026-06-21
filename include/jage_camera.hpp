#ifndef JAGE_CAMERA_HPP
#define JAGE_CAMERA_HPP

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace JAGE
{
    class Camera
    {
    public:
        Camera();
        void Initialize();
        float m_Speed = 0.1f;
    //private:
        void Forward();
        glm::vec3 m_Position;// = glm::vec3(0.0f, 0.0f, 3.0f);
        glm::vec3 m_Front;// = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 m_Target;// = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 m_Direction;
        glm::vec3 m_ZUp; // world Z value up
        glm::vec3 m_Right;
        glm::vec3 m_Up; // Camera Up
        //glm::mat4 m_Model;
        glm::mat4 m_View;
        glm::mat4 m_Projection;
        
        glm::mat4 GetModel() { return m_Model; }
        
    private:
        glm::mat4 m_Model;
        
        
    };
}



#endif
