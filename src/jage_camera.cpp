#include "jage_camera.hpp"
#include <iostream>
namespace JAGE
{
Camera::Camera()
{
    std::cout << "Constructing Camera" << std::endl;
   
    
    //newShader.setMat4("model", model);
    //newShader.setMat4("view", view);
    //newShader.setMat4("projection", projection);
    
    
}
void Camera::Initialize()
{
    std::cout << "INFO: Initializing Camera(?)" << std::endl;
    m_Position = glm::vec3(0.0f, 0.0f, 3.0f);

    m_Front = glm::vec3(0.0f, 0.0f, -1.0f);
    m_Target = glm::vec3(0.0f, 0.0f, 0.0f);
    
    m_Direction = glm::normalize(m_Position - m_Target); //subtracting origin from current position results in the desired direction
    m_ZUp = glm::vec3(0.0f, 1.0f, 0.0f);
    m_Right = glm::normalize(glm::cross(m_ZUp, m_Direction)); //dot product between up and target direction gives perpendicular to both, resulting in the positive x axis
    m_Up = glm::cross(m_Direction, m_Right);
    
    m_Model = glm::mat4(1.0f);
        //model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        
    m_View = glm::lookAt(m_Position, m_Target, m_ZUp); // same as previously entered
    //glm::mat4 view = glm::lookAt(m_Camera->m_Position, m_Camera->m_Target, m_Camera->m_ZUp);
    m_Projection = glm::mat4(1.0f);
    m_Projection = glm::perspective(glm::radians(45.0f), 960.0f/540.0f, 0.1f, 100.0f);
}
void Camera::Forward()
{
    //cameraPos.x += cameraSpeed * cameraFront.x;
    //cameraPos.z += cameraSpeed * cameraFront.z;
    //std::cout << "aaa" << std::endl;

    m_Position.x += m_Speed * m_Front.x;
    m_Position.z += m_Speed * m_Front.z;
    
    m_View = glm::lookAt(m_Position, m_Position + m_Front, m_Up);
    
}
}
