#include "shader.h"
#include "../utils/util.h"
#include <stdio.h>

static GLuint compile_shader(GLenum shaderType, const char* shaderPath){
   const char* shaderSource = parseShader(shaderPath); 
   if(!shaderSource){
       perror("Could not load shader");
   }

   GLuint shader = glCreateShader(shaderType);
   glShaderSource(shader, 1, &shaderSource, NULL);
   glCompileShader(shader);

   int success;
   char info_log[512];
   glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
   if (!success) {
       glGetShaderInfoLog(shader, 512, NULL, info_log);
       printf("%s\n", info_log);
   
   }

   free((void*)shaderSource);

   return shader;

}

int create_shader(Shader *s, const char *vertPath, const char *fragPath){
    GLuint vertShader = compile_shader(GL_VERTEX_SHADER, vertPath);
    GLuint fragShader = compile_shader(GL_FRAGMENT_SHADER, fragPath);

    s->id = glCreateProgram();
    glAttachShader(s->id, vertShader);
    glAttachShader(s->id, fragShader);
    glLinkProgram(s->id);
    int success;
    char info_log[512];
    glGetProgramiv(s->id, GL_LINK_STATUS, &success);

    if(!success) {
        glGetProgramInfoLog(s->id, 512, NULL, info_log);

        printf("%s\n", info_log);

    }

    glDeleteShader(vertShader);
    glDeleteShader(fragShader);

    return success;
}


void use_shader(Shader *s){
    glUseProgram(s->id);
}


void delete_shader(Shader *s){
    glDeleteProgram(s->id);
}

void set_uniform_float(Shader *s, const char *name, float value){
    glUniform1f(glGetUniformLocation(s->id, name), value);
}

void set_uniform_int(Shader *s, const char *name, int value){
    glUniform1i(glGetUniformLocation(s->id, name), value);
}

void set_uniform_mat(Shader *s, const char *name, mat4 value){
    glUniformMatrix4fv(glGetUniformLocation(s->id, name),1, GL_FALSE, (float*)value);
}

void set_uniform_vec3(Shader* s, const char* name, vec3 value){
    glUniform3f(glGetUniformLocation(s->id, name), value[0], value[1], value[2]);
}
