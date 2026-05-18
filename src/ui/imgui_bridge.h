#pragma once

#ifdef __cplusplus
extern "C" {
#endif

// Forward declare GLFWwindow so you don't need to include glfw here
struct GLFWwindow;

// forward declare ImDrawData
typedef struct ImDrawData ImDrawData;

// Init
void bridge_ImGui_ImplGlfw_InitForOpenGL(struct GLFWwindow* window, bool install_callbacks);
void bridge_ImGui_ImplOpenGL3_Init(const char* glsl_version);

// Per-frame
void bridge_ImGui_ImplOpenGL3_NewFrame(void);
void bridge_ImGui_ImplGlfw_NewFrame(void);
void bridge_ImGui_ImplOpenGL3_RenderDrawData(ImDrawData* draw_data);

// Shutdown
void bridge_ImGui_ImplOpenGL3_Shutdown(void);
void bridge_ImGui_ImplGlfw_Shutdown(void);

#ifdef __cplusplus
}
#endif
