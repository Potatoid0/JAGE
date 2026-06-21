#ifndef JAGE_RENDERER_HPP
#define JAGE_RENDERER_HPP

//#include "glad/glad.h" //needs to be included prior to GLFW
//#include "glm/glm.hpp"
//#include "glm/gtc/matrix_transform.hpp"
//#include "glm/gtc/type_ptr.hpp"
#include "jage_shaders.hpp"
#include "jage_camera.hpp"
namespace JAGE
{
    class Renderer
    {
    public:
      
        Renderer();
        void Initialize();
        void Draw();
        //void SetBackgroundColor(glm::vec4 RGBA) { m_BackgroundColor = RGBA; }
        //glm::vec4 GetBackgroundColor() { return m_BackgroundColor; }
        //std::unique_ptr<Camera> m_Camera;

    //private:
        std::unique_ptr<Camera> m_Camera;
        //glm::vec4 m_BackgroundColor = glm::vec4(0.2f, 0.3f, 0.3f, 1.0f);
    };

}



#endif
