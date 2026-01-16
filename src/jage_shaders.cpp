//
//  jage_shaders.cpp
//  JAGE
//
//  Created by Benjamin Wulf on 1/14/26.
//

#include "jage_shaders.hpp"

JAGEShader::JAGEShader(const char* vertexPath, const char* fragmentPath)
{
    std::string vertexCode, fragmentCode;
    std::ifstream vertexFile, fragmentFile;
    std::stringstream vertexStream, fragmentStream;
    unsigned int vertexShader, fragmentShader;
    int success;
    char infoLog[512];
    
    vertexFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fragmentFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    // First try and retrieve vertex shader file
    try
    {
        vertexFile.open(vertexPath);
        vertexStream << vertexFile.rdbuf();
        vertexFile.close();
        vertexCode = vertexStream.str();
    }
    catch(std::ifstream::failure e)
    {
        std::cerr << "ERROR: Failed to read Vertex Shader File: " << vertexPath << std::endl;
    }
    // Now try and retrieve fragment shader file (probably overkill to do it this way but whatever
    try
    {
        fragmentFile.open(fragmentPath);
        fragmentStream << fragmentFile.rdbuf();
        fragmentFile.close();
        fragmentCode = fragmentStream.str();
    }
    catch(std::ifstream::failure e)
    {
        std::cerr << "ERROR: Failed to read Fragment Shader File: " << fragmentPath << std::endl;
    }
    
    // Successfully retrieved both the vertex and fragment shaders, stored as C strings
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    
    // Compile shaders
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vShaderCode, NULL);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cerr << "ERROR: Failed to compile vertex shader: " << infoLog << std::endl;
    }
    
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cerr << "ERROR: Failed to compile fragment shader: " << infoLog << std::endl;
    }
    
    // Vertex and Fragment shaders both successfully compiled
    // Create shader program
    
    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cerr << "ERROR: Failed to link shader program: " << infoLog << std::endl;
    }
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
}

void JAGEShader::use()
{
    glUseProgram(ID);
}

void JAGEShader::setBool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void JAGEShader::setInt(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void JAGEShader::setFloat(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}
