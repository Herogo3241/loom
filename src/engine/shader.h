#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

typedef struct {
    GLuint id;
} Shader;

int create_shader(Shader* s, const char* vertPath, const char* fragPath);
void use_shader(Shader* s);
void delete_shader(Shader* s);

//uniform functions
void set_uniform_float(Shader* s, const char* name, float value);



#endif
