#include <stdio.h>
#include <glad/glad.h>
#include "cglm/affine.h"
#include "cglm/affine2d-post.h"
#include "utils/util.h"
#include "engine/shader.h"
#include <GLFW/glfw3.h>
#include <stdbool.h>
#include <cglm/cglm.h>
#include <cglm/cam.h>


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
    glEnable(GL_DEPTH_TEST);


    Shader shader = {0};
    int success = create_shader(&shader, "assets/shaders/basic.vert", "assets/shaders/basic.frag");
    if(!success){
        glfwTerminate();
        return -1;
    }


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
    
    vec3 cubePositions[] = {
        {  0.0f,   0.0f,   0.0f }, // Center
        {  2.3f,   1.5f,  -4.5f },
        { -3.1f,  -2.2f,  -7.0f },
        {  1.5f,  -3.4f, -12.5f },
        { -2.8f,   3.1f,  -5.2f },
        {  3.9f,  -1.0f,  -9.8f },
        { -1.2f,   2.7f, -14.1f },
        {  2.7f,   3.8f,  -6.3f },
        { -3.5f,  -0.5f, -11.0f },
        {  0.8f,  -2.6f,  -3.5f }
    };

    


    GLuint VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);


    glBindVertexArray(VAO);





    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


    //position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //texture attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);


    GLuint texture = load_texture("assets/textures/wood.jpg");

    use_shader(&shader);
    set_uniform_int(&shader, "u_texture", 0);



    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        use_shader(&shader);
        set_uniform_float(&shader, "u_time", glfwGetTime());

        

        mat4 view;
        glm_mat4_identity(view);
        glm_translate(view, (vec3){0.0f, 0.0f, -3.0f});

        mat4 projection;
        float aspect_ratio = (float)mode->width/(float)mode->height;
        glm_perspective(glm_rad(45.0f), aspect_ratio, 0.1f, 100.0f, projection);

        set_uniform_mat(&shader, "view", view);
        set_uniform_mat(&shader, "projection", projection);

    
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);

        glBindVertexArray(VAO);
        for(unsigned int i = 0; i < sizeof(cubePositions)/sizeof(vec3); i++){
            mat4 model;
            glm_mat4_identity(model);
            glm_translate(model, cubePositions[i]);
            glm_rotate(model, glfwGetTime() * glm_rad(50.0f), (vec3){0.5f, 1.0f, 0.0f});
            glm_scale_uni(model, 0.5f);
            set_uniform_mat(&shader, "model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        


        glfwSwapBuffers(window);
        glfwPollEvents(); 

    }



    delete_shader(&shader);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
