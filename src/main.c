#include <stdio.h>
#include <glad/glad.h>
#include "engine/shader.h"
#include <GLFW/glfw3.h>
#include <stdbool.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>


void processInput(GLFWwindow* window){
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);

    }
}


int main() {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    int count;
    GLFWmonitor** monitors = glfwGetMonitors(&count);
    GLFWmonitor* monitor;

    if (count > 1) {
        monitor = monitors[1];
    }else {
        monitor = glfwGetPrimaryMonitor();
    }
    const char* monitor_name = glfwGetMonitorName(monitor);
    printf("Loom running on %s\n", monitor_name);
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    printf("Width: %d, Height: %d\n", mode->width, mode->height);


    GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, "loom", monitor, NULL);
    if (!window){
        perror("Error creating window\n");
        glfwTerminate();
    }

    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        perror("failed to initalize glad");       
    }
    glViewport(0, 0, mode->width, mode->height);


    Shader shader = {0};
    int success = create_shader(&shader, "assets/shaders/basic.vert", "assets/shaders/basic.frag");
    if(!success){
        glfwTerminate();
        return -1;
    }


    float vertices[] = {
        // x,  y,  z
        -0.5f, -0.5f, 0.0f,     0.6f,0.4f,0.6f,     0.0f, 0.0f,
        -0.5f, 0.5f, 0.0f,      0.3f,0.6f,0.2f,     0.0f, 1.0f,
        0.5f, 0.5f, 0.0f,       0.8f,0.1f,0.0f,     1.0f, 1.0f,
        0.5f, -0.5f, 0.0f,      0.2f, 0.9f, 0.3f,    1.0f, 0.0f
    };

    GLuint indices[] = {
        0, 1, 2,
        2, 3, 0
    };



    GLuint VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);


    glBindVertexArray(VAO);





    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8* sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);


    //texture attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(6*sizeof(float)));
    glEnableVertexAttribArray(2);


    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, channels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load("assets/textures/test.png", &width, &height, &channels, 0);
    if (data) {
        GLenum format;
        switch (channels) {
            case 3:
                format = GL_RGB;
                glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
                break;
            case 4:
                format = GL_RGBA;
                break;
        
        }
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data); 
        glGenerateMipmap(GL_TEXTURE_2D);   
    }else{
        perror("Failed to load image");
    }




    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        use_shader(&shader);
        set_uniform_float(&shader, "u_time", glfwGetTime());

    

        glBindTexture(GL_TEXTURE_2D, texture);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);


        glfwSwapBuffers(window);
        glfwPollEvents(); 

    }



    delete_shader(&shader);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
