#pragma once

#include <glad/glad.h>
#include <stb_image.h>

char* parseShader(const char* filepath);
GLuint load_texture(const char* filepath);
GLfloat winToWorldCoord(int win); 
