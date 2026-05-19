#pragma once
#include <stdbool.h>
#include <GLFW/glfw3.h>

#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include <cimgui.h>


typedef struct{
    ImGuiID id;
    ImGuiIO* io;
}Editor;

void toggle_editor(bool* isOpen);
void editor_init(Editor* e, GLFWwindow* window);
void editor_render(Editor* e, GLFWwindow* window);
void editor_shutdown(Editor* e);
