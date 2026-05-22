#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <cglm/cglm.h>

typedef struct {
    GLuint id;
} Shader;

int create_shader(Shader* s, const char* vertPath, const char* fragPath);
void use_shader(Shader* s);
void delete_shader(Shader* s);

//uniform functions
void set_uniform_float(Shader* s, const char* name, float value);
void set_uniform_int(Shader* s, const char* name, int value);
void set_uniform_mat(Shader* s, const char* name, mat4 value);
void set_uniform_vec3(Shader* s, const char* name, vec3 value);




#endif
