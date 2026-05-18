#include "window.h"
#include <stdio.h>


bool create_window_fullscreen(Window *w, const char *title){
    if (!glfwInit()) {
        perror("Failed to initalize glfw!");
        return false; 
    }
    
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
    w->width = mode->width; w->height = mode->height;

    w->handle = glfwCreateWindow(mode->width, mode->height, title, monitor, NULL);
    if (!w->handle) {
        perror("Error creating window\n");
        return false;
    }

    glfwMakeContextCurrent(w->handle);
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        perror("Failed to initialize glad");
        return false;
    }
    glViewport(0, 0, mode->width, mode->height);
    glEnable(GL_DEPTH_TEST);

    return true;
}

bool create_window(Window *w, const char *title, int width, int height){
    if (!glfwInit()) {
        perror("Failed to initalize glfw!");
        return false; 
    }

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
    
    w->width = width; w->height = height;
    
    printf("Width: %d, Height: %d\n", w->width, w->height);

    w->handle = glfwCreateWindow(w->width, w->height, title, monitor, NULL);
    if (!w->handle) {
        perror("Error creating window\n");
        return false;
    }

    glfwMakeContextCurrent(w->handle);
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        perror("Failed to initialize glad");
        return false;
    }
    glViewport(0, 0, w->width, w->height);
    glEnable(GL_DEPTH_TEST);

    return true;
}



bool window_should_close(Window* w) {
    return glfwWindowShouldClose(w->handle);
}

void window_swap_and_poll(Window* w) {
    glfwSwapBuffers(w->handle);
    glfwPollEvents();
}

void window_set_cursor_callback(Window* w, GLFWcursorposfun fn) {
    glfwSetCursorPosCallback(w->handle, fn);
}

void window_lock_cursor(Window* w) {
    glfwSetInputMode(w->handle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

float window_aspect_ratio(Window* w) {
    return (float)w->width / (float)w->height;
}

void window_destroy(Window* w){
    if (w->handle) {
        glfwDestroyWindow(w->handle);
        w->handle = NULL;
    }
    glfwTerminate();
} 
