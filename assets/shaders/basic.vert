#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexure;

out vec3 m_Color;
out vec2 m_TexCoord;

void main() {
    gl_Position = vec4(aPos, 1.0);
    m_Color = aColor;
    m_TexCoord = aTexure;
}
