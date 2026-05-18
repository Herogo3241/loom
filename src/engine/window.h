#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdbool.h>


typedef struct{
    GLFWwindow* handle;
    int width;
    int height;
    const char* title;
}Window;

bool create_window_fullscreen(Window* w, const char* title); 
bool create_window(Window* w, const char* title, int width, int height);


bool window_should_close(Window* w);
void window_swap_and_poll(Window* w);

void window_set_cursor_callback(Window* w, GLFWcursorposfun fn);
void window_lock_cursor(Window* w);

float window_aspect_ratio(Window* w);

void window_destroy(Window* w);

