#include <stdio.h>
#include <glad/glad.h>
#include "engine/shader.h"
#include "engine/texture.h"
#include "engine/camera.h"
#include "engine/window.h"
#include <GLFW/glfw3.h>
#include <stdbool.h>
#include <cglm/cglm.h>
#include <cglm/cam.h>


Window window = {0};
Camera camera = {0};


float currentFrame = 0.0f;
float lastFrame = 0.0f;
static float deltaTime;
int lastPosX;
int lastPosY;
bool isfirstMouse = true;

void mouse_callback(GLFWwindow* window, double xpos, double ypos){
    if (isfirstMouse) {
        lastPosX = xpos;
        lastPosY = ypos;
        isfirstMouse = false;
    }
    float x_offset = xpos - lastPosX;
    float y_offset = lastPosY - ypos;
    lastPosX = xpos;
    lastPosY = ypos;


    camera_process_mouse(&camera, x_offset, y_offset, deltaTime, true);
}

void processInput(GLFWwindow* window){
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true); } 
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) camera_process_keyboard(&camera, CAMERA_FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) camera_process_keyboard(&camera, CAMERA_BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) camera_process_keyboard(&camera, CAMERA_LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) camera_process_keyboard(&camera, CAMERA_RIGHT, deltaTime);

    float x_offset = 0.0f;
    float y_offset = 0.0f;

    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        x_offset = 1.0f;  
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        x_offset = -1.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        y_offset = 1.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        y_offset = -1.0f;
    }

    if (x_offset != 0.0f || y_offset != 0.0f) {
        camera_process_mouse(&camera, x_offset, y_offset, deltaTime, true);
    }

    
}


int main() {
    if(!create_window_fullscreen(&window, "Loom")){
        window_destroy(&window);
        return -1;
    }


    Shader shader = {0};
    int success = create_shader(&shader, "assets/shaders/basic.vert", "assets/shaders/basic.frag");
    if(!success){
        window_destroy(&window);
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
        {0.0f,  0.0f,  0.0f},
        {2.0f,  5.0f, -15.0f},
        {-1.5f, -2.2f, -2.5f},
        {-3.8f, -2.0f, -12.3f},
        {2.4f, -0.4f, -3.5f},
        {-1.7f,  3.0f, -7.5f},
        {1.3f, -2.0f, -2.5f},
        {1.5f,  2.0f, -2.5f},
        {1.5f,  0.2f, -1.5f},
        {-1.3f,  1.0f, -1.5f}
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


    Texture woodTex = {0};
    Texture imgTex = {0};
    if(!create_texture(&woodTex, "assets/textures/wood.jpg") || !create_texture(&imgTex, "assets/textures/test.png")){
        window_destroy(&window);
        return -1;
    }
        

    use_shader(&shader);
    set_uniform_int(&shader, "u_texture1", 0);
    set_uniform_int(&shader, "u_texture2", 1);


    window_lock_cursor(&window);
    window_set_cursor_callback(&window,mouse_callback);

    init_camera(&camera, (vec3){0.0f, 0.0f, 3.0f});
    camera_set_sensitivity(&camera, 1.25f);


    while (!window_should_close(&window)) {


        currentFrame = (float)glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        



        processInput(window.handle);

        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        use_shader(&shader);
        set_uniform_float(&shader, "u_time", glfwGetTime());


        
        

        mat4 view;
        camera_get_view_matrix(&camera, view);

        mat4 projection;
        float aspect_ratio = window_aspect_ratio(&window);
        glm_perspective(glm_rad(45.0f), aspect_ratio, 0.1f, 100.0f, projection);

        set_uniform_mat(&shader, "view", view);
        set_uniform_mat(&shader, "projection", projection);

    
        bind_texture(&woodTex, 0);
        bind_texture(&imgTex, 1);

        glBindVertexArray(VAO);
        for(unsigned int i = 0; i < sizeof(cubePositions)/sizeof(vec3); i++){
            mat4 model;
            glm_mat4_identity(model);
            glm_translate(model, cubePositions[i]);
            // glm_rotate(model, glfwGetTime() * glm_rad(50.0f), (vec3){0.5f, 1.0f, 0.0f});
            glm_scale_uni(model, 0.5f);
            set_uniform_mat(&shader, "model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        


        window_swap_and_poll(&window);

    }



    delete_texture(&woodTex);
    delete_texture(&imgTex);
    delete_shader(&shader);
    window_destroy(&window);
    return 0;
}
