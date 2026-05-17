cmake_minimum_required(VERSION 3.20)

project(loom)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(GLAD_DIR vendored/glad)

file(GLOB_RECURSE SOURCES "src/*.c")

message("source: ${SOURCES}")

add_subdirectory(vendored/glfw)
add_subdirectory(vendored/cglm)

add_library(glad ${GLAD_DIR}/src/glad.c)
target_include_directories(glad PUBLIC ${GLAD_DIR}/include)


add_executable(loom ${SOURCES})

target_include_directories(loom PRIVATE vendored/glfw/include vendored/stb vendored/glm)



if (WIN32)
    target_link_libraries(loom PRIVATE
        glfw
        glad
        opengl32
    )

    set_target_properties(loom PROPERTIES OUTPUT_NAME "loom_dev")
else()
    find_package(OpenGL REQUIRED)

    target_link_libraries(loom PRIVATE
        cglm
        glfw
        glad
        OpenGL::GL
    )
endif()
