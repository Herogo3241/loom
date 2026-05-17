#version 330 core
out vec4 FragColor;

in vec3 m_Color;
in vec2 m_TexCoord;
uniform float u_time;
uniform sampler2D u_texture;

void main() {
    FragColor = texture(u_texture, m_TexCoord); 
}
