#pragma once
#include <glad/glad.h>
#include <stdbool.h>
#include <stb_image.h>

typedef struct {
    GLuint textureId;
    int width;
    int height;
    int channels;
}Texture;

bool create_texture(Texture* t, const char* texturePath);
void bind_texture(Texture* t, int unit);
void delete_texture(Texture* t);


