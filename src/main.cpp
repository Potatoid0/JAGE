//
//  main.cpp
//  JAGE
//
//  Created by Benjamin Wulf on 1/13/26.
//
#include "glad/glad.h" //needs to be included prior to GLFW
#include "GLFW/glfw3.h"
#include "jage_window.hpp"
#include "jage_shaders.hpp"
#include "stb_image/stb_image.h"
#include <iostream>

int main(int argc, const char * argv[]) {
    
    // Creating a square for texture work
    float squareVertices[] =
    {
        //X      Y     Z       R     G     B       Tx    Ty
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   2.0f, 2.0f, // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   2.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 2.0f  // top left
    };
    
    unsigned int squareIndices[] =
    {
      0, 1, 2,
      0, 2, 3
    };
    
    // Automatically creates a default 800 x 600 game window
    JAGEWindow gameWindow;
    gameWindow.resize(1920, 1200);
    
    JAGEShader newShader("/Users/ben/Dev/JAGE/shaders/default.vs", "/Users/ben/Dev/JAGE/shaders/default.fs");
    newShader.use();
    
    // ===== Adding in textures via stb_image =====
    stbi_set_flip_vertically_on_load(true); // otherwise textures load upside down
    int imgWidth, imgHeight, nrChannels;
    unsigned char *data = stbi_load("/Users/ben/Dev/JAGE/images/container.jpg", &imgWidth, &imgHeight, &nrChannels,     0);
    unsigned int textures[2];
    glGenTextures(2, textures);
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    if(data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cerr << "ERROR: Failed to load first texture" << std::endl;
    }
    stbi_image_free(data);
    data = stbi_load("/Users/ben/Dev/JAGE/images/awesomeface.png", &imgWidth, &imgHeight, &nrChannels, 0);
    glBindTexture(GL_TEXTURE_2D, textures[1]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    if(data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgWidth, imgHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cerr << "ERROR: Failed to load second texture" << std::endl;
    }
    stbi_image_free(data);
    
    newShader.setInt("ourTexture", 0);
    newShader.setInt("secondTexture", 1);
    
    // ===== Create Element Array Object for square instead of triangle
    unsigned int EBO, VAO, VBO;
    //generate
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    //bind
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //Give data
    glBufferData(GL_ARRAY_BUFFER, sizeof(squareVertices), squareVertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(squareIndices), squareIndices, GL_STATIC_DRAW);
    //Tell how VAO works
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    
    newShader.setFloat("opacity", gameWindow.tempOpac);
    
    while(!glfwWindowShouldClose(gameWindow.window))
    {
        
       // processWindowInput(window);
        gameWindow.processInput();
        newShader.setFloat("opacity", gameWindow.tempOpac);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        newShader.use();
        
        // Draw square via EBO
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textures[0]);
        
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, textures[1]);
        
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
        glBindVertexArray(0);
                
        glfwSwapBuffers(gameWindow.window);

        gameWindow.getInput();
    }
    
    // Cleanly shut down
    // @TODO: Move all shutdown/terminate to a dedicated function
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    gameWindow.terminate();
    
    return EXIT_SUCCESS;
}
