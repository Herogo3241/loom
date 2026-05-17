#include <stdbool.h>
#include <stdio.h>
#define STB_IMAGE_IMPLEMENTATION 
#include "texture.h"


bool create_texture(Texture* t, const char *texturePath){
    glGenTextures(1, &t->textureId);
    glBindTexture(GL_TEXTURE_2D, t->textureId);


    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(texturePath, &t->width, &t->height, &t->channels, 0);
    if (!data) {
        perror("failed to load texture");
        return false;
    }
    GLenum format;

    switch (t->channels) {
        case 3:
            format = GL_RGB;
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
            break;
        case 4:
            format = GL_RGBA;
            break;

    }
    glTexImage2D(GL_TEXTURE_2D, 0, format,t->width, t->height, 0, format, GL_UNSIGNED_BYTE, data); 
    glGenerateMipmap(GL_TEXTURE_2D);   

    stbi_image_free(data);
    return true;
}


void bind_texture(Texture *t, int unit){
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, t->textureId);
}


void delete_texture(Texture *t){
    if(t->textureId != 0){
        glDeleteTextures(1, &t->textureId);
        t->textureId = 0;
    }
}
