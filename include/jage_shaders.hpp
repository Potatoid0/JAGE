#ifndef JAGE_SHADERS_H
#define JAGE_SHADERS_H

//
//  jage_shaders.hpp
//  JAGE
//
//  Created by Benjamin Wulf on 1/14/26.
//

#include "glad/glad.h"
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
    JAGEShader(const char* vertexFile, const char* fragmentFile);
    // use/activate the shader
    void use();
    // utility functions
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
};


#endif
