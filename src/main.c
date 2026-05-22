#include <glad/glad.h>

#include "engine/shader.h"
#include "engine/texture.h"
#include "engine/camera.h"
#include "engine/window.h"
#include "editor/editor.h"
#include <GLFW/glfw3.h>
#include <stdbool.h>
#include <cglm/cglm.h>
#include <cglm/cam.h>




Window window = {0};
Camera camera = {0};
// Editor editor = {0};


float currentFrame = 0.0f;
float lastFrame = 0.0f;
static float deltaTime;
int lastPosX;
int lastPosY;
bool isfirstMouse = true;

bool editorOpen = false;


void framebuffer_size_callback(GLFWwindow* handle, int width, int height){
    glViewport(0, 0, width, height);
}
void mouse_callback(GLFWwindow* window, double xpos, double ypos){
    if(editorOpen) return;
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

void key_callback(GLFWwindow* handle, int key, int scancode, int action, int mods){
    if (key == GLFW_KEY_TAB && action == GLFW_PRESS) {
       toggle_editor(&editorOpen); 

       if (!editorOpen) {
           window_lock_cursor(&window);
       }else{
           window_unlock_cursor(&window);
           isfirstMouse = true;
       }
    }
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
    if(!create_window(&window, "Loom", 1280, 720)){
        window_destroy(&window);
        return -1;
    }
    

    Shader shader = {0};
    int success = create_shader(&shader, "assets/shaders/basic.vert", "assets/shaders/texture.frag");
    if(!success){
        window_destroy(&window);
        return -1;
    }

    Shader lightSourceShader = {0};
    if(!create_shader(&lightSourceShader, "assets/shaders/basic.vert", "assets/shaders/light.frag")){
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

    vec3 lightPosition = {0.0f,  0.0f,  0.0f};
    

    


    GLuint VAO, VBO;
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


    Texture texture1 = {0};
    if(!create_texture(&texture1, "assets/textures/wood.jpg")){
        window_destroy(&window);
        return -1;
    }
    vec3 lightColor = {1.0f, 1.0f, 1.0f};
        

    use_shader(&shader);
    set_uniform_int(&shader, "u_texture1", 0);
    set_uniform_vec3(&shader, "lightColor", lightColor);

    use_shader(&lightSourceShader);
    set_uniform_vec3(&lightSourceShader, "lightColor", lightColor);


    glfwSetFramebufferSizeCallback(window.handle, framebuffer_size_callback);
    window_set_key_callback(&window, key_callback);
    window_lock_cursor(&window);
    window_set_cursor_callback(&window,mouse_callback);

    init_camera(&camera, (vec3){0.0f, 0.0f, 3.0f});
    camera_set_sensitivity(&camera, 0.2f);


    // editor_init(&editor, window.handle);





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

    
        bind_texture(&texture1, 0);

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

        use_shader(&lightSourceShader);
        set_uniform_mat(&lightSourceShader, "view", view);
        set_uniform_mat(&lightSourceShader, "projection", projection);
        mat4 lightModel;
        glm_mat4_identity(lightModel);
        glm_translate(lightModel, lightPosition);
        set_uniform_mat(&lightSourceShader, "model", lightModel);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // if(editorOpen)
        //     editor_render(&editor, window.handle);


        



        window_swap_and_poll(&window);

    }


    delete_texture(&texture1);
    delete_shader(&shader);
    // editor_shutdown(&editor);
    window_destroy(&window);
    return 0;
}
