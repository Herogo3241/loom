#include "editor.h"
#include "cimgui.h"
#include "imgui_bridge.h"
#include <stdbool.h>
#include <stdio.h>


void toggle_editor(bool* isOpen) {
    if(isOpen) {
        *isOpen = !(*isOpen);
    }
}
bool check = false;
void editor_init(Editor* e, GLFWwindow *window){
    igCreateContext(NULL);
    e->io = igGetIO_Nil();

    e->io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    e->io->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    e->io->ConfigDpiScaleViewports = true;

    bridge_ImGui_ImplGlfw_InitForOpenGL(window, true);
    bridge_ImGui_ImplOpenGL3_Init("#version 330");

    igStyleColorsDark(NULL);
    ImGuiStyle* style = igGetStyle();
    if (e->io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style->WindowRounding = 2.0f;
        style->Colors[ImGuiCol_WindowBg].w = 1.0f;
    }
}

void editor_render(Editor* e, GLFWwindow *window){
    bridge_ImGui_ImplOpenGL3_NewFrame();
    bridge_ImGui_ImplGlfw_NewFrame();
    igNewFrame();




    igSetNextWindowSize((ImVec2_c){800, 600}, ImGuiCond_Once);
    if(igBegin("Loom Editor", NULL, ImGuiWindowFlags_None)){
        igCheckbox("simple", &check);
    }

    igEnd();
    igRender();
    bridge_ImGui_ImplOpenGL3_RenderDrawData(igGetDrawData());
    if (e->io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable) 
    {
        GLFWwindow *backup_current_window = glfwGetCurrentContext();
        igUpdatePlatformWindows();
        igRenderPlatformWindowsDefault(NULL, NULL);
        glfwMakeContextCurrent(backup_current_window);
    }}

void editor_shutdown(Editor* e){
    bridge_ImGui_ImplOpenGL3_Shutdown();
    bridge_ImGui_ImplGlfw_Shutdown();
    igDestroyContext(NULL);
    if(e)
        e->io = NULL;
}

