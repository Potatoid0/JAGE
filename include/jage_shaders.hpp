#ifndef JAGE_SHADERS_HPP
#define JAGE_SHADERS_HPP

//
//  jage_shaders.hpp
//  JAGE
//
//  Created by Benjamin Wulf on 1/14/26.
//

#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class JAGEShader
{
public:
    // the program ID
    unsigned int ID;
    
    // Constructor
    JAGEShader(const char* vertexPath, const char* fragmentPath);
    // use/activate the shader
    void use();
    // utility functions
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setMat4(const std::string &name, glm::mat4 value) const;
};


#endif
