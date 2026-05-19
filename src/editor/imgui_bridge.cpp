#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include "imgui_bridge.h"  

extern "C" {
    void bridge_ImGui_ImplGlfw_InitForOpenGL(GLFWwindow* w, bool install_callbacks) {
        ImGui_ImplGlfw_InitForOpenGL(w, install_callbacks);
    }
    void bridge_ImGui_ImplOpenGL3_Init(const char* glsl_version) {
        ImGui_ImplOpenGL3_Init(glsl_version);
    }
    void bridge_ImGui_ImplOpenGL3_NewFrame(void)  { ImGui_ImplOpenGL3_NewFrame(); }
    void bridge_ImGui_ImplGlfw_NewFrame(void)     { ImGui_ImplGlfw_NewFrame(); }
    void bridge_ImGui_ImplOpenGL3_RenderDrawData(ImDrawData* d) {
        ImGui_ImplOpenGL3_RenderDrawData(d);
    }
    void bridge_ImGui_ImplOpenGL3_Shutdown(void)  { ImGui_ImplOpenGL3_Shutdown(); }
    void bridge_ImGui_ImplGlfw_Shutdown(void)     { ImGui_ImplGlfw_Shutdown(); }
}
