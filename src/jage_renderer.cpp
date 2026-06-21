#include "jage_renderer.hpp"


namespace JAGE
{
    // Constructor
    Renderer::Renderer()
    {
        
    }

    void Renderer::Initialize()
    {
        m_Camera = std::make_unique<Camera>();
        m_Camera->Initialize();
    }
    void Renderer::Draw()
    {
        

        
        // @TODO: Fix this absolute cluster f
        // === Copying from previous version ===
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
        glm::vec3 cubePositions[] =
            {
                glm::vec3(0.0f,  4.0f,  -2.0f),
                glm::vec3(3.0f,  -1.0f,  -7.0f),
                glm::vec3(-4.0f,  2.0f,  -10.0f),
                glm::vec3(1.2f,  -1.0f,  -6.0f),
                glm::vec3(-3.1f,  0.8f,  -10.0f),
                glm::vec3(6.2f,  -1.3f,  -14.0f),
                glm::vec3(0.6f,  2.8f,  -8.0f),
                glm::vec3(-0.9f,  3.0f,  -4.0f),
                glm::vec3(9.3f,  -0.9f,  -2.0f),
                glm::vec3(0.1f,  2.6f,  -8.0f)
            };
        
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
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_REPEAT);
            
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
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_REPEAT);
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
        
        //    newShader.setFloat("opacity", gameWindow.tempOpac); //ignore opacity for now
        
        //glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);     // create vector of 1,0,0
        //glm::mat4 trans = glm::mat4(1.0f);         // create identity matrix prior to transformations
        //trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f)); // apply desired translation to identity matrix
        //vec = trans * vec;                         // apply the new translation matrix to vector
        
        
        
        /*
        glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
        glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget); //subtracting origin from current position results in the desired direction
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
        glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection)); //dot product between up and target direction gives perpendicular to both, resulting in the positive x axis
        glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight); // similar to above
            // This is the Gram-Schmidt process if I want to do some studying up on linear algebra
        
        
        glm::mat4 model = glm::mat4(1.0f);
            //model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            
        glm::mat4 view = glm::lookAt(cameraPos, cameraTarget, up); // same as previously entered
        //glm::mat4 view = glm::lookAt(m_Camera->m_Position, m_Camera->m_Target, m_Camera->m_ZUp);
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(45.0f), 960.0f/540.0f, 0.1f, 100.0f);
        */
        glm::mat4 model = m_Camera->GetModel();
        newShader.setMat4("model", model);
        newShader.setMat4("view", m_Camera->m_View);
        newShader.setMat4("projection", m_Camera->m_Projection);

        // Issues with clipping, need to enable depth testing
        glEnable(GL_DEPTH_TEST);
        newShader.use();
                
                // Draw square via EBO
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, textures[0]);
                
                glActiveTexture(GL_TEXTURE1);
                glBindTexture(GL_TEXTURE_2D, textures[1]);
                
                glBindVertexArray(cubeVAO);
        // Background
        
        /* === Inside actual Loop === */
        glClearColor(0.2f, 0.3f, 0.4f, 1.0f); // 0.2f, 0.3f, 0.3f, 1.0f
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // include depth buffer bit so it doesn't include previous frames
        
        newShader.use();
                
                // Draw square via EBO
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, textures[0]);
                
                glActiveTexture(GL_TEXTURE1);
                glBindTexture(GL_TEXTURE_2D, textures[1]);
                
                glBindVertexArray(cubeVAO);
       
        for(unsigned int i=0; i<10; i++)
                {
                    glm::mat4 model = glm::mat4(1.0f);
                    model = glm::translate(model, cubePositions[i]);
                    float angle = 20.0f * i;
                    model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
                    newShader.setMat4("model", model);
                    glDrawArrays(GL_TRIANGLES, 0, 36);
                    
                }
                //Trying to make a floor
                m_Camera->GetModel() = glm::mat4(1.0f);
        m_Camera->GetModel() = glm::scale(m_Camera->GetModel(), glm::vec3(1000.0f, 1.0f, 1000.0f));
        m_Camera->GetModel() = glm::translate(m_Camera->GetModel(), glm::vec3(0.0f, -1.5f, 0.0f));
                newShader.setMat4("model", m_Camera->GetModel());
                glDrawArrays(GL_TRIANGLES, 0, 36);
                
                //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
                glBindVertexArray(0);
        
        
        //Input to be moved later
        
        // === End copying ===
        
        
        
    }


    
}
