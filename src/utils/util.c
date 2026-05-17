
#include <stdio.h>
#include <stdlib.h>
#define STB_IMAGE_IMPLEMENTATION 
#include "util.h"
#include <stdbool.h>

char* parseShader(const char* filepath){
    FILE* fp;

    fp = fopen(filepath, "rb");
    if(!fp){
        perror("failed to open shader\n");
        return NULL;
    }

    fseek(fp, 0, SEEK_END);
    long length = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char* buffer = (char*)malloc(length + 1);
    if(buffer){
        size_t bytesRead = fread(buffer, 1, length, fp);
        buffer[bytesRead] = '\0';
    }

    fclose(fp);

    return buffer;
}


GLuint load_texture(const char* filepath){

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, channels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(filepath, &width, &height, &channels, 0);
    if (data) {
        GLenum format;
        switch (channels) {
            case 3:
                format = GL_RGB;
                glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
                break;
            case 4:
                format = GL_RGBA;
                break;

        }
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data); 
        glGenerateMipmap(GL_TEXTURE_2D);   
    }else{
        perror("Failed to load image");
    }
    stbi_image_free(data);

    return texture;
}


