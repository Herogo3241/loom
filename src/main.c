#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdbool.h>
#include "utils/util.h"

void processInput(GLFWwindow* window){
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);

    }
}


int main() {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWmonitor* primary= glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(primary);


    GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, "loom", primary, NULL);
    if (!window){
        perror("Error creating window\n");
        glfwTerminate();
    }

    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        perror("failed to initalize glad");       
    }
    glViewport(0, 0, mode->width, mode->height);

    const char* vertexSource = parseShader("assets/basic.vert");
    const char* fragmentSource = parseShader("assets/basic.frag");

    if (!vertexSource) {
        perror("Could not load vertex shader");
    
    }
    if (!fragmentSource) {
        perror("could not load fragment shader");
    
    }



    GLuint vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);

    int success;
    char info_log[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, info_log);
        printf("Vertex shader error:%s", info_log);

    }
    GLuint fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, info_log);
        printf("Fragment shader error:%s", info_log);

    }

    GLuint shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, info_log);
        printf("Shader Program error: %s", info_log);
    
    }






    float vertices[] = {
        // x,  y,  z
        -0.7f, -0.5f, 0.0f,     0.6f,0.4f,0.6f,
        -0.5f, 0.4f, 0.0f,      0.3f,0.6f,0.2f,
        0.2f, 0.8f, 0.0f,       0.8f,0.1f,0.0f,
        0.5f, -0.3f, 0.0f,      0.2f, 0.9f, 0.3f
    };

    GLuint indices[] = {
        0, 1, 2,
        3, 0, 2
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6* sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);




    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);


        glfwSwapBuffers(window);
        glfwPollEvents(); 

    }



    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
