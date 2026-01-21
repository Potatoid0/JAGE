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
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
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
    
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    
    
    unsigned int squareIndices[] =
    {
      0, 1, 2,
      0, 2, 3
    };
    
    // Automatically creates a default 800 x 600 game window
    int screenWidth = 1920;
    int screenHeight = 1200;
    JAGEWindow gameWindow;
    gameWindow.resize(screenWidth, screenHeight);
    
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
    
    unsigned int cubeVAO, cubeVBO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &cubeVBO);
    glBindVertexArray(cubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(2);
    
    
    
    newShader.setFloat("opacity", gameWindow.tempOpac);
    
    // ===== Adding 3D elements =====
    glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);                      // create vector of 1,0,0
    glm::mat4 trans = glm::mat4(1.0f);                          // create identity matrix prior to transformations
    trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f)); // apply desired translation to identity matrix
    vec = trans * vec;                                          // apply the new translation matrix to vector
    std::cout << vec.x << vec.y << vec.z << std::endl;          // output new vector
    // Saving above for reference for now
    
    // Modifying existing code, scaling and rotating the existing square
    // scale -> rotate -> translate, but we need to translate, rotate, scale because of.. multiplication.. or something
    //newTrans = glm::scale(newTrans, glm::vec3(0.5, 0.5, 0.5));                          // scale by 0.5x
    //newTrans = glm::rotate(newTrans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));    // rotate 90 degrees on Z-axis
    
    // Need to give this transformation data to the shader via uniform
    //unsigned int transUniLoc = glGetUniformLocation(newShader.ID, "transform");
    //glUniformMatrix4fv(transUniLoc, 1, GL_FALSE, glm::value_ptr(newTrans));
    
    // How orthographic projection is created in GLM
    //glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f);
    
    // How a perspective projection is created in GLM
    //glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)width/(float)height, 0.1f, 100.0f);
    
    // Actual 3D stuff now:
    glm::mat4 model = glm::mat4(1.0f);
    //model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    
    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    
    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(45.0f), (float)screenWidth/(float)screenHeight, 0.1f, 100.0f);
    
    unsigned int modelLoc, viewLoc, projectionLoc;
    modelLoc = glGetUniformLocation(newShader.ID, "model");
    viewLoc = glGetUniformLocation(newShader.ID, "view");
    projectionLoc = glGetUniformLocation(newShader.ID, "projection");
    
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));


    // Issues with clipping, need to enable depth testing
    glEnable(GL_DEPTH_TEST);
    
    
    while(!glfwWindowShouldClose(gameWindow.window))
    {
        
       // processWindowInput(window);
        gameWindow.processInput();
        newShader.setFloat("opacity", gameWindow.tempOpac);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // include depth buffer bit so it doesn't include previous frames
        
        // Update transform matrix
        //glm::mat4 newTrans = glm::mat4(1.0f);   // create identity matrix
        //newTrans = glm::translate(newTrans, glm::vec3(0.5, -0.5, 0.0));
        //newTrans = glm::rotate(newTrans, (float)glfwGetTime(), glm::vec3(0.0, 0.0, 1.0));
        //newTrans = glm::scale(newTrans, glm::vec3(0.5, 0.5, 0.0));
        //glUniformMatrix4fv(transUniLoc, 1, GL_FALSE, glm::value_ptr(newTrans));

        model = glm::rotate(model, glm::radians(0.5f), glm::vec3(0.5f, 1.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        newShader.use();
        
        // Draw square via EBO
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textures[0]);
        
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, textures[1]);
        
        glBindVertexArray(cubeVAO);
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glDrawArrays(GL_TRIANGLES, 0, 36);
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
