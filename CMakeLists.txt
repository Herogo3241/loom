cmake_minimum_required(VERSION 3.20)

project(loom)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(GLAD_DIR vendored/glad)

file(GLOB_RECURSE SOURCES "src/*.c" "src/*.cpp")

add_subdirectory(vendored/glfw)
add_subdirectory(vendored/cglm)

add_library(glad ${GLAD_DIR}/src/glad.c)
target_include_directories(glad PUBLIC ${GLAD_DIR}/include)

set(IMGUI_STATIC "yes" CACHE STRING "" FORCE)
add_subdirectory(vendored/cimgui)

# Backends live inside imgui — compile them separately as C++
# because your main sources are .c and CMake would treat them as C
add_library(imgui_backends STATIC
    vendored/cimgui/imgui/backends/imgui_impl_glfw.cpp
    vendored/cimgui/imgui/backends/imgui_impl_opengl3.cpp
)
target_include_directories(imgui_backends PUBLIC
    vendored/cimgui                        # cimgui.h
    vendored/cimgui/imgui                  # imgui.h (needed by backends internally)
    vendored/cimgui/imgui/backends         # imgui_impl_*.h
    vendored/glfw/include
    ${GLAD_DIR}/include
)
target_link_libraries(imgui_backends PUBLIC cimgui glfw glad)


add_executable(loom ${SOURCES})

target_include_directories(loom PRIVATE vendored/glfw/include vendored/stb vendored/glm vendored/nuklear vendored/nuklear/demo/glfw_opengl3 vendored/cimgui vendored/cimgui/imgui/backends) 



if (WIN32)
    target_link_libraries(loom PRIVATE
        cglm
        glfw
        glad
        imgui_backends
        opengl32
    )

    set_target_properties(loom PROPERTIES OUTPUT_NAME "loom_dev")
else()
    find_package(OpenGL REQUIRED)
    target_link_libraries(loom PRIVATE
        cglm
        glfw
        glad
        imgui_backends
        OpenGL::GL
    )
endif()
